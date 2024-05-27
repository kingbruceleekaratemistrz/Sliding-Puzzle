#include "main_menu_scene.h"

MainMenuScene::MainMenuScene(int x, int y, int w, int h)
{
    setSceneRect(x, y, w, h);
    addItem(new QGraphicsPixmapItem(QPixmap("./assets/main_menu/background.png")));
    for (int i = 0; i < 5; i++)
    {
        QString path = QString::fromStdString("./assets/main_menu/button"+std::to_string(i+1)+".png");
        buttons_.push_back(new MyButton(path, 460, 280 + 80*i));
        addItem(buttons_[i]);
    }
}

MyButton *MainMenuScene::getButton(int i)
{
    return buttons_[i];
}

