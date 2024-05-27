#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "board.h"
#include "main_menu_scene.h"
#include "leadership_scene.h"
#include "settings_scene.h"
#include "game_scene.h"

class GameManager : public QObject
{
    Q_OBJECT
private:
    Board *board_;
    MainMenuScene *main_menu_scene_;
    GameScene *game_scene_;
    LeadershipScene *leadership_scene_;
    SettingsScene *settings_scene_;
    QGraphicsView *view_;
public:
    GameManager(int size);
    ~GameManager();
public slots:
    void startNewGame();
};

#endif // GAMEMANAGER_H
