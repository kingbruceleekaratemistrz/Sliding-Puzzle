#include "game_manager.h"
#include <QApplication>

GameManager::GameManager(int size) : board_(new Board(size))
{
    view_ = new QGraphicsView();
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setWindowState(Qt::WindowFullScreen);

    qDebug() << QPoint(view_->width(), view_->height());
    main_menu_scene_ = new MainMenuScene(QPoint(view_->width(), view_->height()));
    leadership_scene_ = new LeadershipScene(QPoint(view_->width(), view_->height()));
    settings_scene_ = new SettingsScene(QPoint(view_->width(), view_->height()));

    // connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_CONTINUE), SIGNAL(click()), this, SLOT());
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_NEW_GAME), SIGNAL(click()), this, SLOT(startNewGame()));
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_LEADERSHIP), &MyPixmapButton::click, this, [this]{ view_->setScene(leadership_scene_); });
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_SETTINGS), &MyPixmapButton::click, this, [this]{ view_->setScene(settings_scene_); });
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_EXIT), SIGNAL(click()), QApplication::instance(), SLOT(quit()));
    // connect(leadership_scene_->getButton(), &MyButton::click, this, [this]{ view_->setScene(main_menu_scene_); });
    connect(settings_scene_->getButtons()[1], &MyButton::click, this, [this]{ view_->setScene(main_menu_scene_); });


    //view_->setFixedSize(res_.x(), res_.y());
    view_->setScene(main_menu_scene_    );
    view_->show();
}

GameManager::~GameManager()
{
    delete board_;
    delete main_menu_scene_;
    delete leadership_scene_;
    delete settings_scene_;
    delete game_scene_;
}

void GameManager::startNewGame()
{
    board_->initializeNewGame();
    game_scene_ = new GameScene(QPoint(view_->width(), view_->height()), board_->getSize(), board_->getTilesValues());
    connect(game_scene_, SIGNAL(playMove(int)), this, SLOT(movePlayed(int)));
    view_->setScene(game_scene_);
}

void GameManager::movePlayed(int tile_to_move)
{
    qDebug() << "Poruszono kafel: " << tile_to_move;
    board_->playMove(tile_to_move);
    if (board_->isSolved() == true)
        qDebug() << "Wygrałeś koleżko!!!";
}
