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

                ManageFriend();
                QHBoxLayout *getFriendLayout() const;
                QWidget *getFormWidget() const;
                QString getPassword() const;
                QString getLogin() const;
                void setFormWidget();
                void setFormCLayout();
                void setFormVLayout();
                void setFormHLayout();

            private slots:

                void addFriend();
                void removeFriend();

            private:

                QHBoxLayout *m_FriendHLayout = new QHBoxLayout();
                QVBoxLayout *formLayout = new QVBoxLayout;
                QHBoxLayout *Horizontal = new QHBoxLayout;
                customWidget *formWidget;
                QFormLayout *formForm = new QFormLayout;
                QLineEdit *formLogin= new QLineEdit;
                QLineEdit *formPassword= new QLineEdit;
                QPushButton *add = new QPushButton("ADD");
                QPushButton *remove = new QPushButton("REMOVE");
        };
    }
}

#endif // MANAGEFRIEND_H
