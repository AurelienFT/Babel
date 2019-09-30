#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include <QObject>
#include <QVBoxLayout>
#include <QPushButton>
#include "contact.hpp"
#include "customwidget.hpp"
#include <QWidget>
#include <QScrollArea>
#include <QDialog>

class friendList : public QWidget
{

    Q_OBJECT

public:

    friendList();
    QVBoxLayout *getIndividualLayout();
    void setFriendListWidget();
    void setFriendListScroll();
    void setFriendListCLayout();
    void setFriendListVLayout();
    void createFriend(QList<QString> contactList);

private slots:
    void buttonClicked(int index);
    void addContact();

signals:
    void changeFriend(int index);

private:

      QScrollArea *f_scrollArea = new QScrollArea;
      QVBoxLayout *f_listVLayout = new QVBoxLayout();
      QVBoxLayout *f_container = new QVBoxLayout();
      customWidget *f_listTitle;
      QList<QString> f_listFriend = {"laura", "arnaud", "délice", "coucou", "kikou", "juju", "koko", "lulu","lili","paul"};
      QPushButton *f_add = new QPushButton("ADD FRIENDS");
      QWidget *f_listWidget = new QWidget;
      qint32 f_currentFriend;
      qint32 f_index;

};

#endif // FRIENDLIST_H