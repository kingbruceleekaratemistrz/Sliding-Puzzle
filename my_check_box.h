#ifndef MYCHECKBOX_H
#define MYCHECKBOX_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MyCheckBox : public QGraphicsRectItem
{    
private:
    bool is_checked_;
public:
    MyCheckBox(QRectF rect);
    bool isChecked();
    void setChecked(bool state);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

};

#endif // MYCHECKBOX_H
