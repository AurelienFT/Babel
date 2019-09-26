#ifndef CHAT_H
#define CHAT_H

#include <QScrollArea>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include "message.h"

class chat
{

public:

    chat();
    QVBoxLayout *getChatLayout();
    void setChatVLayout();
    void setChatScroll();
    void setListMessage();

private:

    QVBoxLayout *c_container = new QVBoxLayout();
    QVBoxLayout *c_scroll = new QVBoxLayout();
    QScrollArea *c_chat =  new QScrollArea();
    QTextEdit *c_entry = new QTextEdit();
    QList<message>  *c_listMessage;

};

#endif // CHAT_H
