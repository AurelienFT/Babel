#include "conversation.hpp"
#include <iostream>

Babel::Graphic::conversation::conversation()
{
    _conversationLayout = new QHBoxLayout();
    _conversationFriend = new friendList();
    _conversationChat = new chat(_currentFriend.toStdString());
    setConversation();
}

void Babel::Graphic::conversation::setConversation()
{
    _conversationLayout->setAlignment(Qt::AlignTop);
    _conversationLayout->addLayout(_conversationFriend->getIndividualLayout());

    QPair<QString, QString> a("Laura", "Coucou ca va ?");
    QPair<QString, QString> b("Jean", "Coucou oui et toi ?");
    QPair<QString, QString> c("Laura", "Yep yep super alors quoi de neuf ?");
    QPair<QString, QString> d("Bouh", "lolo");
    QPair<QString, QString> e("Bibi", "lili");
    QList<QPair<QString, QString>> mList({ a});

    QPair<qint32, qint32> s_size(100, 80);
    QPair<qint32, qint32> m_size(1400, 80);
    QList<qint32> color = {32, 34, 37, 255};
    QList<message> lm;


    for (int i = 0; i < mList.size(); i++) {
        message m(mList[i].first, mList[i].second, s_size, m_size);
        lm.push_front(m);
    }
    _conversationChat->setMessage(lm);
    connect(_conversationFriend, SIGNAL(changeFriend(int)), this, SLOT(getMessage(int)));
    _conversationLayout->addLayout(_conversationChat->getChatLayout());
}

QHBoxLayout *Babel::Graphic::conversation::getConversationLayout() const
{
    return (_conversationLayout);
}

void Babel::Graphic::conversation::getMessage(int index) //fonction pour recevoir la liste de message //
 {
    QPair<QString, QString> a("Laura", "Coucou ca va ?");
    QPair<QString, QString> b("Jean", "Coucou oui et toi ?");
    QPair<QString, QString> c("Laura", "Yep yep super alors quoi de neuf ?");
    QPair<QString, QString> d("Bouh", "lolo");
    QPair<QString, QString> e("Bibi", "lili");
    QList<QPair<QString, QString>> mList({ a,b,c,d,e });
    QList<QPair<QString, QString>> mList2({ a,b });

    QPair<qint32, qint32> s_size(100, 80);
    QPair<qint32, qint32> m_size(1400, 80);
    QList<qint32> color = {32, 34, 37, 255};
    QList<message> ml;
    QList<message> ml2;


    for (int i = 0; i < mList.size(); i++) {
        message m(mList[i].first, mList[i].second, s_size, m_size);
        ml.push_front(m);
    }

    for (int i = 0; i < mList2.size(); i++) {
        message m(mList[i].first, mList[i].second, s_size, m_size);
        ml2.push_front(m);
    }

    if (index == 1)
        _conversationChat->setMessage(ml);
    if (index == 2)
        _conversationChat->setMessage(ml2);
    if (_conversationFriend->_listFriend.length() - 1 < index)
        _currentFriend = "";
    else
        _currentFriend = _conversationFriend->_listFriend[index];
        _conversationChat->setFriend(_currentFriend.toStdString());
 }
