#ifndef MYTEXTBOX_H
#define MYTEXTBOX_H

#include <QGraphicsTextItem>

class MyTextBox : public QGraphicsTextItem
{
public:
    MyTextBox(qreal x, qreal y);
    void keyPressEvent(QKeyEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;
};

#endif // MYTEXTBOX_H
