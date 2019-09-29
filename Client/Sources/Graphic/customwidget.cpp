#include "customwidget.hpp"
#include <QPainter>
#include <QDebug>

customWidget::customWidget(QList<qint32> color, QPair<qint32, qint32> size, QPair<qint32, qint32> pos, QString txt, QWidget *parent)
    :  QWidget(parent), w_txt(txt), w_color(color), w_size(size), w_pos(pos) {}

void customWidget::setColorWidget(QList<qint32> color)
{
    w_color = color;
}

void customWidget::setSizeWidget(QPair<qint32, qint32> size)
{
    w_size = size;
}

void customWidget::setPosWidget(QPair<qint32, qint32> pos)
{
    w_pos = pos;
}

void customWidget::paintEvent(QPaintEvent *event)
{
    QPainter w_painter(this);

    (void)event;

    if (w_click == true) {
        w_painter.setPen(QColor(242, 101, 34, 255));
        w_painter.setBrush(QColor(242, 101, 34,255));
    } else if (w_click == false){
        w_painter.setPen(QColor(w_color[0], w_color[1], w_color[2], w_color[3]));
        w_painter.setBrush(QColor(w_color[0], w_color[1], w_color[2], w_color[3]));
    }
    w_painter.drawRect(w_pos.first, w_pos.second, w_size.first, w_size.second);

    if (w_txt != nullptr) {
        w_painter.setPen(Qt::white);
        w_painter.setFont(QFont("Arial", 12));
        w_painter.drawText(QRectF(0, 0, w_size.first, w_size.second), Qt::AlignCenter | Qt::AlignTop, w_txt);
    }
}

void customWidget::mousePressEvent(QMouseEvent *event)
{

//    w_click = true;
//    repaint();
}

void customWidget::mouseReleaseEvent(QMouseEvent *event)
{
//    w_click = false;
//    repaint();
}
