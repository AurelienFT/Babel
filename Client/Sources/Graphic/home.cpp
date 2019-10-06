#include "home.hpp"

Babel::Graphic::home::home()
{
    QList<qint32> color = {32, 34, 37, 255};
    QPair<qint32, qint32> size(1920, 1080);
    QPair<qint32, qint32> pos(0, 0);

    _homeLayout = new QVBoxLayout(nullptr);
    _homeWidget = new customWidget(color, size, pos, nullptr, nullptr);
    _homeBar = new QTabBar(nullptr);
    _conversationStatut = new conversation();
    setHome();
}

void Babel::Graphic::home::setHome()
{
    QWidget *conversation = new QWidget();

    conversation->setLayout(_conversationStatut->getConversationLayout());
    _stack->addWidget(conversation);
    _stack->addWidget(_friendStatut->getFormWidget());
    setHomeBar();
    _homeLayout->addWidget(_homeBar);
    _homeLayout->addWidget(_stack);
    _homeWidget->setLayout(_homeLayout);
}

void Babel::Graphic::home::setHomeBar()
{

    _homeBar->addTab("Conversations");
    _homeBar->addTab("Friends");
    _homeBar->addTab("Profil");
    _homeBar->setDrawBase(false);
    _homeBar->setStyleSheet("QTabBar::tab { max-width: 0px; height : 28px; border: 1px; color: #ffffff; background-color: #36393f; font-weight: bold}"
                           "QTabBar::tab:selected { max-width: 0px; height : 30px; border: 0px; color: #ffffff; background-color: #f26522}" );
    connect(_homeBar, SIGNAL(currentChanged(int)), this, SLOT(setHomeLayout()));
}

Babel::Graphic::customWidget *Babel::Graphic::home::getHomeWidget() const
{
    return (_homeWidget);
}

void Babel::Graphic::home::setHomeLayout() // Change le contenu de la fenêtre de login en fonction de la TabBar//
{
    if (_homeBar->currentIndex() == 0)
        _stack->setCurrentIndex(0);
    else if (_homeBar->currentIndex() == 1)
        _stack->setCurrentIndex(1);
}
