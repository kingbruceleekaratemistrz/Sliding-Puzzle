#ifndef VIEW_BOARD_H
#define VIEW_BOARD_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class View_Board : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    View_Board();
    View_Board(int x, int y, int w, int h);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
signals:
    void click();
};

#endif // VIEW_BOARD_H
