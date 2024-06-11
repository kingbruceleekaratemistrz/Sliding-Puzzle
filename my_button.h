#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MyButton : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    QString text_ = "";
public:
    MyButton(QRectF rect, QString text);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
signals:
    void click();
};

#endif // MYBUTTON_H
