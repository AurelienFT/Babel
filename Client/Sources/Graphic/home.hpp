#ifndef HOME_H
#define HOME_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include "customwidget.hpp"
#include <QTabBar>
#include "conversation.hpp"
#include <QStackedWidget>
#include "managefriend.hpp"
#include <iostream>

namespace Babel {

    namespace Graphic {

        class home : public QWidget
        {
            Q_OBJECT

            public:
            /**
                *constructor : build a home object
            */
                home();
            /**
                *destructor : destroy a home object
            */
                ~home() = default;
            /**
                *getter the home widget
                @return _homeWidget
            */
                customWidget *getHomeWidget() const;
            /**
                *set home
            */
                void setHome();
            /**
                *set home bar
            */
                void setHomeBar();
            /**
                *getter conversation object
            */
                conversation *getConversation() const {
                    return (_conversationStatut);
                };

            private slots:
            /**
                *set the home layout
            */
                void setHomeLayout();

            private :

                QVBoxLayout *_homeLayout;
                customWidget *_homeWidget;
                QTabBar *_homeBar;
                conversation *_conversationStatut;
                ManageFriend * _friendStatut = new ManageFriend();
                QStackedWidget *_stack = new QStackedWidget();
        };
    }
}

#endif // HOME_H
