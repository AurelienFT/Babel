#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QVBoxLayout>
#include <QWidget>
#include "customwidget.hpp"
#include <QFormLayout>
#include <QLineEdit>
#include "QPushButton"

class loginForm :  public QWidget
{

    Q_OBJECT

public:

    loginForm();

    QWidget *getFormWidget() const;
    QPushButton &getValidateButton();
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
    QPushButton *validate = new QPushButton("Validate");

};

#endif // LOGINFORM_H
