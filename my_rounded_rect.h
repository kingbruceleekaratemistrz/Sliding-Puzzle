#ifndef MYROUNDEDRECT_H
#define MYROUNDEDRECT_H

#include <QGraphicsRectItem>
#include <QBrush>

class MyRoundedRect : public QGraphicsRectItem
{
private:
    int arc_;
    QBrush brush_;
public:
    MyRoundedRect(QRectF rect, QBrush brush, int arc);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // MYROUNDEDRECT_H
