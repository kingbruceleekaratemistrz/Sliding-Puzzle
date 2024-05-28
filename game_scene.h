#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QRectF>
#include <vector>

#include "tile_graphics_item.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    bool animation_played_;
    int board_size_;
    int tile_size_;
    int tile_offset_;
    QRectF empty_tile_rect_;
public:
    GameScene(int x, int y, int w, int h, int size, std::vector<int> tiles_values);
private:
    std::vector<TileGraphicsItem*> findNeighbors(QRectF rect);
public slots:
    void moveTile();
signals:
    void playMove(int tile_to_move);
};

#endif // GAMESCENE_H
