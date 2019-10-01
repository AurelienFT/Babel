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

                login();
                customWidget *getLoginWidget() const;
                void setLoginBar();
                void setLoginWidget();
                void setLoginVLayout();
                void setLoginHLayout();
                loginForm *form = new loginForm();
                loginRegister *formRegister = new loginRegister();


            private slots:

                void setLoginLayout();
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
