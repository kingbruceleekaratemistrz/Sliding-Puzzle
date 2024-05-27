#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QGraphicsScene>
#include <QList>

#include "my_button.h"

class MainMenuScene : public QGraphicsScene
{
private:
    QList<MyButton *> buttons_;
public:
    MainMenuScene(int x, int y, int w, int h);
    MyButton *getButton(int i);

    enum { BUTTON_CONTINUE, BUTTON_NEW_GAME, BUTTON_LEADERSHIP, BUTTON_SETTINGS, BUTTON_EXIT };
};

#endif // MAINMENUSCENE_H
