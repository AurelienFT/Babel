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
    QWidget *conversation = new QWidget();
//    QWidget *manageFriend = new QWidget();

    conversation->setLayout(conversationStatut->getConversationLayout());
//    manageFriend->setLayout(h_friendStatut->getFriendLayout());
    h_stack->addWidget(conversation);
    h_stack->addWidget(h_friendStatut->getFormWidget());
    setHomeBar();
    homeLayout->addWidget(homeBar);
    homeLayout->addWidget(h_stack);
    homeWidget->setLayout(homeLayout);
}

void home::setHomeBar()
{

    homeBar->addTab("Conversations");
    homeBar->addTab("Friends");
    homeBar->addTab("Profil");
    homeBar->setDrawBase(false);
    homeBar->setStyleSheet("QTabBar::tab { max-width: 0px; height : 28px; border: 1px; color: #ffffff; background-color: #36393f; font-weight: bold}"
                           "QTabBar::tab:selected { max-width: 0px; height : 30px; border: 0px; color: #ffffff; background-color: #f26522}" );
    connect(homeBar, SIGNAL(currentChanged(int)), this, SLOT(setHomeLayout()));
}

customWidget *home::getHomeWidget() const
{
    return (homeWidget);
}

void home::setHomeLayout() // Change le contenu de la fenêtre de login en fonction de la TabBar//
{
    std::cout << "coucou34" << std::endl;
    if (homeBar->currentIndex() == 0)
        h_stack->setCurrentIndex(0);
    else if (homeBar->currentIndex() == 1)
        h_stack->setCurrentIndex(1);
}
