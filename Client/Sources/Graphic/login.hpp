#ifndef LOGIN_H
#define LOGIN_H

#include <QVBoxLayout>
#include <customwidget.hpp>
#include <QTabBar>
#include "loginform.hpp"
#include "loginregister.hpp"
#include "QStackedWidget"

namespace Babel {

    namespace Graphic {

        class login : public QWidget
        {

            Q_OBJECT

            public:
            /**
                *constructor : build a login object
            */
                login();
            /**
                *destructor : build a login object
            */
                ~login() = default;
            /**
                *get the login main widget
                @return _loginWidget;
            */
                customWidget *getLoginWidget() const;
            /**
                *set the login bar
            */
                void setLoginBar();
            /**
                *set the login widget
            */
                void setLoginWidget();
            /**
                *set the login vertical layout
            */
                void setLoginVLayout();
            /**
                *set the login horizontal layout
            */
                void setLoginHLayout();
                loginForm *form = new loginForm();
                loginRegister *formRegister = new loginRegister();


            private slots:
            /**
                *set the layout
            */
                void setLoginLayout();
            /**
                *go to the login widget
            */
                void goToLogin();

            private:

                QVBoxLayout *_loginLayout;
                QVBoxLayout *_vLayout = new QVBoxLayout();
                customWidget *_loginWidget;
                customWidget *_registerWidget;
                QTabBar *_loginBar;
                QHBoxLayout *_formLayout = new QHBoxLayout();
                QStackedWidget *_stack = new QStackedWidget();
        };
    }
}

#endif // LOGIN_H
