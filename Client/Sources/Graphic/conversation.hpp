#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QHBoxLayout>
#include "chat.hpp"
#include "friendlist.hpp"
#include "message.hpp"

namespace Babel {

    namespace Graphic {

        class conversation : public QWidget
        {
            Q_OBJECT

            public:
            /**
                *constructor : build a conversation object 
            */
                conversation();
            /**
                *destructor : destroy a conversation object 
            */
                ~conversation() = default;
            /**
                *return the main layout of conversation object
            */
                QHBoxLayout *getConversationLayout() const;
            /**
                *init a conversation object
            */
                void setConversation();
            /**
                *return the object conversation
                @return  a conversation object
            */
            
                friendList *getFriendList() const 
                {
                    return (_conversationFriend);
                };

            private slots:
            /**
                *slot to get the message 
                @param index index of the contact
            */
                void getMessage(int index);

            private:

                QHBoxLayout *_conversationLayout;
                chat *_conversationChat;
                friendList *_conversationFriend;
                int _index = -1;
                QString _currentFriend;
        };
    }
}

#endif // CONVERSATION_H
