#include "my_pixmap_button.h"

MyPixmapButton::MyPixmapButton(QPixmap pixmap, qreal x, qreal y) : QGraphicsPixmapItem(pixmap)
{    
    setPos(x, y);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void MyPixmapButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{    
    emit click();
}
