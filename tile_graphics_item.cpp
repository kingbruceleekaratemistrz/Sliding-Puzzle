#include "tile_graphics_item.h"

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsDropShadowEffect>

TileGraphicsItem::TileGraphicsItem(QRectF rect, QString text, QColor color, QPixmap image, bool *show_numbers_ptr, bool image_mode)
    : text_(text), color_(color), image_(image), show_numbers_ptr_(show_numbers_ptr), image_mode_(image_mode)
{
    setRect(rect);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(2);
    setGraphicsEffect(effect);
}

TileGraphicsItem::TileGraphicsItem(int x, int y, int w, int h, QString text, QColor color, QPixmap image, bool *show_numbers_ptr, bool image_mode)
    : text_(text), color_(color), image_(image), image_mode_(image_mode), show_numbers_ptr_(show_numbers_ptr)
{
    setRect(x, y, w, h);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(2);
    setGraphicsEffect(effect);
}

void TileGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    if (image_mode_)
    {
        painter->drawPixmap(rect().x(), rect().y(), image_);
        painter->drawRect(rect());
        if (*show_numbers_ptr_)
        {
            painter->setFont(QFont("Irish Grover", int(rect().height()/2)));
            painter->setPen(Qt::black);
            painter->drawText(rect(), Qt::AlignCenter, text_);
        }
    }
    else
    {
        QPainterPath path;

        path.addRoundedRect(rect(), 20*rect().width()/145, 20*rect().height()/145);

        painter->setPen(color_);
        painter->fillPath(path, color_);
        painter->drawPath(path);

        painter->setFont(QFont("Irish Grover", int(rect().height()/2)));
        painter->setPen(Qt::black);
        painter->drawText(rect(), Qt::AlignCenter, text_);
    }
}

void TileGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "!kilK";
    emit click();
}

void TileGraphicsItem::onUpdate()
{
    update();
}

QString TileGraphicsItem::getText()
{
    return text_;
}

QColor TileGraphicsItem::getColor()
{
    return color_;
}

QPixmap TileGraphicsItem::getImage()
{
    return image_;
}

bool TileGraphicsItem::getImageMode()
{
    return image_mode_;
}
