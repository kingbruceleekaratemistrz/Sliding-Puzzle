#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QObject>
#include <QRectF>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class TileGraphicsItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    QString text_;
public:
    TileGraphicsItem(QRectF rect, QString text);
    TileGraphicsItem(int x, int y, int w, int h, QString text);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QString getText();
    virtual bool move(QRectF empty_space) = 0;
    virtual QString toString() = 0;
signals:
    void click();
};

#endif // TILEGRAPHICSITEM_H
