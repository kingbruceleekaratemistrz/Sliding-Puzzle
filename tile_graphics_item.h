#ifndef TILEGRAPHICSITEM_H
#define TILEGRAPHICSITEM_H

#include <QObject>
#include <QRectF>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class TileGraphicsItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
    Q_PROPERTY(QRectF rect READ rect WRITE setRect)
private:
    QColor color_;
    QString text_;
    QPixmap image_;
    bool image_mode_;
    bool *show_numbers_ptr_;
public:
    TileGraphicsItem(QRectF rect, QString text, QColor color, QPixmap image, bool *show_numbers_ptr, bool image_mode = false);
    TileGraphicsItem(int x, int y, int w, int h, QString text, QColor color, QPixmap image,  bool *show_numbers_ptr, bool image_mode = false);
    QString getText();
    QColor getColor();
    QPixmap getImage();
    bool getImageMode();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);    
    virtual bool move(QRectF empty_space_rect, bool &animation_played) = 0;
    virtual QString toString() = 0;
public slots:
    void onUpdate();
signals:
    void click();
};

#endif // TILEGRAPHICSITEM_H
