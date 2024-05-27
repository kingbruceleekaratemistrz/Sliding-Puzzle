#include "tile_graphics_item.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>

TileGraphicsItem::TileGraphicsItem(QRectF rect, QString text) : text_(text)
{
    setRect(rect);
}

TileGraphicsItem::TileGraphicsItem(int x, int y, int w, int h, QString text) : text_(text)
{
    setRect(x, y, w, h);
}

void TileGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(QColor(50, 40, 200));
    painter->drawRect(rect());

    painter->setFont(QFont("Arial", 30));
    painter->drawText(rect(), Qt::AlignCenter, text_);
}

void TileGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "!kilK";
    emit click();
}

QString TileGraphicsItem::getText()
{
    return text_;
}
