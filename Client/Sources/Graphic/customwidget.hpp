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
            /**
                *constructor : build a customWidget object 
                @param color color of the widget
                @param size size of the widget
                @param pos pos of the widget 
                @param txt txt in widget
                @param parent parent of the widget
            */
                explicit customWidget(QList<qint32> color, QPair<qint32, qint32> size, QPair<qint32, qint32> pos, QString txt, QWidget *parent = nullptr);
            /**
                *destructor : destroy a customWidget object
            */
                ~customWidget() = default;
            /**
                *set the color of the widget
                @param color color of the widget
            */
                void setColorWidget(QList<qint32> color);
            /**
                *set the size of the widget
                @param size size of the widget
            */
                void setSizeWidget(QPair<qint32, qint32> size);
            /**
                *set the pos of the widget
                @param pos pos of the widget
            */
                void setPosWidget(QPair<qint32, qint32> pos);

            protected:
            /**
                *overload of the method paintEvent
                @param event event
            */
                void paintEvent(QPaintEvent *event);

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
