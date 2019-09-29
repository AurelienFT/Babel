#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "customwidget.hpp"
#include "friendlist.hpp"
#include "chat.hpp"
#include "QFormLayout"
#include "home.hpp"
#include "login.hpp"
#include "QStackedWidget"

class MainWindow : public QMainWindow
{

    Q_OBJECT


public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void slotDisplayFen();

private:

    QStackedWidget *stack;
    customWidget *homeWidget;
    home *homePage;
    login *loginPage;
    int fenIndex = 0;

};

#endif // MAINWINDOW_H
