#include "friendlist.hpp"
#include <iostream>
#include <QSignalMapper>
#include <ostream>
#include "NetworkClient.hpp"

Babel::Graphic::friendList::friendList()
{
    setFriendListCLayout();
}

void Babel::Graphic::friendList::update(std::vector<std::string> users)
{
    clearLayout(_listVLayout);
    _listFriend = QList<QString>();
    for (auto user : users)
    {
        _listFriend.push_back(QString::fromStdString(user));
    }
    for (int i = 0; i < _listFriend.size(); i++)
    {
        contact *c = new contact(_listFriend[i], i, this);
        c->setMaximumWidth(280);
        c->setFixedHeight(50);
        connect(c, SIGNAL(clicked(int)), this, SLOT(buttonClicked(int)));
        _listVLayout->addWidget(c);
    }
}

void Babel::Graphic::friendList::createFriend(QList<QString> contactList)
{
    for (int i = 0; i < contactList.size(); i++)
    {
        contact *c = new contact(contactList[i], i, this);
        c->setMaximumWidth(280);
        c->setFixedHeight(50);
        connect(c, SIGNAL(clicked(int)), this, SLOT(buttonClicked(int)));
        _listVLayout->addWidget(c);
    }
}

void Babel::Graphic::friendList::setFriendListWidget()
{
    _listWidget->setLayout(_listVLayout);
    setFriendListScroll();
}

void Babel::Graphic::friendList::setFriendListScroll()
{
    _scrollArea->setMaximumWidth(280);
    _scrollArea->setStyleSheet("background-color: #2f3136");
    _scrollArea->setWidget(_listWidget);
    _scrollArea->setWidgetResizable(true);
}

void Babel::Graphic::friendList::setFriendListCLayout()
{
    QList<qint32> color = {242, 101, 34, 255};
    QPair<qint32, qint32> size(280, 50);
    QPair<qint32, qint32> pos(0, 1);
    _listRequest = {};
    customWidget *requestTitel = new customWidget(color, size, pos, "FRIENDS REQUEST", nullptr);
    requestTitel->setStyleSheet("font-weight: bold");
    requestTitel->setMaximumWidth(280);
    requestTitel->setFixedHeight(50);
    _container->addWidget(requestTitel);
    setFriendRequest();
    _listTitle = new customWidget(color, size, pos, "DIRECT MESSAGES", nullptr);
    _listTitle->setStyleSheet("font-weight: bold");
    _listTitle->setMaximumWidth(280);
    _listTitle->setFixedHeight(50);
    _signOut->setFixedSize(280, 60);
    _signOut->setStyleSheet("background-color:#2c9f32; color : white; font-weight: bold");
    _container->addWidget(_listTitle);
    setFriendListVLayout();
    _container->addWidget(_scrollArea);
    _container->addWidget(_signOut);
}

void Babel::Graphic::friendList::setFriendRequest()
{
    for (int i = 0; _listRequest.size() > i; i++)
    {
        friendRequest *request = new friendRequest(i, _listRequest[i]);
        connect(request, SIGNAL(clicked(int)), this, SLOT(addFriend(int)));
        connect(request, SIGNAL(reject(int)), this, SLOT(rejectFriend(int)));
        _friendRequest->addWidget(request);
    }
    _container->addLayout(_friendRequest);
}

void Babel::Graphic::friendList::setListFriendRequest(std::vector<std::string> users)
{
    clearLayout(_friendRequest);
    _listRequest = QList<QString>();
    for (auto user : users)
    {
        _listRequest.push_back(QString::fromStdString(user));
    }
    for (int i = 0; _listRequest.size() > i; i++)
    {
        friendRequest *request = new friendRequest(i, _listRequest[i]);
        connect(request, SIGNAL(clicked(int)), this, SLOT(addFriend(int)));
        connect(request, SIGNAL(reject(int)), this, SLOT(rejectFriend(int)));
        _friendRequest->addWidget(request);
    }
}

void HideAllWidgets(QLayout &layout)
{
    for (int i = 0; i < layout.count(); i++)
    {
        auto item = layout.itemAt(i);
        if (item->layout())
            HideAllWidgets(*item->layout());

        if (item->widget())
            item->widget()->hide();
    }
}

void Babel::Graphic::friendList::clearLayout(QLayout *layout)
{
    HideAllWidgets(*layout);

    QLayoutItem *item;
    while ((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
            delete item->layout();
        }

        if (item->widget())
            item->widget()->deleteLater();
        delete item;
    }
}
void Babel::Graphic::friendList::setFriendListVLayout()
{
    _listVLayout->setSpacing(0);
    _listVLayout->setAlignment(Qt::AlignTop);
    createFriend(_listFriend);
    setFriendListWidget();
}

QVBoxLayout *Babel::Graphic::friendList::getIndividualLayout()
{
    return (_container);
}

void Babel::Graphic::friendList::buttonClicked(int index)
{
    emit changeFriend(index);
}

void Babel::Graphic::friendList::addFriend(int index) // Here the user accept the friend request
{
    if (_listRequest.empty())
        return;
    std::cout << "user accepted " << _listRequest[index].toStdString() << std::endl;
    NetworkClient::instance()->send_server(MessageType::ACCEPT_FRIEND_REQUEST, _listRequest[index].toStdString());
    NetworkClient::instance()->receive_messageCode();
    QLayoutItem *wItem;
    if (_listRequest.size() == 1)
    {
        wItem = _friendRequest->layout()->takeAt(index);
        delete wItem;
        _listRequest = QList<QString>();
    }
    else if (_listRequest.size() > 1)
    {
        wItem = _friendRequest->layout()->takeAt(index);
        _listRequest.erase(_listRequest.begin() + index);
        delete wItem;
    }
    else
    {
        wItem = _friendRequest->layout()->takeAt(0);
        delete wItem;
    }
}

void Babel::Graphic::friendList::rejectFriend(int index) // Here the user reject the friend request
{
    if (_listRequest.empty())
        return;
    NetworkClient::instance()->send_server(MessageType::REJECT_FRIEND_REQUEST, _listRequest[index].toStdString());
    NetworkClient::instance()->receive_messageCode();
    QLayoutItem *wItem;
    if (_listRequest.size() == 1)
    {
        wItem = _friendRequest->layout()->takeAt(index);
        delete wItem;
        _listRequest = QList<QString>();
    }
    else if (_listRequest.size() > 1)
    {
        wItem = _friendRequest->layout()->takeAt(index);
        _listRequest.erase(_listRequest.begin() + index);
        delete wItem;
    }
    else
    {
        wItem = _friendRequest->layout()->takeAt(0);
        delete wItem;
    }
}
