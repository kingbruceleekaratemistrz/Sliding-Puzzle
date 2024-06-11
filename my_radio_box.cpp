#include "my_radio_box.h"

#include <QGraphicsSceneMouseEvent>

MyRadioBox::MyRadioBox(QRectF rect) : MyCheckBox(rect)
{
}

void MyRadioBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (isChecked() == true)
        event->accept();
    else
    {
        MyCheckBox::mousePressEvent(event);
        emit click();
    }
}

void MyRadioBox::onClick()
{
    if (isChecked())
    {
        setChecked(!isChecked());
        update();
    }
}
