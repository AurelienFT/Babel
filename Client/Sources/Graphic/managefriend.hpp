#ifndef MANAGEFRIEND_H
#define MANAGEFRIEND_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include "customwidget.hpp"
#include <QFormLayout>
#include<QLineEdit>
#include <QPushButton>

namespace Babel {

    namespace Graphic {

        class ManageFriend : public QWidget
        {
            Q_OBJECT

            public:
            /**
                *constructor : build a ManageFriend object
            */
                ManageFriend();
            /**
                *destructor : destroy a ManageFriend object
            */
                ~ManageFriend() = default;
            /**
                *get the main layout
                @return _formLayout
            */
                QHBoxLayout *getFriendLayout() const;
             /**
                *get the main widget
                @return _formWidget
            */
                QWidget *getFormWidget() const;
            /**
                *get the password
                @return password
            */
                QString getPassword() const;
            /**
                *get the login
                @return login
            */
                QString getLogin() const;
            /**
                *set the _formWidget
            */
                void setFormWidget();
            /**
                *set the container layout
            */
                void setFormCLayout();
            /**
                *set the vertical layout
            */
                void setFormVLayout();
            /**
                *set the horizontal layout
            */
                void setFormHLayout();

            private slots:
            /**
                *add a friend
            */
                void addFriend();
            /**
                *remove friend
            */
                void removeFriend();

            private:

                QHBoxLayout *_FriendHLayout = new QHBoxLayout();
                QVBoxLayout *_formLayout = new QVBoxLayout;
                QHBoxLayout *_Horizontal = new QHBoxLayout;
                customWidget *_formWidget;
                QFormLayout *_formForm = new QFormLayout;
                QLineEdit *_formLogin= new QLineEdit;
                QLineEdit *_formPassword= new QLineEdit;
                QPushButton *_add = new QPushButton("ADD");
                QPushButton *_remove = new QPushButton("REMOVE");
        };
    }
}

#endif // MANAGEFRIEND_H
