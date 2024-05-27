#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <QGraphicsScene>

#include "my_button.h"

class SettingsScene : public QGraphicsScene
{
private:
    MyButton *exit_button_;
public:
    SettingsScene(int x, int y, int w, int h);
    MyButton *getButton();
};

#endif // SETTINGSSCENE_H
