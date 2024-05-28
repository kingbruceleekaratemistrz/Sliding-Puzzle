#include "moveable_tile.h"

#include <QPropertyAnimation>

MoveableTile::MoveableTile(QRectF rect, QString text) : TileGraphicsItem(rect, text)
{    
}

MoveableTile::MoveableTile(int x, int y, int w, int h, QString text) : TileGraphicsItem(x, y, w, h, text)
{
}


bool MoveableTile::move(QRectF empty_tile_rect, bool &animation_played)
{
    qDebug() << "Klik na ruszalny kafel";
    qDebug() << "x: " << empty_tile_rect.x() << "; y: " << empty_tile_rect.y();

    QPropertyAnimation *anim = new QPropertyAnimation(this, "rect");
    anim->setDuration(125);
    anim->setStartValue(rect());
    anim->setEndValue(empty_tile_rect);
    connect(anim, &QAbstractAnimation::finished, this, [&animation_played]{ animation_played = false; });
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    return true;
}

QString MoveableTile::toString()
{
    return QString("Moveable Tile num: " + getText());
}
