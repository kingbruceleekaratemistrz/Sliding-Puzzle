#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QRectF>
#include <vector>

#include "tile_graphics_item.h"
#include "my_button.h"
#include "my_label.h"
#include "my_timer.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    bool animation_played_;
    qreal board_size_;
    qreal tile_size_;
    qreal tile_offset_;
    QRectF empty_tile_rect_;
    QPixmap *background_;
    MyButton *button_;
    int move_count_;
    MyLabel *move_count_label_;
    MyTimer *timer_;
public:
    GameScene(QPointF resolution, int size, std::vector<int> tiles_values, int time = 0, int move_count = 0);
    MyButton *getButton();
    QPoint getResult();
private:
    std::vector<TileGraphicsItem*> findNeighbors(QRectF rect);
    bool isNeighborOfEmptyTile(int r, int c, int er, int ec);
public slots:
    void moveTile();    
signals:
    void playMove(int tile_to_move);    
};

#endif // GAMESCENE_H
