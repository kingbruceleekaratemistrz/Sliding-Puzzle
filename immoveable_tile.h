#ifndef IMMOVEABLETILE_H
#define IMMOVEABLETILE_H

#include "tile_graphics_item.h"

class ImmoveableTile : public TileGraphicsItem
{    
public:
    ImmoveableTile(QRectF rect, QString text, QColor color);
    ImmoveableTile(int x, int y, int w, int h, QString text, QColor color);
    bool move(QRectF empty_space_rect, bool &animation_played);
    QString toString();
};

#endif // IMMOVEABLETILE_H
