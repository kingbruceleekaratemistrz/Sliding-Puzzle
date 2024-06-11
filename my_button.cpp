#include "my_button.h"

#include <QPainter>

MyButton::MyButton(QRectF rect, QString text) : text_(text)
{
    setRect(rect);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "KLIKENS";
    emit click();
}

void MyButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 5, 5);
    painter->setPen(QColor(0, 14, 63));
    painter->fillPath(path, QColor(0, 14, 63));
    painter->drawPath(path);

    painter->setFont(QFont("Irish Grover", 24));
    painter->setPen(QColor(208, 211, 231));
    painter->drawText(rect(), Qt::AlignCenter, text_);
}
