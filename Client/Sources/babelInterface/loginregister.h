#ifndef LOGINREGISTER_H
#define LOGINREGISTER_H


#include <QVBoxLayout>
#include <QWidget>
#include "customwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include "QPushButton"
#include "loginform.h"
#include "QDebug"
#include "QObject"


class loginRegister :  public QWidget
{

    Q_OBJECT

public:

    loginRegister();
    QWidget *getFormWidget() const;
    QPushButton &getRegisterButton();
    QString getPassword() const;
    QString getLogin() const;
    void setFormWidget();
    void setFormCLayout();
    void setFormVLayout();
    void setFormHLayout();

private:

    QVBoxLayout *formLayout = new QVBoxLayout;
    QHBoxLayout *Horizontal = new QHBoxLayout;
    customWidget *formWidget;
    QFormLayout *formForm = new QFormLayout;
    QLineEdit *formLogin= new QLineEdit;
    QLineEdit *formPassword= new QLineEdit;
    QPushButton *validate = new QPushButton("Register");

};

#endif // LOGINREGISTER_H
