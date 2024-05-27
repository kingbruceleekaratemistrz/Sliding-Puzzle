#include "view_board.h"

#include <QDebug>

#include <QGraphicsScene>
#include <QGraphicsView>

View_Board::View_Board()
{
    setRect(50, 50, 100, 100);
}

View_Board::View_Board(int x, int y, int w, int h)
{
    setRect(x, y, w, h);
}

void View_Board::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Wykryto klik";

    emit click();
}

// void Renderer::mousePressEvent(QMouseEvent *event)
// {
//     if (current_view_->scene() == main_menu_)
//     {
//         current_view_->setScene(game_);
//         qDebug() << "Zmiana na game_";
//     }
//     else
//     {
//         current_view_->setScene(main_menu_);
//         qDebug() << "Zmiana na main_menu_";
//     }
// }
