#include "game_scene.h"

#include <QPainter>
#include <QTransform>
#include <QTimer>
#include "tile_graphics_item.h"
#include "moveable_tile.h"
#include "immoveable_tile.h"
#include "my_label.h"

GameScene::GameScene(QPointF resolution, int size, std::vector<int> tiles_values)
    : board_size_(size), animation_played_(false)
{
    setSceneRect(0, 0, resolution.x(), resolution.y());
    setBackgroundBrush(QImage("./assets/game/background.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    qreal sc = resolution.x()/1920.0;

    button_ = new MyButton(QRectF(50*sc, 50*sc, 250*sc, 40*sc), "Wróć do menu", 23*sc);
    addItem(button_);

    QGraphicsPixmapItem *move_count_pixmap = new QGraphicsPixmapItem(QPixmap("./assets/game/piece.png").scaled(62*sc, 50*sc, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    move_count_pixmap->setPos(width()-270*sc, 123*sc);
    addItem(move_count_pixmap);
    move_count_ = 0;
    move_count_label_ = new MyLabel(QRectF(width()-200*sc, 120*sc, 200*sc, 70*sc), "0", 40*sc);
    addItem(move_count_label_);

    int break_len = 40*sc/size;
    tile_size_ = (750*sc - break_len * (size - 1)) / size;
    tile_offset_ = tile_size_ + break_len;

    QColor colors[19] = {
        QColor(42, 51, 133),
        QColor(50, 59, 139),
        QColor(59, 67, 146),
        QColor(67, 75, 152),
        QColor(76, 84, 159),
        QColor(84, 92, 165),
        QColor(93, 100, 172),
        QColor(101, 108, 178),
        QColor(110, 117, 185),
        QColor(118, 125, 191),
        QColor(127, 133, 198),
        QColor(135, 142, 204),
        QColor(144, 150, 211),
        QColor(152, 158, 217),
        QColor(161, 166, 224),
        QColor(169, 175, 230),
        QColor(178, 183, 237),
        QColor(186, 191, 243),
        QColor(195, 199, 250)
    };

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == size-1 && j == size-1)
                continue;

            int tile_value = tiles_values[i*size+j];
            QColor color;

            if (size > 2)
            {
                int color_index = (((tile_value-1)%size) < int((tile_value-1)/size)) ? (tile_value-1)%size : int((tile_value-1)/size);
                color = colors[int(color_index*18/(size-2))];
            }
            else
                color = colors[0];

            TileGraphicsItem *tmp_tile;
            if ((i == size-1 && j == size-2) || (i == size-2 && j == size-1))
                tmp_tile = new MoveableTile(585*sc+ j*tile_offset_, 150*sc + i*tile_offset_, tile_size_, tile_size_, QString::number(tiles_values[i*size+j]), color);
            else
                tmp_tile = new ImmoveableTile(585*sc+ j*tile_offset_, 150*sc + i*tile_offset_, tile_size_, tile_size_, QString::number(tiles_values[i*size+j]), color);
            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
        }
    }

    empty_tile_rect_ = QRect(585*sc+(size-1)*tile_offset_, 150*sc+(size-1)*tile_offset_, tile_size_, tile_size_);

    QGraphicsPixmapItem *timer_pixmap = new QGraphicsPixmapItem(QPixmap("./assets/game/clock.png").scaled(50*sc, 50*sc, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    timer_pixmap->setPos(width()-260*sc, 57*sc);
    addItem(timer_pixmap);
    timer_ = new MyTimer(QRectF(width()-200*sc, 50*sc, 200*sc, 70*sc), 40*sc);
    addItem(timer_);
}

MyButton* GameScene::getButton()
{
    return button_;
}

QPoint GameScene::getResult()
{
    return QPoint(move_count_, timer_->getTime());
}

std::vector<TileGraphicsItem*> GameScene::findNeighbors(QRectF rect)
{
    qreal x_offsets[4] = { 0, -tile_offset_, tile_offset_, 0 };
    qreal y_offsets[4] = { -tile_offset_, 0, 0, tile_offset_ };
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
            QColor tmp_color = tile->getColor();
            delete tile;
            MoveableTile *tmp_tile = new MoveableTile(tmp_rect, tmp_text, tmp_color);
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
            QColor tmp_color = tile->getColor();
            delete tile;
            ImmoveableTile *tmp_tile = new ImmoveableTile(tmp_rect, tmp_text, tmp_color);
            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
        }

        empty_tile_rect_ = rect_before_move;
        move_count_++;
        move_count_label_->setText(QString::number(move_count_label_->text().toInt()+1));
    }
}
