#include "home.h"

home::home()
{
    QList<qint32> color = {32, 34, 37, 255};
    QPair<qint32, qint32> size(1920, 1080);
    QPair<qint32, qint32> pos(0, 0);

    homeLayout = new QVBoxLayout(nullptr);
    homeWidget = new customWidget(color, size, pos, nullptr, nullptr);
    homeBar = new QTabBar(nullptr);
    conversationStatut = new conversation();
    setHome();

}

void home::setHome()
{

    setHomeBar();
    homeLayout->addWidget(homeBar);
    homeLayout->addLayout(conversationStatut->getConversationLayout());
    homeWidget->setLayout(homeLayout);

}

void home::setHomeBar()
{

    homeBar->addTab("Conversations");
    homeBar->addTab("Profil");
    homeBar->addTab("Options");
    homeBar->setDrawBase(false);
    homeBar->setStyleSheet("QTabBar::tab { max-width: 0px; height : 28px; border: 1px; color: #ffffff; background-color: #36393f; font-weight: bold}"
                           "QTabBar::tab:selected { max-width: 0px; height : 30px; border: 0px; color: #ffffff; background-color: #f26522}" );

}

customWidget *home::getHomeWidget() const
{

    return (homeWidget);

}
