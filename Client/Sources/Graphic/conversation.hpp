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

                conversation();
                QHBoxLayout *getConversationLayout() const;
                void setConversation();
                friendList *getFriendList() const {
                    return (conversationFriend);
                };

            private slots:

                void getMessage(int index);

            private:

                QHBoxLayout *conversationLayout;
                chat *conversationChat;
                friendList *conversationFriend;
                int _index = -1;
                QString _currentFriend;
        };
    }
}

#endif // CONVERSATION_H
