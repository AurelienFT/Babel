#include "conversation.h"

conversation::conversation()
{
    conversationLayout = new QHBoxLayout();
    conversationFriend = new friendList();
    conversationChat = new chat();
    setConversation();
}

void conversation::setConversation()
{
    conversationLayout->setAlignment(Qt::AlignTop);
    conversationLayout->addLayout(conversationFriend->getIndividualLayout());
    conversationLayout->addLayout(conversationChat->getChatLayout());

}

QHBoxLayout *conversation::getConversationLayout() const
{
    return (conversationLayout);
}
