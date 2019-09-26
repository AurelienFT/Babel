#ifndef CUSTOMLAYOUT_H
#define CUSTOMLAYOUT_H

#include <QObject>

class customLayout : public QVBoxLayout
{

public:

    customLayout();

private:

    QString *title;

};

#endif // CUSTOMLAYOUT_H
