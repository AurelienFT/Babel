#include "mainwindow.h"
#include "QDebug"
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
    std::cout << "test" << std::endl;
    if ((fenIndex < 0) || (fenIndex > 1)) {return;}
    stack->setCurrentIndex(fenIndex);
}

