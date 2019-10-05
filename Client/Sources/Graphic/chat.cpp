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
    c_chatEntry->setMaximumSize(1620, 100);
    c_chatScroll->setMaximumSize(1620, 1000);
    c_chatEntry->setStyleSheet("background-color: #36393f");
    c_chatScroll->setStyleSheet("background-color: #36393f");
    setChatVLayout();
    c_chatWidget->setLayout(c_chatVLayout);
    setChatHLayout();
    setChatScroll();
    c_chatCLayout->addWidget(c_chatScroll);
    c_chatCLayout->addLayout(c_chatHLayout);
    connect(c_chatSend, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(c_chatResponse, SIGNAL(clicked()), this, SLOT(sendResponse()));
    connect(c_chatSend, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(c_chatCall, SIGNAL(clicked()), this, SLOT(changeStateCall()));

}

void Babel::Graphic::chat::setChatHLayout()
{
    c_chatEntry->setAlignment(Qt::AlignLeft);
    c_chatHLayout->addWidget(c_chatEntry);
    c_chatHLayout->addWidget(c_chatSend);
    c_chatHLayout->addWidget(c_chatResponse);
    c_chatHLayout->addWidget(c_chatCall);
    c_chatEntry->setStyleSheet("color:white; background-color: #36393f; font-weight: bold; font-size: 15px;");
    c_chatSend->setMinimumSize(60, 100);
    c_chatSend->setStyleSheet("background-color:#2c9f32;color: white;font-weight: bold");
    c_chatCall->setMinimumSize(60, 100);
    c_chatCall->setStyleSheet("background-color:#2c9f32;color: white;font-weight: bold");
    c_chatResponse->setMinimumSize(60, 100);
    c_chatResponse->setStyleSheet("background-color:#2c9f32;color: white;font-weight: bold");

}

void Babel::Graphic::chat::setChatVLayout()
{
    setListMessage();
    c_chatVLayout->addLayout(c_chatList);
}

void Babel::Graphic::chat::setChatScroll()
{
    c_chatScroll->setWidget(c_chatWidget);
    c_chatScroll->setWidgetResizable(true);
}

void Babel::Graphic::chat::setListMessage()
{
    c_chatList->setAlignment(Qt::AlignTop);
    clearLayout(c_chatList);
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
    for (int i = 0; i < c_listMessage.size(); i++) {
       message m = c_listMessage[i];
       QWidget *m_s = m.getWidgetSender();
       QWidget *m_m = m.getWidgetMessage();
       QHBoxLayout *barMessage = new QHBoxLayout();
       m_s->setFixedSize(100, 100);
       m_m->setFixedSize(1400, 100);
       barMessage->addWidget(m_s);
       barMessage->addWidget(m_m, Qt::AlignLeft);
       c_chatList->addLayout(barMessage);
    }
}

void Babel::Graphic::chat::sendMessage()
{
    QPair<qint32, qint32> s_size(100, 80);
    QPair<qint32, qint32> m_size(1400, 80);
    QList<qint32> color = {32, 34, 37, 255};

    if (c_chatEntry->toPlainText() != nullptr) {
        message m("Laura", c_chatEntry->toPlainText(), s_size, m_size);
        c_chatEntry->clear();
        QWidget *m_s = m.getWidgetSender();
        QWidget *m_m = m.getWidgetMessage();
        QHBoxLayout *barMessage = new QHBoxLayout();
        m_s->setFixedSize(100, 100);
        m_m->setFixedSize(1400, 100);
        barMessage->addWidget(m_s);
        barMessage->addWidget(m_m, Qt::AlignLeft);
        c_chatList->addLayout(barMessage);
    }
}


void Babel::Graphic::chat::setMessage(QList<message> listMessage)
{
    c_listMessage = listMessage;
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
    c_chatList->addLayout(barMessage);
}

void Babel::Graphic::chat::changeStateCall()
{
    if (_currentFriend == "") {
        std::cerr << "Click on friend before" << std::endl;
    }
    if (c_stateCall == 0) {
        NetworkClient::instance()->send_server(MessageType::CALL, _currentFriend);
        MessageType code = NetworkClient::instance()->receive_messageCode();
        if (code != MessageType::OK) {
            std::cerr << "Error friend not connected" << std::endl;
            return;
        }
        std::string reponse = NetworkClient::instance()->getReponse();
        c_chatCall->setStyleSheet("background-color: #e3191e;color: white;font-weight: bold");
        c_chatCall->setText("HANG UP");
        c_stateCall = 1;
        int port = std::stoi(reponse);
        _clientAudio = new VoIpNetwork::VoIpClient(SERVER_ADDRESS, port);
        std::cout << "port = " << port << std::endl;
        std::cout << "IL EST CONNECTE MAGGLE" << std::endl;
        _clientAudio->recvOtherClientData();
        _clientAudio->startTransmition();
    } else if (c_stateCall == 1) {
        _clientAudio->stop();
        delete _clientAudio;
        c_chatCall->setStyleSheet("background-color: #2c9f32;color: white;font-weight: bold");
        c_chatCall->setText("CALL");
        c_stateCall = 0;
    }
}

QVBoxLayout *Babel::Graphic::chat::getChatLayout()
{
    return (c_chatCLayout);
}
