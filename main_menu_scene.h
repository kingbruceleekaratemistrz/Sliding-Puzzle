#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include <QGraphicsScene>
#include <QList>

#include "my_pixmap_button.h"

class MainMenuScene : public QGraphicsScene
{
private:
    QList<MyPixmapButton *> buttons_;
public:
    MainMenuScene(QPoint resolution);
    MyPixmapButton *getButton(int i);

    enum { BUTTON_CONTINUE, BUTTON_NEW_GAME, BUTTON_LEADERSHIP, BUTTON_SETTINGS, BUTTON_EXIT };
};

#endif // MAINMENUSCENE_H
