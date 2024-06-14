#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QObject>
#include <QGraphicsScene>
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
    bool *show_numbers_ptr_;
    bool show_numbers_hold_;
    qreal board_size_;
    qreal tile_size_;
    qreal tile_offset_;
    QRectF empty_tile_rect_;
    MyButton *back_to_menu_button_;
    int move_count_;
    MyLabel *move_count_label_;
    MyTimer *timer_;

    static QColor colors[19];
public:
    GameScene(QPointF resolution, int size, std::vector<int> tiles_values, int time_count = 0, int move_count = 0);
    ~GameScene();
    MyButton *getButton();
    QPoint getResult();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    std::vector<TileGraphicsItem*> findNeighbors(QRectF rect);
    bool isNeighborOfEmptyTile(int r, int c, int er, int ec);
    void loadPixmaps(qreal sx, qreal sy, int move_count, int time_count);
    void loadTiles(qreal sx, qreal sy, std::vector<int> &tiles_values, int size);
    QList<QPixmap> loadImages();
public slots:
    void moveTile();    
signals:
    void playMove(int tile_to_move);
    void updateTiles();
};

#endif // GAMESCENE_H
