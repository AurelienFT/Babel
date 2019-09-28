#include "mainwindow.h"
#include "QDebug"
#include "NetworkClient.hpp"
#include <iostream>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    homePage = new home();
    loginPage = new login();
    setWindowTitle("Babel");
    stack = new QStackedWidget(this);

    stack->addWidget(loginPage->getLoginWidget());
    stack->addWidget(homePage->getHomeWidget());

    this->setCentralWidget(stack);
    stack->setCurrentIndex(fenIndex); // on affiche la première fenêtre à l'ouverture du programme
    std::cout <<"test1" << std::endl;


    QWidget::connect(&loginPage->form->getValidateButton(), SIGNAL(clicked()), this, SLOT(slotDisplayFen()));
}
MainWindow::~MainWindow() {}

void MainWindow::slotDisplayFen()
{
    fenIndex = 1;
    std::string username = loginPage->form->getLogin().toStdString();
    std::string password = loginPage->form->getPassword().toStdString();
    NetworkClient::instance()->send_server(MessageType::LOGIN, username + "|" + password);
    MessageType returnType = NetworkClient::instance()->receive_messageCode();
    if (returnType == MessageType::OK) {
        if ((fenIndex < 0) || (fenIndex > 1)) {return;}
        stack->setCurrentIndex(fenIndex);
    } else {
        std::cout << "error login" << std::endl;
    }
}

