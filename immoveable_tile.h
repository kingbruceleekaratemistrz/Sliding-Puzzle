#ifndef IMMOVEABLETILE_H
#define IMMOVEABLETILE_H

#include "tile_graphics_item.h"

class ImmoveableTile : public TileGraphicsItem
{
public:
    ImmoveableTile(QRectF rect, QString text);
    ImmoveableTile(int x, int y, int w, int h, QString text);
    bool move(QRectF empty_space);
    QString toString();
};

#endif // IMMOVEABLETILE_H