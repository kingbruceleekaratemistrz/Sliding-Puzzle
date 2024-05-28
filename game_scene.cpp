#include "game_scene.h"

#include <QTransform>
#include "tile_graphics_item.h"
#include "moveable_tile.h"
#include "immoveable_tile.h"

GameScene::GameScene(int x, int y, int w, int h, int size, std::vector<int> tiles_values)
    : board_size_(size), animation_played_(false)
{
    setSceneRect(x, y, w, h);

    int break_len = 10;
    tile_size_ = (500 - break_len * (size - 1)) / size;
    tile_offset_ = tile_size_ + break_len;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == size-1 && j == size-1)
                continue;
            TileGraphicsItem *tmp_tile;
            if ((i == size-1 && j == size-2) || (i == size-2 && j == size-1))
                tmp_tile = new MoveableTile(390+ j*tile_offset_, 100 + i*tile_offset_, tile_size_, tile_size_, QString::number(tiles_values[i*size+j]));
            else
                tmp_tile = new ImmoveableTile(390+ j*tile_offset_, 100 + i*tile_offset_, tile_size_, tile_size_, QString::number(tiles_values[i*size+j]));
            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
        }
    }

    empty_tile_rect_ = QRect(390+(size-1)*tile_offset_, 100+(size-1)*tile_offset_, tile_size_, tile_size_);
}

std::vector<TileGraphicsItem*> GameScene::findNeighbors(QRectF rect)
{
    int x_offsets[4] = { 0, -tile_offset_, tile_offset_, 0 };
    int y_offsets[4] = { -tile_offset_, 0, 0, tile_offset_ };
    std::vector<TileGraphicsItem*> neighbors;
    for (int i = 0; i < 4; i++)
    {
        TileGraphicsItem *potential_neighbor = static_cast<TileGraphicsItem*>(this->itemAt(rect.x()+x_offsets[i], rect.y()+y_offsets[i], QTransform()));
        if (potential_neighbor != nullptr)
            neighbors.push_back(potential_neighbor);
    }
    return neighbors;
}

void GameScene::moveTile()
{
    if (animation_played_ == true)
        return;

    TileGraphicsItem *tile_to_move = static_cast<TileGraphicsItem*>(QObject::sender());
    QRectF rect_before_move = tile_to_move->rect();

    animation_played_ = true;
    if (tile_to_move->move(empty_tile_rect_, animation_played_))
    {
        emit playMove(tile_to_move->getText().toInt());
        std::vector<TileGraphicsItem*> prev_neighbors = findNeighbors(rect_before_move);
        for (TileGraphicsItem *tile : prev_neighbors)
        {
            if (tile == tile_to_move)
                continue;
            QRectF tmp_rect = tile->rect();
            QString tmp_text = tile->getText();
            delete tile;
            MoveableTile *tmp_tile = new MoveableTile(tmp_rect, tmp_text);
            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
        }

        std::vector<TileGraphicsItem*> new_neighbors = findNeighbors(empty_tile_rect_);
        for (TileGraphicsItem *tile : new_neighbors)
        {
            if (tile == tile_to_move)
                continue;
            QRectF tmp_rect = tile->rect();
            QString tmp_text = tile->getText();
            delete tile;
            ImmoveableTile *tmp_tile = new ImmoveableTile(tmp_rect, tmp_text);
            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
        }

        empty_tile_rect_ = rect_before_move;
    }
}
