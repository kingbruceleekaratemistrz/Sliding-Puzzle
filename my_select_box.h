#ifndef MYSELECTBOX_H
#define MYSELECTBOX_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MySelectBox : public QGraphicsRectItem
{
private:
    int val_;
    const int kMin_, kMax_;
    int format_;
public:
    enum { BOARD_SIZE, TIME };

    MySelectBox(QRectF rect, int format, int min, int max);
    void setVal(int val);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // MYSELECTBOX_H
