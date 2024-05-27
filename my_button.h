#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

class MyButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    MyButton(QString path, int x, int y);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void click();
};

#endif // MYBUTTON_H
