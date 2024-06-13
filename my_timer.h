#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QGraphicsRectItem>

class MyTimer : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int min_;
    int sec_;
    int font_size_;
    QTimer *timer_;
public:
    MyTimer(QRectF rect, int font_size = -1);
    ~MyTimer();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    int getTime();
public slots:
    void inc();
};

#endif // MYTIMER_H
