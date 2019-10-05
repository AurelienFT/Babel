#ifndef CHAT_H
#define CHAT_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include "message.hpp"
#include "VoIpClient.hpp"
#include <QList>
#include <QObject>

namespace Babel {

    namespace Graphic {

        class chat : public QWidget
        {
            Q_OBJECT

            public:

                chat(std::string friendToAdd);
                QVBoxLayout *getChatLayout();
                void setChatVLayout();
                void setChatScroll();
                void setListMessage();
                void addMessage();
                void setChatWidget();
                void setChatHLayout();
                void addMessage(QList<QPair<QString, QString>> mList);
                void sendMessage(QList<QPair<QString, QString>> mList);
                void setMessage(QList<message>listMessage);
                void clearLayout(QLayout *layout);
                void setFriend(std::string friendToAdd) {
                    _currentFriend = friendToAdd;
                }

            public slots:

                void sendMessage();
                void sendResponse();
                void changeStateCall();

            private:

                bool c_stateCall = 0;
                QWidget *c_chatWidget = new QWidget;
                QVBoxLayout *c_chatCLayout = new QVBoxLayout();
                QVBoxLayout *c_chatVLayout = new QVBoxLayout();
                QVBoxLayout *c_chatList = new QVBoxLayout();
                QHBoxLayout *c_chatHLayout = new QHBoxLayout();
                QScrollArea *c_chatScroll =  new QScrollArea();
                QTextEdit *c_chatEntry = new QTextEdit();
                QPushButton *c_chatCall = new QPushButton("CALL");
                QPushButton *c_chatSend = new QPushButton("SEND");
                QPushButton *c_chatResponse = new QPushButton("REP");
                QList<message>c_listMessage;
                std::string _currentFriend = "";
                VoIpNetwork::VoIpClient *_clientAudio;
        };
    }
}

#endif // CHAT_H
