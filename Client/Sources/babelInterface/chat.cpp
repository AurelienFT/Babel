#include "chat.h"
#include "message.h"

chat::chat()
{
    c_entry->setMaximumSize(1620, 100);
    c_chat->setMaximumSize(1620, 1000);
    QWidget *contenu = new QWidget;
    contenu->setLayout(c_scroll);
    QVBoxLayout *coucou = new QVBoxLayout();

    c_entry->setStyleSheet("background-color: #36393f");
    c_chat->setStyleSheet("background-color: #36393f");

    coucou->setAlignment(Qt::AlignTop);

    message m("Laura", "Coucou ca va ?");
    message n("Jean", "Coucou oui et toi ?");
    message p("Laura", "Yep yep super alors quoi de neuf ?");
    message o("Bouh", "lolo");
    message q("Bibi", "lili");
    message r("Bouh", "lolo");
    message s("Bibi", "lili");
    QWidget *m_s = m.getWidgetSender();
    m_s->setFixedSize(1550, 100);
    QWidget *m_m = m.getWidgetMessage();
    m_m->setFixedSize(1550, 100);
    QWidget *m_j = n.getWidgetSender();
    m_j->setFixedSize(1550, 100);
    QWidget *p_j = n.getWidgetMessage();
     p_j->setFixedSize(1550, 100);
    QWidget *p_l = p.getWidgetMessage();
    p_l->setFixedSize(1550, 100);
    QWidget *p_v = p.getWidgetSender();
    p_v->setFixedSize(1550, 100);
    QWidget *o_l = o.getWidgetMessage();
      o_l->setFixedSize(1550, 100);
    QWidget *o_v = o.getWidgetSender();
     o_v->setFixedSize(1550, 100);
    QWidget *i_l = q.getWidgetMessage();
       i_l->setFixedSize(1550, 100);
    QWidget *i_v = q.getWidgetSender();
        i_v->setFixedSize(1550, 100);
    QWidget *s_l = s.getWidgetMessage();
    s_l->setFixedSize(1550, 100);
    QWidget *s_v = s.getWidgetSender();
    QWidget *r_l = r.getWidgetMessage();
    QWidget *r_v = r.getWidgetSender();

    c_scroll->addLayout(coucou);
    coucou->addWidget(m_s);
    coucou->addWidget(m_m);
    coucou->addWidget(m_j);
    coucou->addWidget(p_j);
    coucou->addWidget(p_l);
    coucou->addWidget(o_l);
    coucou->addWidget(o_v);
    coucou->addWidget(i_l);
    coucou->addWidget(i_v);
    coucou->addWidget(r_l);
    coucou->addWidget(r_v);




//     c_scroll->setSpacing(0);
//    m_s->setMaximumWidth(1620);
//    m_s->setFixedHeight(100);


//    c_scroll->addWidget(m_s);
//    c_scroll->addWidget(m_m);
//    c_scroll->addWidget(m_j);
//    c_scroll->addWidget(p_j);
//    c_scroll->addWidget(p_l);

//    c_scroll->addWidget(p_v);

//    c_scroll->addWidget(o_l);
//    c_scroll->addWidget(o_v);
//    c_scroll->addWidget(i_l);
//    c_scroll->addWidget(i_v);
//    c_scroll->addWidget(s_l);
//    c_scroll->addWidget(s_v);

//    c_scroll->addWidget(r_l);
//    c_scroll->addWidget(r_v);



    c_chat->setWidget(contenu);
    c_chat->setWidgetResizable(true);

    c_entry->setAlignment(Qt::AlignRight);
    QHBoxLayout *horizontal = new QHBoxLayout();
    QPushButton *call = new QPushButton("CALL");

    horizontal->addWidget(c_entry);
    horizontal->addWidget(call);
    call->setMinimumSize(60, 100);
    call->setStyleSheet("background-color:#2c9f32;color: white;font-weight: bold");


        c_container->addWidget(c_chat);
    c_container->addLayout(horizontal);
}

void chat::setChatVLayout()
{

}

void chat::setChatScroll()
{

}


void chat::setListMessage()
{

}






QVBoxLayout *chat::getChatLayout()
{
    return (c_container);
}
