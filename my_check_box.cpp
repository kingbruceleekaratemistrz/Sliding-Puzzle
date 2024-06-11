#include "my_check_box.h"

#include <QPainter>

MyCheckBox::MyCheckBox(QRectF rect)
{
    setRect(rect);
    setFlag(QGraphicsItem::ItemIsFocusable);
    is_checked_ = false;
}

bool MyCheckBox::isChecked()
{
    return is_checked_;
}

void MyCheckBox::setChecked(bool state)
{
    is_checked_ = state;
}

void MyCheckBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 5, 5);
    path.addRoundedRect(rect().adjusted(5, 5, -5, -5), 5, 5);
    painter->setPen(QColor(0, 14, 63));
    painter->fillPath(path, QColor(0, 14, 63));
    painter->drawPath(path);

    if (is_checked_)
    {
        QPainterPath check;
        check.addEllipse(rect().adjusted(10, 10, -10, -10));
        painter->fillPath(check, QColor(0, 14, 63));
        painter->drawPath(check);
    }
}

void MyCheckBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    is_checked_ = !is_checked_;
    update();
}

