#include "moveable_tile.h"


MoveableTile::MoveableTile(QRectF rect, QString text) : TileGraphicsItem(rect, text)
{
}

MoveableTile::MoveableTile(int x, int y, int w, int h, QString text) : TileGraphicsItem(x, y, w, h, text)
{
}


bool MoveableTile::move(QRectF empty_space)
{
    qDebug() << "Klik na ruszalny kafel";
    qDebug() << "x: " << empty_space.x() << "; y: " << empty_space.y();
    //setPos(coords);
    setRect(empty_space);
    return true;
}

QString MoveableTile::toString()
{
    return QString("Moveable Tile num: " + getText());
}
