#include "immoveable_tile.h"

#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>

ImmoveableTile::ImmoveableTile(QRectF rect, QString text)
    : TileGraphicsItem(rect, text)
{
}

ImmoveableTile::ImmoveableTile(int x, int y, int w, int h, QString text)
    : TileGraphicsItem(x, y, w, h, text)
{
}

bool ImmoveableTile::move(QRectF empty_tile_rect, bool &animation_played)
{    
    qDebug() << "Klik na nieruszalny kafel";

    QRectF rect_moved_right = rect();
    rect_moved_right.moveLeft(rect_moved_right.x()+15);
    QRectF rect_moved_left = rect();
    rect_moved_left.moveLeft(rect_moved_left.x()-15);

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

QString ImmoveableTile::toString()
{
    return QString("Immoveable Tile num: " + getText());
}
