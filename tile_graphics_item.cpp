#include "tile_graphics_item.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>

TileGraphicsItem::TileGraphicsItem(QRectF rect, QString text, QColor color) : text_(text), color_(color)
{
    setRect(rect);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(2);
    setGraphicsEffect(effect);
}

TileGraphicsItem::TileGraphicsItem(int x, int y, int w, int h, QString text, QColor color) : text_(text), color_(color)
{
    setRect(x, y, w, h);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(2);
    setGraphicsEffect(effect);
}

void TileGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;

    path.addRoundedRect(rect(), 20*rect().width()/145, 20*rect().height()/145);

    painter->setPen(color_);
    painter->fillPath(path, color_);
    painter->drawPath(path);

    painter->setFont(QFont("Irish Grover", int(rect().height()/2)));
    painter->setPen(Qt::black);
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

QColor TileGraphicsItem::getColor()
{
    return color_;
}
