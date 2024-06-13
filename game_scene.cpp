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

GameScene::GameScene(QPointF resolution, int size, std::vector<int> tiles_values, int time, int move_count)
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
    move_count_ = move_count;
    move_count_label_ = new MyLabel(QRectF(width()-200*sc, 120*sc, 200*sc, 70*sc), QString::number(move_count), Qt::AlignLeft, 40*sc);
    addItem(move_count_label_);

    QSettings settings("./config.ini", QSettings::IniFormat);

    show_numbers_ptr_ = new bool(false);
    show_numbers_hold_ = settings.value("showonhold").toBool();

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

    int empty_tile_index = -1;
    for (auto &value : tiles_values)
    {
        empty_tile_index++;
        if (value == size*size)
            break;

    }
    int empty_tile_row = empty_tile_index / size;
    int empty_tile_col = empty_tile_index % size;
    empty_tile_rect_ = QRect(585*sc+ empty_tile_col*tile_offset_, 150*sc + empty_tile_row*tile_offset_, tile_size_, tile_size_);



    // wczytywanie obrazu, nazwa brana z settings(config)
    QString path = "./assets/images/"+QString::number(settings.value("image").toInt())+".jpg";
    if (!QFile::exists(path))
        path = "./assets/images/"+QString::number(settings.value("image").toInt())+".png";
    if (!QFile::exists(path))
        path = "./assets/images/1.jpg";

    QPixmap image(path);
    image = image.scaled(tile_size_*board_size_, tile_size_*board_size_, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    bool image_mode = settings.value("imagemode").toBool();
    QList<QPixmap> image_sections;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            image_sections.push_back(image.copy(j*tile_size_, i*tile_size_, tile_size_, tile_size_));

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
                tmp_tile = new MoveableTile(585*sc+ j*tile_offset_, 150*sc + i*tile_offset_, tile_size_, tile_size_, QString::number(tiles_values[i*size+j]), color, image_sections.at(tiles_values[i*size+j]-1), show_numbers_ptr_, image_mode);
            else
                tmp_tile = new ImmoveableTile(585*sc+ j*tile_offset_, 150*sc + i*tile_offset_, tile_size_, tile_size_, QString::number(tiles_values[i*size+j]), color, image_sections.at(tiles_values[i*size+j]-1), show_numbers_ptr_, image_mode);

            addItem(tmp_tile);
            connect(tmp_tile, SIGNAL(click()), this, SLOT(moveTile()));
            connect(this, SIGNAL(updateTiles()), tmp_tile, SLOT(onUpdate()));
        }
    }

    QGraphicsPixmapItem *timer_pixmap = new QGraphicsPixmapItem(QPixmap("./assets/game/clock.png").scaled(50*sc, 50*sc, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    timer_pixmap->setPos(width()-260*sc, 57*sc);
    addItem(timer_pixmap);
    int min = int(time/60);
    int sec = time%60;
    timer_ = new MyTimer(QRectF(width()-200*sc, 50*sc, 200*sc, 70*sc), min, sec, 40*sc);
    addItem(timer_);
}

GameScene::~GameScene()
{
    delete show_numbers_ptr_;
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
        qDebug() << "OFFSETS: "<< x_offsets[i] << ", " << y_offsets[i];
        qDebug() << "COORDS: " << rect.x()+x_offsets[i]<< ", " << rect.y()+y_offsets[i];

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
