#ifndef MYPIXMAPBUTTON_H
#define MYPIXMAPBUTTON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class MyPixmapButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MyPixmapButton(QPixmap pixmap, qreal x, qreal y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void click();
};

#endif // MYPIXMAPBUTTON_H
