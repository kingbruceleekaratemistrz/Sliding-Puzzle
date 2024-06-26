#include "immoveable_tile.h"

#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

ImmoveableTile::ImmoveableTile(QRectF rect, QString text, QColor color, QPixmap image, bool *show_numbers_ptr, bool image_mode)
    : TileGraphicsItem(rect, text, color, image, show_numbers_ptr, image_mode)
{
}

bool ImmoveableTile::move(QRectF empty_tile_rect, bool &animation_played)
{        
    QRectF rect_moved_right = rect();
    rect_moved_right.moveLeft(rect_moved_right.x()+rect().width()*0.1);
    QRectF rect_moved_left = rect();
    rect_moved_left.moveLeft(rect_moved_left.x()-rect().width()*0.1);

    QSequentialAnimationGroup *group_anim = new QSequentialAnimationGroup();
    QPropertyAnimation *anim = new QPropertyAnimation(this, "rect");
    anim->setDuration(25);
    anim->setStartValue(rect());
    anim->setEndValue(rect_moved_right);
    group_anim->addAnimation(anim);

    anim = new QPropertyAnimation(this, "rect");
    anim->setDuration(75);
    anim->setStartValue(rect_moved_right);
    anim->setEndValue(rect_moved_left);
    group_anim->addAnimation(anim);

    anim = new QPropertyAnimation(this, "rect");
    anim->setDuration(25);
    anim->setStartValue(rect_moved_left);
    anim->setEndValue(rect());
    group_anim->addAnimation(anim);

    connect(group_anim, &QAbstractAnimation::finished, this, [&animation_played]{ animation_played = false; });
    group_anim->start(QAbstractAnimation::DeleteWhenStopped);

    return false;
}
