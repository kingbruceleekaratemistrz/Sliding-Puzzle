#ifndef MYTEXTBOX_H
#define MYTEXTBOX_H

#include <QGraphicsTextItem>

class MyTextBox : public QGraphicsTextItem
{
private:
    int arc_;
    qreal sc_;
    QRectF rect_;
public:
    MyTextBox(QRectF rect, QString text, int font_size, int arc);
    void keyPressEvent(QKeyEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;
};

#endif // MYTEXTBOX_H
