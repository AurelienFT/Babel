#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QObject>
#include <QWidget>

namespace Babel {

    namespace Graphic {

        class customWidget : public QWidget
        {

            Q_OBJECT

            public:

                explicit customWidget(QList<qint32> color, QPair<qint32, qint32> size, QPair<qint32, qint32>, QString txt, QWidget *parent = nullptr);
                void setColorWidget(QList<qint32> color);
                void setSizeWidget(QPair<qint32, qint32> size);
                void setPosWidget(QPair<qint32, qint32> pos);
                void setClicked(bool click);

            protected:

                void paintEvent(QPaintEvent *event);
                void mousePressEvent(QMouseEvent *event);
                void mouseReleaseEvent(QMouseEvent *event);

            private:

                QString w_txt;
                QList<qint32> w_color;
                QPair<qint32, qint32> w_size;
                QPair<qint32, qint32> w_pos;
                bool w_click = false;
        };
    }
}

#endif // CUSTOMWIDGET_H
