#include "game_manager.h"
#include <QApplication>

GameManager::GameManager(int size) : board_(new Board(size))
{
    main_menu_scene_ = new MainMenuScene(0, 0, 1280, 720);
    leadership_scene_ = new LeadershipScene(0, 0, 1280, 720);
    settings_scene_ = new SettingsScene(0, 0, 1280, 720);

    // connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_CONTINUE), SIGNAL(click()), this, SLOT());
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_NEW_GAME), SIGNAL(click()), this, SLOT(startNewGame()));
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_LEADERSHIP), &MyButton::click, this, [this]{ view_->setScene(leadership_scene_); });
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_SETTINGS), &MyButton::click, this, [this]{ view_->setScene(settings_scene_); });
    connect(main_menu_scene_->getButton(MainMenuScene::BUTTON_EXIT), SIGNAL(click()), QApplication::instance(), SLOT(quit()));
    connect(leadership_scene_->getButton(), &MyButton::click, this, [this]{ view_->setScene(main_menu_scene_); });
    connect(settings_scene_->getButton(), &MyButton::click, this, [this]{ view_->setScene(main_menu_scene_); });


    view_ = new QGraphicsView(main_menu_scene_);
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setFixedSize(1280, 720);
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
    game_scene_ = new GameScene(0, 0, 1280, 720, board_->getSize(), board_->getTilesValues());
    view_->setScene(game_scene_);
}
