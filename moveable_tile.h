#ifndef MOVEABLETILE_H
#define MOVEABLETILE_H

#include "tile_graphics_item.h"

class MoveableTile : public TileGraphicsItem
{   
public:
    MoveableTile(QRectF rect, QString text, QColor color, QPixmap image, bool *show_numbers_ptr, bool image_mode = false);
    MoveableTile(int x, int y, int w, int h, QString text, QColor color, QPixmap image, bool *show_numbers_ptr, bool image_mode = false);
    bool move(QRectF empty_space_rect, bool &animation_played);
    QString toString();
};

#endif // MOVEABLETILE_H
