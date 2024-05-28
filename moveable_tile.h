#ifndef MOVEABLETILE_H
#define MOVEABLETILE_H

#include "tile_graphics_item.h"

class MoveableTile : public TileGraphicsItem
{   
public:
    MoveableTile(QRectF rect, QString text);
    MoveableTile(int x, int y, int w, int h, QString text);
    bool move(QRectF empty_space_rect, bool &animation_played);
    QString toString();
};

#endif // MOVEABLETILE_H
