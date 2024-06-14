#include "my_select_box.h"

#include <QPainter>

MySelectBox::MySelectBox(QRectF rect, int format, int min, int max, int val, int font_size, int arc)
    : format_(format), kMin_(min), kMax_(max), val_(val), font_size_(font_size)
{
    arc_ = (arc > 1) ? arc : 1;
    setRect(rect);
    setFlag(QGraphicsItem::ItemIsFocusable);    
}

void MySelectBox::setVal(int val)
{
    if (val <= kMin_)
        val_ = kMin_;
    else if (val >= kMax_)
        val_ = kMax_;
    else
        val_ = val;
    update();
}

int MySelectBox::val()
{
    return val_;
}

void MySelectBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    int h = rect().height();
    int w = rect().width();

    QPainterPath path;
    path.addRoundedRect(rect(), arc_, arc_);
    path.addRoundedRect(rect().adjusted(arc_, arc_, -arc_, -arc_), arc_, arc_);

    int arrow_size = rect().height() - 4*arc_;
    QPixmap arrow_left("./assets/settings/arrow_left.png");
    QPixmap arrow_right("./assets/settings/arrow_right.png");
    painter->drawPixmap(rect().x()+2*arc_, rect().y()+2*arc_, arrow_left.scaled(arrow_size, arrow_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter->drawPixmap(rect().x()+w-h+2*arc_, rect().y()+2*arc_, arrow_right.scaled(arrow_size, arrow_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    painter->setPen(QColor(0, 14, 63));
    painter->fillPath(path, QColor(0, 14, 63));
    painter->drawPath(path);

    painter->setFont(QFont("Irish Grover", font_size_));
    painter->setPen(QColor(0, 14, 63));
    QString text = "";
    if (format_ == BOARD_SIZE)
        text = QString::number(val_)+"x"+QString::number(val_);
    else if (format_ == TIME)
    {
        if (val_ == 0)
            text = "Wył.";
        else
        {
            text = QString::number(val_/60)+":";
            text += (val_%60 < 10) ? "0"+QString::number(val_%60) : QString::number(val_%60);
        }
    }
    else
        text = QString::number(val_)+"/"+QString::number(kMax_);


    painter->drawText(rect(), Qt::AlignCenter, text);
}

void MySelectBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int h = rect().height();
    int w = rect().width();
    QRectF left_rect = rect().adjusted(2*arc_, 2*arc_,  h-w-2*arc_, -2*arc_);
    QRectF right_rect = rect().adjusted(w-h+2*arc_, 2*arc_, -2*arc_, -2*arc_);

    int new_val;
    if (format_ == TIME)
        new_val = 10;
    else
        new_val = 1;
    if (left_rect.contains(event->pos()))
    {
        setVal(val_ - new_val);
    }
    else if (right_rect.contains(event->pos()))
        setVal(val_ + new_val);
    emit click();
}
