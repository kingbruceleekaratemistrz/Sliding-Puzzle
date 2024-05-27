#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QRectF>
#include <vector>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
private:
    int board_size_;
    int tile_size_;
    int tile_offset_;
    QRectF empty_tile_;
public:
    GameScene(int x, int y, int w, int h, int size, std::vector<int> tiles_values);
public slots:
    void moveTile();
};

#endif // GAMESCENE_H
