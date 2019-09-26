#ifndef LOGIN_H
#define LOGIN_H

#include <QVBoxLayout>
#include <customwidget.h>
#include <QTabBar>
#include "loginform.h"
#include "loginregister.h"
#include "QStackedWidget"


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

    QVBoxLayout *loginLayout;
    QVBoxLayout *vLayout = new QVBoxLayout();
    customWidget *loginWidget;
    customWidget *registerWidget;
    QTabBar *loginBar;
    QHBoxLayout *formLayout = new QHBoxLayout();
    QStackedWidget *stack = new QStackedWidget();
};

#endif // LOGIN_H
