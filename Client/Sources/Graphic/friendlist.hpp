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
#include "friendrequest.hpp"


namespace Babel {

    namespace Graphic {

        class friendList : public QWidget {

            Q_OBJECT

            public:
            /**
                *constructor : build a frienList object 
            */
                friendList();
            /**
                *destructor : destroy a friendList object 
            */
                ~friendList() = default;
            /**
                *get a main layout of friendList object
                @return _container
            */
                QVBoxLayout *getIndividualLayout();
            /**
                *init the friendList Widget
            */
                void setFriendListWidget();
            /**
                *init the friendList scroll area
            */
                void setFriendListScroll();
            /**
                *init the friendList main layout
            */
                void setFriendListCLayout();
            /**
                *init the friendList vertical layout
            */
                void setFriendListVLayout();
            /**
                *create a friend object
                @param contactList list of contact
            */
                void createFriend(QList<QString> contactList);
            /**
                *upadte the main layout of the friendList object
                @param users list of contact's name
            */
                void update(std::vector<std::string> users);
            /**
                *set a friend request
            */
                void setFriendRequest();
            /**
                *set the friendList friend request 
                @param users list of the friend request
            */
                void setListFriendRequest(std::vector<std::string> users);
            /**
                *clear a layout 
                @param layout main layout 
            */
                void clearLayout(QLayout *layout);
            /**
                *sign out
            */
                QPushButton *getSignOut() {
                    return (_signOut);
                };
                QList<QString> _listFriend;

            private slots:

            /**
                *add friend into friendList 
                @param index index of the friend 
            */
                void addFriend(int index);
            /**
                *catch the clicked 
                @param index index of the friend 
            */
                void buttonClicked(int index);
            /**
                *reject friend request 
                @param index index of the friend 
            */
                void rejectFriend(int index);

            signals:
            /**
                *change friend signal 
                @param index index of the friend 
            */
                void changeFriend(int index);

            private:

                QScrollArea *_scrollArea = new QScrollArea;
                QVBoxLayout *_listVLayout = new QVBoxLayout();
                QVBoxLayout *_container = new QVBoxLayout();
                customWidget *_listTitle;
                QVBoxLayout *_friendRequest = new QVBoxLayout();
                QPushButton *_signOut = new QPushButton("SIGN OUT");
                QWidget *_listWidget = new QWidget;
                QList<QString> _listRequest;
                qint32 _currentFriend;
                qint32 _index;
        };
    }
}

#endif // FRIENDLIST_H
