#include "game_manager.h"

#include <QApplication>
#include <QSettings>

#include "main_menu_scene.h"
#include "leadership_scene.h"
#include "settings_scene.h"
#include "game_scene.h"

GameManager::GameManager(int size) : board_(new Board(size))
{
    initSettings();
    QSettings settings("config.ini", QSettings::IniFormat);

    view_ = new QGraphicsView();
    view_->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view_->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    if (settings.value("fullscreen").toBool())
        view_->setWindowState(Qt::WindowFullScreen);
    else
        view_->setFixedSize(1280, 720);

    setMenuScene();
    view_->show();
}

GameManager::~GameManager()
{
    delete board_;
    delete view_;
}

void GameManager::setMenuScene()
{
    reload();

    MainMenuScene *new_scene = new MainMenuScene(QPointF(view_->width(), view_->height()));
    connect(new_scene->getButton(MainMenuScene::BUTTON_NEW_GAME), SIGNAL(click()), this, SLOT(setGameScene()));
    //connect(new_scene->getButton(MainMenuScene::BUTTON_LEADERSHIP))
    connect(new_scene->getButton(MainMenuScene::BUTTON_SETTINGS), SIGNAL(click()), this, SLOT(setSettingsScene()));
    connect(new_scene->getButton(MainMenuScene::BUTTON_EXIT), SIGNAL(click()), QApplication::instance(), SLOT(quit()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    delete prev_scene;
}

void GameManager::setSettingsScene()
{
    SettingsScene *new_scene = new SettingsScene(QPointF(view_->width(), view_->height()));
    connect(new_scene->getButton(SettingsScene::EXIT), SIGNAL(click()), this, SLOT(setMenuScene()));
    connect(new_scene->getButton(SettingsScene::SAVE_AND_EXIT), SIGNAL(click()), this, SLOT(setMenuScene()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    delete prev_scene;
}

void GameManager::setGameScene()
{
    board_->initializeNewGame();
    GameScene *new_scene = new GameScene(QPoint(view_->width(), view_->height()), board_->getSize(), board_->getTilesValues());
    connect(new_scene, SIGNAL(playMove(int)), this, SLOT(movePlayed(int)));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    delete prev_scene;
}

void GameManager::setLeadershipScene()
{
    LeadershipScene *new_scene = new LeadershipScene(QPoint(view_->width(), view_->height()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    delete prev_scene;
}

void GameManager::movePlayed(int tile_to_move)
{
    qDebug() << "Poruszono kafel: " << tile_to_move;
    board_->playMove(tile_to_move);
    if (board_->isSolved() == true)
        qDebug() << "Wygrałeś koleżko!!!";
}

void GameManager::initSettings()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    if (!settings.contains("fullscreen"))
        settings.setValue("fullscreen", true);
    if (!settings.contains("username"))
        settings.setValue("username", "player");
    if (!settings.contains("boardsize"))
        settings.setValue("boardsize", 3);
    if (!settings.contains("maxtime"))
        settings.setValue("maxtime", 0);
    if (!settings.contains("imagemode"))
        settings.setValue("imagemode", false);
    if (!settings.contains("showonhold"))
        settings.setValue("showonhold", true);
}

void GameManager::reload()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    if (settings.value("fullscreen").toBool() && view_->windowState() != Qt::WindowFullScreen)
    {
        view_->setFixedSize(QSize(1920, 1080));
        view_->setWindowState(Qt::WindowFullScreen);

    }
    else if (!settings.value("fullscreen").toBool() && view_->windowState() == Qt::WindowFullScreen)
    {
        view_->setWindowState(Qt::WindowNoState);
        view_->setFixedSize(QSize(1280, 720));
    }
}

// void GameManager::reloadResolution()
// {
//     QSettings settings("config.ini", QSettings::IniFormat);
//     if (settings.value("fullscreen").toBool() && view_->windowState() != Qt::WindowFullScreen)
//     {
//         view_->setFixedSize(QSize(1920, 1080));
//         view_->setWindowState(Qt::WindowFullScreen);

//     }
//     else if (!settings.value("fullscreen").toBool() && view_->windowState() == Qt::WindowFullScreen)
//     {
//         view_->setWindowState(Qt::WindowNoState);
//         view_->setFixedSize(QSize(1280, 720));
//     }

//     initMenuScene();
//     initSettingsScene();
// }

// void GameManager::setSettingsScene()
// {
//     settings_scene_->reload();
//     view_->setScene(settings_scene_);
// }
