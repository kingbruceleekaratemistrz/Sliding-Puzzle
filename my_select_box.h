#ifndef MYSELECTBOX_H
#define MYSELECTBOX_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MySelectBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int val_;
    const int kMin_, kMax_;
    int format_;
    int font_size_;
    int arc_;
public:
    enum { BOARD_SIZE, TIME, PAGES };

    MySelectBox(QRectF rect, int format, int min, int max, int val, int font_size, int arc);
    void setVal(int val);
    int val();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void click();
};

#endif // MYSELECTBOX_H
