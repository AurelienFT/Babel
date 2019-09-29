#include "login.hpp"
#include "QDebug"
#include <iostream>
#include "NetworkInterface.hpp"
#include "NetworkClient.hpp"

login::login()
{
    QList<qint32> color = {32, 34, 37, 255};
    QPair<qint32, qint32> size(1920, 1080);
    QPair<qint32, qint32> pos(0, 0);

    loginLayout = new QVBoxLayout();
    loginWidget = new customWidget(color, size, pos, nullptr, nullptr);
    loginBar = new QTabBar();
    setLoginWidget();
}


void login::setLoginWidget()
{
    setLoginBar();
    setLoginVLayout();
    setLoginHLayout();
    loginLayout->addWidget(loginBar);
    loginLayout->addLayout(formLayout);
    loginWidget->setLayout(loginLayout);
    connect(&formRegister->getRegisterButton(), SIGNAL(clicked()), this, SLOT(goToLogin()));
}

void login::setLoginHLayout()
{
    formLayout->addStretch();
    formLayout->addLayout(vLayout);
    formLayout->addStretch();
}

void login::setLoginVLayout()
{
    stack->addWidget(form->getFormWidget());
    stack->addWidget(formRegister->getFormWidget());
    vLayout->addStretch();
    vLayout->addWidget(stack);
    vLayout->addStretch();
}

void login::setLoginBar()
{
    loginBar->addTab("Connection");
    loginBar->addTab("Registration");
    loginBar->setDrawBase(false);
    loginBar->setStyleSheet("QTabBar::tab { max-width: 0px; height : 28px; border: 1px; color: #ffffff; background-color: #36393f; font-weight: bold}"
                            "QTabBar::tab:selected { max-width: 0px; height : 30px; border: 0px; color: #ffffff; background-color: #f26522}" );
     connect(loginBar, SIGNAL(currentChanged(int)), this, SLOT(setLoginLayout()));
}


customWidget *login::getLoginWidget() const {

    return(loginWidget);
}

// Private Slots//

void login::setLoginLayout() // Change le contenu de la fenêtre de login en fonction de la TabBar//
{
    if (loginBar->currentIndex() == 0)
        stack->setCurrentIndex(0);
    else if (loginBar->currentIndex() == 1)
        stack->setCurrentIndex(1);
}

void login::goToLogin() // Fonction pour aller à la feneêtre de connection //
{
    std::string login = formRegister->getLogin().toStdString();
    std::string password = formRegister->getPassword().toStdString();
    NetworkClient::instance()->send_server(MessageType::REGISTER, login + "|" + password);
    MessageType type = NetworkClient::instance()->receive_messageCode();
    std::cout << "type: " << static_cast<int>(type) << std::endl;
    loginBar->setCurrentIndex(0);
    stack->setCurrentIndex(0);
}




