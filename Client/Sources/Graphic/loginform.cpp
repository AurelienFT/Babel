#include "loginform.hpp"

Babel::Graphic::loginForm::loginForm()
{
    setFormWidget();
}

void Babel::Graphic::loginForm::setFormWidget() // Set the form widget
{
    QList<qint32> color = {47, 49, 54, 255};
    QPair<qint32, qint32> size(800, 500);
    QPair<qint32, qint32> pos(0, 1);
    setFormVLayout();
    setFormHLayout();
    setFormCLayout();

    _formWidget = new customWidget(color, size, pos, nullptr, nullptr);
    _formWidget->setMinimumSize(800, 500);
    _formWidget->setLayout(_formLayout);
}

void Babel::Graphic::loginForm::setFormCLayout() // Set the container Layout
{
    _formLayout->addStretch();
    _formLayout->addLayout(_formForm);
    _formLayout->addStretch();
    _formLayout->addLayout(_Horizontal);
}

void Babel::Graphic::loginForm::setFormVLayout() // Set the vertical layout
{
    _formLogin->setMaximumSize(700, 50);
    _formPassword->setMaximumSize(700, 50);
    _formForm->addRow("Login :", _formLogin);
    _formForm->addRow("Password :", _formPassword);
}

void Babel::Graphic::loginForm::setFormHLayout() // Set the horizontal Layout
{
    _validate->setMinimumSize(200,50);
    _validate->setStyleSheet("background-color: #ffffff;");
    _Horizontal->addStretch();
    _Horizontal->addWidget(_validate);
    _Horizontal->addStretch();
}

// Getter /

QWidget *Babel::Graphic::loginForm::getFormWidget() const 
{
    return (_formWidget);
}

QPushButton &Babel::Graphic::loginForm::getValidateButton() const
{
    return (*_validate);
}

QString Babel::Graphic::loginForm::getPassword() const
{
    return (_formPassword->text());
}

QString Babel::Graphic::loginForm::getLogin() const
{
    return (_formLogin->text());
}


