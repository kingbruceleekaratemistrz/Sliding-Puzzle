#include "my_button.h"

#include <QDebug>

MyButton::MyButton(QString path, int x, int y) : QGraphicsPixmapItem(QPixmap(path))
{
    setPos(x, y);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

void MyButton::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Klik!";
    emit click();
}
