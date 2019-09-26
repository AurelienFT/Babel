#ifndef HOME_H
#define HOME_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <customwidget.h>
#include <QTabBar>
#include <conversation.h>


class home : public QWidget
{
    Q_OBJECT

public:

    home();
    customWidget *getHomeWidget() const;
    void setHome();
    void setHomeBar();

private :

    QVBoxLayout *homeLayout;
    customWidget *homeWidget;
    QTabBar *homeBar;
    conversation *conversationStatut;

};

#endif // HOME_H
