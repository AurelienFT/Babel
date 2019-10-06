#include "chat.hpp"
#include "message.hpp"
#include "iostream"
#include "Interface/NetworkInterface.hpp"
#include "NetworkClient.hpp"
#include <QDebug>

Babel::Graphic::chat::chat(std::string currentFriend) : _currentFriend(currentFriend)
{
    setChatWidget();
}

void Babel::Graphic::chat::setChatWidget()
{
    _chatEntry->setMaximumSize(1620, 100);
    _chatScroll->setMaximumSize(1620, 1000);
    _chatEntry->setStyleSheet("background-color: #36393f");
    _chatScroll->setStyleSheet("background-color: #36393f");
    setChatVLayout();
    _chatWidget->setLayout(_chatVLayout);
    setChatHLayout();
    setChatScroll();
    _chatCLayout->addWidget(_chatScroll);
    _chatCLayout->addLayout(_chatHLayout);
    connect(_chatSend, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(_chatResponse, SIGNAL(clicked()), this, SLOT(sendResponse()));
    connect(_chatSend, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(_chatCall, SIGNAL(clicked()), this, SLOT(changeStateCall()));
}

void Babel::Graphic::chat::setChatHLayout()
{
    _chatEntry->setAlignment(Qt::AlignLeft);
    _chatHLayout->addWidget(_chatEntry);
    _chatHLayout->addWidget(_chatSend);
    _chatHLayout->addWidget(_chatResponse);
    _chatHLayout->addWidget(_chatCall);
    _chatEntry->setStyleSheet("color:white; background-color: #36393f; font-weight: bold; font-size: 15px;");
    _chatSend->setMinimumSize(60, 100);
    _chatSend->setStyleSheet("background-color:#2c9f32;color: white;font-weight: bold");
    _chatCall->setMinimumSize(60, 100);
    _chatCall->setStyleSheet("background-color:#2c9f32;color: white;font-weight: bold");
    _chatResponse->setMinimumSize(60, 100);
    _chatResponse->setStyleSheet("background-color:#2c9f32;color: white;font-weight: bold");
}

void Babel::Graphic::chat::setChatVLayout()
{
    setListMessage();
    _chatVLayout->addLayout(_chatList);
}

void Babel::Graphic::chat::setChatScroll()
{
    _chatScroll->setWidget(_chatWidget);
    _chatScroll->setWidgetResizable(true);
}

void Babel::Graphic::chat::setListMessage()
{
    _chatList->setAlignment(Qt::AlignTop);
    clearLayout(_chatList);
    addMessage();
}

void Babel::Graphic::chat::clearLayout(QLayout *layout)
{
    QLayoutItem *item;

    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
    }
}

void Babel::Graphic::chat::addMessage()
{
    for (int i = 0; i < _listMessage.size(); i++) {
       message m = _listMessage[i];
       QWidget *m_s = m.getWidgetSender();
       QWidget *m_m = m.getWidgetMessage();
       QHBoxLayout *barMessage = new QHBoxLayout();
       m_s->setFixedSize(100, 100);
       m_m->setFixedSize(1400, 100);
       barMessage->addWidget(m_s);
       barMessage->addWidget(m_m, Qt::AlignLeft);
       _chatList->addLayout(barMessage);
    }
}

void Babel::Graphic::chat::sendMessage()
{
    QPair<qint32, qint32> s_size(100, 80);
    QPair<qint32, qint32> m_size(1400, 80);
    QList<qint32> color = {32, 34, 37, 255};

    if (_chatEntry->toPlainText() != nullptr) {
        message m("Laura", _chatEntry->toPlainText(), s_size, m_size);
        _chatEntry->clear();
        QWidget *m_s = m.getWidgetSender();
        QWidget *m_m = m.getWidgetMessage();
        QHBoxLayout *barMessage = new QHBoxLayout();
        m_s->setFixedSize(100, 100);
        m_m->setFixedSize(1400, 100);
        barMessage->addWidget(m_s);
        barMessage->addWidget(m_m, Qt::AlignLeft);
        _chatList->addLayout(barMessage);
    }
}

void Babel::Graphic::chat::setMessage(QList<message> listMessage)
{
    _listMessage = listMessage;
    setListMessage();
}

void Babel::Graphic::chat::sendResponse()
{
    QPair<qint32, qint32> s_size(100, 80);
    QPair<qint32, qint32> m_size(1400, 80);
    QList<qint32> color = {32, 34, 37, 255};

    message m("Bouh", "blabla", s_size, m_size);
    QWidget *m_s = m.getWidgetSender();
    QWidget *m_m = m.getWidgetMessage();
    QHBoxLayout *barMessage = new QHBoxLayout();
    m_s->setFixedSize(100, 100);
    m_m->setFixedSize(1400, 100);
    barMessage->addWidget(m_s);
    barMessage->addWidget(m_m, Qt::AlignLeft);
    _chatList->addLayout(barMessage);
}

void Babel::Graphic::chat::changeStateCall()
{
    if (_currentFriend == "") {
        std::cerr << "Click on friend before" << std::endl;
    }
    if (_stateCall == 0) {
        NetworkClient::instance()->send_server(MessageType::CALL, _currentFriend);
        MessageType code = NetworkClient::instance()->receive_messageCode();
        if (code != MessageType::OK) {
            std::cerr << "Error friend not connected" << std::endl;
            return;
        }
        std::string reponse = NetworkClient::instance()->getReponse();
        _chatCall->setStyleSheet("background-color: #e3191e;color: white;font-weight: bold");
        _chatCall->setText("HANG UP");
        _stateCall = 1;
        int port = std::stoi(reponse);
        _clientAudio = new VoIpNetwork::VoIpClient(SERVER_ADDRESS, port);
        std::cout << "port = " << port << std::endl;
        std::cout << "IL EST CONNECTE MAGGLE" << std::endl;
        _clientAudio->recvOtherClientData();
        _clientAudio->startTransmition();
    } else if (_stateCall == 1) {
        _clientAudio->stop();
        delete _clientAudio;
        _chatCall->setStyleSheet("background-color: #2c9f32;color: white;font-weight: bold");
        _chatCall->setText("CALL");
        _stateCall = 0;
    }
}

QVBoxLayout *Babel::Graphic::chat::getChatLayout()
{
    return (_chatCLayout);
}