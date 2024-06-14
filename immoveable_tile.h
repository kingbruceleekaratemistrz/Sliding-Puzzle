#ifndef IMMOVEABLETILE_H
#define IMMOVEABLETILE_H

#include "tile_graphics_item.h"

class ImmoveableTile : public TileGraphicsItem
{    
public:
    ImmoveableTile(QRectF rect, QString text, QColor color, QPixmap image, bool *show_numbers_ptr, bool image_mode = false);    
    bool move(QRectF empty_space_rect, bool &animation_played);    
};

#endif // IMMOVEABLETILE_H
