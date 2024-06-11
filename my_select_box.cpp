#include "my_select_box.h"

#include <QPainter>

MySelectBox::MySelectBox(QRectF rect, int format, int min, int max) : format_(format), kMin_(min), kMax_(max)
{
    setRect(rect);
    setFlag(QGraphicsItem::ItemIsFocusable);
    val_ = (format_ == BOARD_SIZE ? 4 : 300);
}

void MySelectBox::setVal(int val)
{
    if (val >= kMin_ && val <= kMax_)
    {
        val_ = val;
        update();
    }
}

void MySelectBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 5, 5);
    path.addRoundedRect(rect().adjusted(5, 5, -5, -5), 5, 5);
    path.addRoundedRect(rect().adjusted(10, 10, -164, -10), 5, 5);
    path.addRoundedRect(rect().adjusted(164, 10, -10, -10), 5, 5);
    painter->setPen(QColor(0, 14, 63));
    painter->fillPath(path, QColor(0, 14, 63));
    painter->drawPath(path);

    painter->setFont(QFont("Irish Grover", 24));
    painter->setPen(QColor(0, 14, 63));
    QString text = "";
    if (format_ == BOARD_SIZE)
        text = QString::number(val_)+"x"+QString::number(val_);
    else
    {
        text = QString::number(val_/60)+":";
        text += (val_%60 < 10) ? "0"+QString::number(val_%60) : QString::number(val_%60);
    }

    painter->drawText(rect(), Qt::AlignCenter, text);
}

void MySelectBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QRectF left_rect = rect().adjusted(10, 10, -164, -10);
    QRectF right_rect = rect().adjusted(164, 10, -10, -10);
    if (left_rect.contains(event->pos()))
        setVal(val_ - (format_ == BOARD_SIZE ? 1 : 10));
    else if (right_rect.contains(event->pos()))
        setVal(val_ + (format_ == BOARD_SIZE ? 1 : 10));
}
