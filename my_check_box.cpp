#include "my_check_box.h"

#include <QPainter>

MyCheckBox::MyCheckBox(QRectF rect, bool is_checked, int arc) : is_checked_(is_checked)
{
    arc_ = (arc > 1) ? arc : 1;
    setRect(rect);
    setFlag(QGraphicsItem::ItemIsFocusable);    
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
    path.addRoundedRect(rect(), arc_, arc_);
    path.addRoundedRect(rect().adjusted(arc_, arc_, -arc_, -arc_), arc_, arc_);
    painter->setPen(QColor(0, 14, 63));
    painter->fillPath(path, QColor(0, 14, 63));
    painter->drawPath(path);

    if (is_checked_)
    {
        QPainterPath check;
        check.addEllipse(rect().adjusted(2*arc_, 2*arc_, -2*arc_, -2*arc_));
        painter->fillPath(check, QColor(0, 14, 63));
        painter->drawPath(check);
    }
}

void MyCheckBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    is_checked_ = !is_checked_;
    update();
}

