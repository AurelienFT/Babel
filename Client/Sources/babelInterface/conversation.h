#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <QHBoxLayout>
#include <chat.h>
#include <friendlist.h>

class conversation
{

public:

    conversation();
    QHBoxLayout *getConversationLayout() const;
    void setConversation();

private:

    QHBoxLayout *conversationLayout;
    chat *conversationChat;
    friendList *conversationFriend;
};

#endif // CONVERSATION_H
