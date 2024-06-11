#ifndef MYRADIOBOX_H
#define MYRADIOBOX_H

#include <QObject>
#include "my_check_box.h"

class MyRadioBox : public QObject, public MyCheckBox
{
    Q_OBJECT
public:
    MyRadioBox(QRectF rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
public slots:
    void onClick();
signals:
    void click();
};

#endif // MYRADIOBOX_H
