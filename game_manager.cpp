#include "game_manager.h"

#include <QApplication>
#include <QSettings>
#include <QTimer>

#include "main_menu_scene.h"
#include "leadership_scene.h"
#include "settings_scene.h"
#include "game_scene.h"
#include "end_scene.h"
#include "score_parser.h"

GameManager::GameManager() : board_(new Board())
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

bool GameManager::loadGameState(std::vector<int> &tiles_values, int &board_size, int &move_count, int &time_count)
{
    QFile file("./gamestate");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    bool *ok = new bool;
    QTextStream in(&file);
    QStringList list = in.readLine().split(u';');
    board_size = list.at(0).toInt(ok);
    if (!ok)
        return false;
    move_count = list.at(1).toInt(ok);
    if (!ok)
        return false;
    time_count = list.at(2).toInt(ok);
    if (!ok)
        return false;

    list = in.readLine().split(u';');
    for (auto &val : list)
    {
        int num = val.toInt(ok);
        if (!ok || num < 0 || num > board_size*board_size)
            return false;

        tiles_values.push_back(num);
    }

    return true;
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
    if (settings.value("boardsize").toInt() != board_->getSize())
        board_->setSize(settings.value("boardsize").toInt());
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
    if (!settings.contains("image"))
        settings.setValue("image", 1);
    if (!settings.contains("numofimages"))
        settings.setValue("numofimages", 2);
}

void GameManager::setEndScene(QPixmap background, QPoint result)
{
    EndScene *new_scene = new EndScene(QPointF(view_->width(), view_->height()), background, result);
    connect(new_scene->getButton(EndScene::NEW_GAME), SIGNAL(click()), this, SLOT(setGameScene()));
    connect(new_scene->getButton(EndScene::BACK_TO_MENU), SIGNAL(click()), this, SLOT(setMenuScene()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    prev_scene->deleteLater();
}

void GameManager::setMenuScene()
{
    reload();

    MainMenuScene *new_scene = new MainMenuScene(QPointF(view_->width(), view_->height()));
    connect(new_scene->getButton(MainMenuScene::BUTTON_CONTINUE), SIGNAL(click()), this, SLOT(setContinueGameScene()));
    connect(new_scene->getButton(MainMenuScene::BUTTON_NEW_GAME), SIGNAL(click()), this, SLOT(setGameScene()));
    connect(new_scene->getButton(MainMenuScene::BUTTON_LEADERSHIP), SIGNAL(click()), this, SLOT(setLeadershipScene()));
    connect(new_scene->getButton(MainMenuScene::BUTTON_SETTINGS), SIGNAL(click()), this, SLOT(setSettingsScene()));
    connect(new_scene->getButton(MainMenuScene::BUTTON_EXIT), SIGNAL(click()), QApplication::instance(), SLOT(quit()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    prev_scene->deleteLater();
}

void GameManager::setSettingsScene()
{
    SettingsScene *new_scene = new SettingsScene(QPointF(view_->width(), view_->height()));
    connect(new_scene->getButton(SettingsScene::EXIT), SIGNAL(click()), this, SLOT(setMenuScene()));
    connect(new_scene->getButton(SettingsScene::SAVE_AND_EXIT), SIGNAL(click()), this, SLOT(setMenuScene()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);    
    prev_scene->deleteLater();
}

void GameManager::setGameScene()
{
    board_->initializeNewGame();
    GameScene *new_scene = new GameScene(QPointF(view_->width(), view_->height()), board_->getSize(), board_->getTilesValues());
    connect(new_scene, SIGNAL(playMove(int)), this, SLOT(movePlayed(int)));
    connect(new_scene->getButton(), &MyButton::click, this, [this]{ saveGameState(static_cast<GameScene*>(view_->scene())->getResult()); });
    connect(new_scene->getButton(), SIGNAL(click()), this, SLOT(setMenuScene()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    prev_scene->deleteLater();
}

void GameManager::setContinueGameScene()
{
    int board_size, move_count, time_count;
    std::vector<int> tiles_values;
    bool load_succcess = loadGameState(tiles_values, board_size, move_count, time_count);

    if (load_succcess)
    {
        board_->setSize(board_size);
        board_->initializeNewGame(tiles_values);
        GameScene *new_scene = new GameScene(QPointF(view_->width(), view_->height()), board_size, tiles_values, time_count, move_count);
        connect(new_scene, SIGNAL(playMove(int)), this, SLOT(movePlayed(int)));
        connect(new_scene->getButton(), &MyButton::click, this, [this]{ saveGameState(static_cast<GameScene*>(view_->scene())->getResult()); });
        connect(new_scene->getButton(), SIGNAL(click()), this, SLOT(setMenuScene()));

        QGraphicsScene *prev_scene = view_->scene();
        view_->setScene(new_scene);
        prev_scene->deleteLater();
    }
    else
    {
        setGameScene();
        return;
    }

}

void GameManager::setLeadershipScene()
{
    LeadershipScene *new_scene = new LeadershipScene(QPoint(view_->width(), view_->height()));
    connect(new_scene->getButton(), SIGNAL(click()), this, SLOT(setMenuScene()));

    QGraphicsScene *prev_scene = view_->scene();
    view_->setScene(new_scene);
    prev_scene->deleteLater();
}

void GameManager::saveGameState(QPoint score)
{
    QFile file("./gamestate");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << board_->getSize() << ";" << score.x() << ";" << score.y() << "\n";

    std::vector<int> tiles_values = board_->getTilesValues();
    for (auto &value : tiles_values)
        out << value << ";";

    file.close();
}

void GameManager::movePlayed(int tile_to_move)
{
    board_->playMove(tile_to_move);    
    if (board_->isSolved() == true)
    {
        QSettings settings("config.ini", QSettings::IniFormat);
        QPoint result = static_cast<GameScene*>(view_->scene())->getResult();
        ScoreParser::saveScore(settings.value("username").toString(), result, board_->getSize());

        QTimer timer;
        timer.singleShot(150, [this]{ setEndScene(view_->grab(), static_cast<GameScene*>(view_->scene())->getResult()); });
    }
}
