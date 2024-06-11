#ifndef MYLABEL_H
#define MYLABEL_H

#include <QGraphicsRectItem>

class MyLabel : public QGraphicsRectItem
{
private:
    int font_size_;
    QString text_;
public:    
    MyLabel(QRectF rect, QString text, int font_size = -1);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
};

#endif // MYLABEL_H
