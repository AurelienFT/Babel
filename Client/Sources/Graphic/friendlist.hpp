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

                friendList();
                QVBoxLayout *getIndividualLayout();
                void setFriendListWidget();
                void setFriendListScroll();
                void setFriendListCLayout();
                void setFriendListVLayout();
                void createFriend(QList<QString> contactList);
                void update(std::vector<std::string> users);
                void setFriendRequest();
                void setListFriendRequest(std::vector<std::string> users);
                void clearLayout(QLayout *layout);
                void updateFriend();
                QPushButton *getSignOut() {
                    return (_signOut);
                };
                QList<QString> _listFriend;

            private slots:

                void addFriend(int index);
                void buttonClicked(int index);
                void rejectFriend(int index);

            signals:

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
