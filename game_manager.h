#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QGraphicsView>

#include "board.h"

class GameManager : public QObject
{
    Q_OBJECT
private:
    Board *board_;
    QGraphicsView *view_;

public:
    GameManager();
    ~GameManager();
private:
    void reload();
    void initSettings();
    void setEndScene(QPixmap background, QPoint result);
private slots:
    void setMenuScene();
    void setSettingsScene();
    void setGameScene();
    void setContinueGameScene();
    void setLeadershipScene();
    void saveGameState(QPoint score);
public slots:    
    void movePlayed(int tile_to_move);
};

#endif // GAMEMANAGER_H
