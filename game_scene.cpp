#include "game_scene.h"

#include <QTransform>
#include "tile_graphics_item.h"
#include "moveable_tile.h"
#include "immoveable_tile.h"

GameScene::GameScene(int x, int y, int w, int h, int size, std::vector<int> tiles_values) : board_size_(size)
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

    empty_tile_ = QRect(390+(size-1)*tile_offset_, 100+(size-1)*tile_offset_, tile_size_, tile_size_);
}

void GameScene::moveTile()
{
    TileGraphicsItem *tile = static_cast<TileGraphicsItem*>(QObject::sender());

    QRectF prev_rect = tile->rect();
    qDebug() << "x: " << tile->rect().x() << "; y: " << tile->rect().y() << "; num: " << tile->getText();

    if (tile->move(empty_tile_))
    {
        empty_tile_ = prev_rect;
        // [x | y][north | west | east | south]
        int offsets[2][4] = { {0, -tile_offset_, tile_offset_, 0}, {-tile_offset_, 0, 0, tile_offset_} };
        for (int i = 0; i < 4; i++)
        {
            TileGraphicsItem *prev_neighb = static_cast<TileGraphicsItem*>(this->itemAt(prev_rect.x()+offsets[0][i], prev_rect.y()+offsets[1][i], QTransform()));
            if (prev_neighb != nullptr && prev_neighb != tile)
            {
                qDebug() << "Były sąsiad: " << prev_neighb->getText() << " zamieniany na ruszalnego";
                QRectF rect = prev_neighb->rect();
                QString text = prev_neighb->getText();
                delete prev_neighb;

                MoveableTile *tmp_tile = new MoveableTile(rect, text);
                addItem(tmp_tile);
                connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
            }

            TileGraphicsItem *curr_neighb = static_cast<TileGraphicsItem*>(this->itemAt(tile->rect().x()+offsets[0][i], tile->rect().y()+offsets[1][i], QTransform()));
            if (curr_neighb != nullptr)
            {
                qDebug() << "Nowy sąsiad: " << curr_neighb->getText() << " zamieniany na nieruszalnego";
                QRectF rect = curr_neighb->rect();
                QString text = curr_neighb->getText();
                delete curr_neighb;

                ImmoveableTile *tmp_tile = new ImmoveableTile(rect, text);
                addItem(tmp_tile);
                connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
            }
        }
    }


    // TileGraphicsItem *neighb = static_cast<TileGraphicsItem*>(this->itemAt(x, y-tile_offset_, QTransform()));
    // if (neighb == nullptr)
    //     qDebug() << "Brak górnego sąsiada";
    // else
    //     qDebug() << "Górny sąsiad: " << neighb->getText();

    // neighb = static_cast<TileGraphicsItem*>(this->itemAt(x-tile_offset_, y, QTransform()));
    // if (neighb == nullptr)
    //     qDebug() << "Brak lewego sąsiada";
    // else
    //     qDebug() << "Lewy sąsiad: " << neighb->getText();

    // neighb = static_cast<TileGraphicsItem*>(this->itemAt(x+tile_offset_, y, QTransform()));
    // if (neighb == nullptr)
    //     qDebug() << "Brak prawego sąsiada";
    // else
    //     qDebug() << "Prawy sąsiad: " << neighb->getText();

    // neighb = static_cast<TileGraphicsItem*>(this->itemAt(x, y+tile_offset_, QTransform()));
    // if (neighb == nullptr)
    //     qDebug() << "Brak dolnego sąsiada";
    // else
    //     qDebug() << "Dolny sąsiad: " << neighb->getText();
}
