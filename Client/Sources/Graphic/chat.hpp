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

            /**
                *constructor : init a chat object 
            */
                chat();
            /**
                *destructor : destroy a chat object
            */ 
                ~chat() = default;
                chat(std::string friendToAdd);
            /**
                *Return the layout of chat object
                @return c_chatCLayout
            */
                QVBoxLayout *getChatLayout();
            /**
                *Init the vertical Layout of chat object
            */
                void setChatVLayout();
            /**
                *Init the scroll area of chat object
            */
                void setChatScroll();
            /**
                *Init list message of chat object
            */
                void setListMessage();
            /**
                *Add a object message to the list Message
            */
                void addMessage();
            /**
                *Set the central widget of the chat object
            */ 
                void setChatWidget();
            /**
                *Set the horizontal layout of the chat object 
            */  
                void setChatHLayout();
            /**
                *Send a message text
                @param mList list of message of the chat object
            */  
                void sendMessage(QList<QPair<QString, QString>> mList);
            /**
                *Set Message text
                 @param listMessage list of message of the chat object
            */
                void setMessage(QList<message>listMessage);
            /**
                *Clear the main layout of the chat object
                @param layout main layout of the main object
            */
                void clearLayout(QLayout *layout);
                void setFriend(std::string friendToAdd) {
                    _currentFriend = friendToAdd;
                }

            public slots:

            /**
                *Slot to send Message
            */
                void sendMessage();
            /**
                Slot to send a dummy response message
            */
                void sendResponse();
            /**
             * Change the state of the call
             */ 
                void changeStateCall();

            private:

                bool _stateCall = 0;
                QWidget *_chatWidget = new QWidget;
                QVBoxLayout *_chatCLayout = new QVBoxLayout();
                QVBoxLayout *_chatVLayout = new QVBoxLayout();
                QVBoxLayout *_chatList = new QVBoxLayout();
                QHBoxLayout *_chatHLayout = new QHBoxLayout();
                QScrollArea *_chatScroll =  new QScrollArea();
                QTextEdit *_chatEntry = new QTextEdit();
                QPushButton *_chatCall = new QPushButton("CALL");
                QPushButton *_chatSend = new QPushButton("SEND");
                QPushButton *_chatResponse = new QPushButton("REP");
                QList<message>_listMessage;
                std::string _currentFriend = "";
                VoIpNetwork::VoIpClient *_clientAudio;
        };
    } 
}

#endif // CHAT_H
