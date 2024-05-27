#include "immoveable_tile.h"

ImmoveableTile::ImmoveableTile(QRectF rect, QString text) : TileGraphicsItem(rect, text)
{
}

ImmoveableTile::ImmoveableTile(int x, int y, int w, int h, QString text) : TileGraphicsItem(x, y, w, h, text)
{
}

bool ImmoveableTile::move(QRectF empty_space)
{
    qDebug() << "Klik na nieruszalny kafel";
    return false;
}

QString ImmoveableTile::toString()
{
    return QString("Immoveable Tile num: " + getText());
}
