#ifndef MYLABEL_H
#define MYLABEL_H

#include <QGraphicsRectItem>

class MyLabel : public QGraphicsRectItem
{
private:
    int font_size_;
    int align_flag_;
    QString text_;
public:
    MyLabel(QRectF rect, QString text, int align_flag, int font_size = -1);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QString text();
    void setText(QString text);
};

#endif // MYLABEL_H
