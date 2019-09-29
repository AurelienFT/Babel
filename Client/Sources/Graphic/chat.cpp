#include "chat.hpp"
#include "message.hpp"
#include "iostream"
#include <QDebug>

chat::chat()
{
    setChatWidget();
}

void chat::setChatWidget()
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

void chat::setChatHLayout()
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

void chat::setChatVLayout()
{
    setListMessage();
    c_chatVLayout->addLayout(c_chatList);
}

void chat::setChatScroll()
{
    c_chatScroll->setWidget(c_chatWidget);
    c_chatScroll->setWidgetResizable(true);
}

void chat::setListMessage()
{
    c_chatList->setAlignment(Qt::AlignTop);
    clearLayout(c_chatList);
    addMessage();
}

void chat::clearLayout(QLayout *layout)
{
    QLayoutItem *item;

    while((item = layout->takeAt(0))) {
        std::cout << "coucou" << std::endl;
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            std::cout << "coucou1" << std::endl;
            delete item->widget();
        }
        std::cout << "coucou2" << std::endl;
    }
}

void chat::addMessage()
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

void chat::sendMessage()
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


void chat::setMessage(QList<message> listMessage)
{
    c_listMessage = listMessage;
    setListMessage();

}
void chat::sendResponse()
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

void chat::changeStateCall()
{
    if (c_stateCall == 0) {
        c_chatCall->setStyleSheet("background-color: #e3191e;color: white;font-weight: bold");
        c_chatCall->setText("HANG UP");
        c_stateCall = 1;
    } else if (c_stateCall == 1) {
        c_chatCall->setStyleSheet("background-color: #2c9f32;color: white;font-weight: bold");
        c_chatCall->setText("CALL");
        c_stateCall = 0;
    }
}

QVBoxLayout *chat::getChatLayout()
{
    return (c_chatCLayout);
}
