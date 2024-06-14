#include "game_scene.h"

#include <QSettings>
#include <QPainter>
#include <QTransform>
#include <QTimer>
#include <QKeyEvent>
#include <QFile>

#include "tile_graphics_item.h"
#include "moveable_tile.h"
#include "immoveable_tile.h"
#include "my_label.h"

QColor GameScene::colors[19] = {
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

GameScene::GameScene(QPointF resolution, int board_size, std::vector<int> tiles_values, int time_count, int move_count)
    : board_size_(board_size), animation_played_(false), show_numbers_ptr_(new bool(false))
{
    setSceneRect(0, 0, resolution.x(), resolution.y());
    setBackgroundBrush(QImage("./assets/game/background.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    QSettings settings("./config.ini", QSettings::IniFormat);
    qreal sx = resolution.x()/1920.0;
    qreal sy = resolution.y()/1080.0;

    loadPixmaps(sx, sy, move_count, time_count);

    back_to_menu_button_ = new MyButton(QRectF(50*sx, 50*sy, 250*sx, 40*sy), "Wróć do menu", 23*sy);
    addItem(back_to_menu_button_);

    show_numbers_hold_ = settings.value("showonhold").toBool();

    loadTiles(sx, sy, tiles_values, board_size);
}

QList<QPixmap> GameScene::loadImages()
{
    QSettings settings("./config.ini", QSettings::IniFormat);
    QString path = "./assets/images/"+QString::number(settings.value("image").toInt())+".jpg";
    if (!QFile::exists(path))
        path = "./assets/images/"+QString::number(settings.value("image").toInt())+".png";
    if (!QFile::exists(path))
        path = "./assets/images/1.jpg";

    QPixmap image(path);
    image = image.scaled(tile_size_*board_size_, tile_size_*board_size_, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QList<QPixmap> images;
    for (int i = 0; i < board_size_; i++)
        for (int j = 0; j < board_size_; j++)
        {
            if (i == board_size_-1 && j == board_size_-1)
                continue;
            images.push_back(image.copy(j*tile_size_, i*tile_size_, tile_size_, tile_size_));
        }

    return images;
}

void GameScene::loadTiles(qreal sx, qreal sy, std::vector<int> &tiles_values, int size)
{
    QSettings settings("./config.ini", QSettings::IniFormat);

    int break_len = 40*sx/size;
    tile_size_ = (750*sx - break_len * (size - 1)) / size;
    tile_offset_ = tile_size_ + break_len;

    int empty_tile_index = -1;
    for (auto &value : tiles_values)
    {
        empty_tile_index++;
        if (value == size*size)
            break;

    }
    int empty_tile_row = empty_tile_index / size;
    int empty_tile_col = empty_tile_index % size;
    empty_tile_rect_ = QRect(585*sx+ empty_tile_col*tile_offset_, 150*sy + empty_tile_row*tile_offset_, tile_size_, tile_size_);

    QList<QPixmap> image_sections = loadImages();
    bool image_mode = settings.value("imagemode").toBool();

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            int tile_value = tiles_values[i*size+j];
            if (tile_value == size*size)
                continue;

            QColor color;
            if (size > 2)
            {
                int color_index = (((tile_value-1)%size) < int((tile_value-1)/size)) ? (tile_value-1)%size : int((tile_value-1)/size);
                color = colors[int(color_index*18/(size-2))];
            }
            else
                color = colors[0];

            TileGraphicsItem *tmp_tile;
            if (isNeighborOfEmptyTile(i, j, empty_tile_row, empty_tile_col))
                tmp_tile = new MoveableTile(QRectF(585*sx+ j*tile_offset_, 150*sy + i*tile_offset_, tile_size_, tile_size_), QString::number(tiles_values[i*size+j]), color, image_sections.at(tiles_values[i*size+j]-1), show_numbers_ptr_, image_mode);
            else
                tmp_tile = new ImmoveableTile(QRectF(585*sx+ j*tile_offset_, 150*sy + i*tile_offset_, tile_size_, tile_size_), QString::number(tiles_values[i*size+j]), color, image_sections.at(tiles_values[i*size+j]-1), show_numbers_ptr_, image_mode);

            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
            connect(this, SIGNAL(updateTiles()), tmp_tile, SLOT(onUpdate()));
        }
    }
}

GameScene::~GameScene()
{
    delete show_numbers_ptr_;    
}

void GameScene::loadPixmaps(qreal sx, qreal sy, int move_count, int time_count)
{
    QGraphicsPixmapItem *move_count_pixmap = new QGraphicsPixmapItem(QPixmap("./assets/game/piece.png").scaled(62*sx, 50*sy, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    move_count_pixmap->setPos(width()-270*sx, 123*sy);
    addItem(move_count_pixmap);
    move_count_ = move_count;
    move_count_label_ = new MyLabel(QRectF(width()-200*sx, 120*sy, 200*sx, 70*sy), QString::number(move_count), Qt::AlignLeft, 40*sy);
    addItem(move_count_label_);

    QGraphicsPixmapItem *timer_pixmap = new QGraphicsPixmapItem(QPixmap("./assets/game/clock.png").scaled(50*sx, 50*sy, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    timer_pixmap->setPos(width()-260*sx, 57*sy);
    addItem(timer_pixmap);
    int min = int(time_count/60);
    int sec = time_count%60;
    timer_ = new MyTimer(QRectF(width()-200*sx, 50*sy, 200*sx, 70*sy), min, sec, 40*sy);
    addItem(timer_);
}

bool GameScene::isNeighborOfEmptyTile(int r, int c, int er, int ec)
{
    int nr, nc;
    //north
    if (r == er-1 && c == ec)
        return true;
    //west
    else if (r == er && c == ec-1)
        return true;
    //east
    else if (r == er && c == ec+1)
        return true;
    //south
    else if (r == er+1 && c == ec)
        return true;
    return false;
}

MyButton* GameScene::getButton()
{
    return back_to_menu_button_;
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
        TileGraphicsItem *potential_neighbor = static_cast<TileGraphicsItem*>(this->itemAt(rect.center().x()+x_offsets[i], rect.center().y()+y_offsets[i], QTransform()));
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
            QPixmap tmp_image = tile->getImage();
            bool tmp_image_mode = tile->getImageMode();
            delete tile;
            MoveableTile *tmp_tile = new MoveableTile(tmp_rect, tmp_text, tmp_color, tmp_image, show_numbers_ptr_, tmp_image_mode);
            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
            connect(this, SIGNAL(updateTiles()), tmp_tile, SLOT(onUpdate()));
        }

        std::vector<TileGraphicsItem*> new_neighbors = findNeighbors(empty_tile_rect_);
        for (TileGraphicsItem *tile : new_neighbors)
        {
            if (tile == tile_to_move)
                continue;
            QRectF tmp_rect = tile->rect();
            QString tmp_text = tile->getText();
            QColor tmp_color = tile->getColor();
            QPixmap tmp_image = tile->getImage();
            bool tmp_image_mode = tile->getImageMode();
            delete tile;
            ImmoveableTile *tmp_tile = new ImmoveableTile(tmp_rect, tmp_text, tmp_color, tmp_image, show_numbers_ptr_, tmp_image_mode);
            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
            connect(this, SIGNAL(updateTiles()), tmp_tile, SLOT(onUpdate()));
        }

        empty_tile_rect_ = rect_before_move;
        move_count_++;
        move_count_label_->setText(QString::number(move_count_label_->text().toInt()+1));
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Alt && show_numbers_hold_)
    {
        *show_numbers_ptr_ = true;
        emit updateTiles();
    }
    else
        QGraphicsScene::keyPressEvent(event);

}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Alt)
    {
        if (show_numbers_hold_)
        {
            *show_numbers_ptr_ = false;
            emit updateTiles();
        }
        else
        {
            *show_numbers_ptr_ = !*show_numbers_ptr_;
            emit updateTiles();
        }
    }
    else
        QGraphicsScene::keyReleaseEvent(event);
}
