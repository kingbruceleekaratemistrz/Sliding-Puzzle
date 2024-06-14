#include "my_rounded_rect.h"

#include <QPainter>

MyRoundedRect::MyRoundedRect(QRectF rect, QBrush brush, int arc) : brush_(brush)
{
    arc_ = (arc > 1) ? arc : 1;
    setRect(rect);
}

void MyRoundedRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), arc_, arc_);

    painter->setPen(Qt::NoPen);
    painter->fillPath(path, brush_);
    painter->drawPath(path);
}
