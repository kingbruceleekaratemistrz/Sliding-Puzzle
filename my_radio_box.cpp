#include "my_radio_box.h"

#include <QGraphicsSceneMouseEvent>

MyRadioBox::MyRadioBox(QRectF rect, bool is_checked, int arc) : MyCheckBox(rect, is_checked, arc)
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
