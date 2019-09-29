#ifndef HOME_H
#define HOME_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <customwidget.h>
#include <QTabBar>
#include <conversation.h>
#include <QStackedWidget>
#include <managefriend.h>
#include <iostream>


class home : public QWidget
{
    Q_OBJECT

public:

    home();
    customWidget *getHomeWidget() const;
    void setHome();
    void setHomeBar();

private slots:

    void setHomeLayout();

private :

    QVBoxLayout *homeLayout;
    customWidget *homeWidget;
    QTabBar *homeBar;
    conversation *conversationStatut;
    ManageFriend * h_friendStatut = new ManageFriend();
    QStackedWidget *h_stack = new QStackedWidget();

};

#endif // HOME_H
