#include "friendlist.h"
#include <iostream>
#include <QSignalMapper>

friendList::friendList()
{
    setFriendListCLayout();
}

void friendList::createFriend(QList<QString> contactList)
{

    for (int i = 0; i < contactList.size(); i++) {
       contact *c = new contact(contactList[i], i , this);
       c->setMaximumWidth(280);
       c->setFixedHeight(50);
       connect(c, SIGNAL(clicked(int)), this, SLOT(buttonClicked(int)));
       f_listVLayout->addWidget(c);
    }
}

void friendList::setFriendListWidget()
{
    f_listWidget->setLayout(f_listVLayout);
    setFriendListScroll();
}


void friendList::setFriendListScroll()
{
   f_scrollArea->setMaximumWidth(280);
   f_scrollArea->setStyleSheet("background-color: #2f3136");
   f_scrollArea->setWidget(f_listWidget);
   f_scrollArea->setWidgetResizable(true);
}

void friendList::setFriendListCLayout()
{
    QList<qint32> color = {242, 101, 34, 255};
    QPair<qint32, qint32> size(280, 50);
    QPair<qint32, qint32> pos(0, 1);

    f_listTitle = new customWidget(color, size, pos, "DIRECT MESSAGES", nullptr);
    f_listTitle->setStyleSheet("font-weight: bold");
    f_listTitle->setMaximumWidth(280);
    f_listTitle ->setFixedHeight(50);
    f_add->setFixedSize(280, 60);
    f_add->setStyleSheet("background-color:#2c9f32; color : white; font-weight: bold");
    f_container->addWidget(f_add);
    f_container->addWidget(f_listTitle);
    setFriendListVLayout();
    f_container->addWidget(f_scrollArea);
    QWidget::connect(f_add, SIGNAL(clicked()), this, SLOT(addContact()));
}

void friendList::setFriendListVLayout()
{
    f_listVLayout->setSpacing(0);
    f_listVLayout->setAlignment(Qt::AlignTop);
    createFriend(f_listFriend);
    setFriendListWidget();
}

void friendList::addContact()
{
//    std::cout << "coucou" << std::endl;
//     QDialog fenetre;
//     fenetre.setWindowFlags(Qt::Tool);
//     fenetre.show();

}

QVBoxLayout *friendList::getIndividualLayout()
{
    return(f_container);
}

void friendList::buttonClicked(int index)
  {
//    std::cout << index << std::endl;
    emit changeFriend(index);
  }
