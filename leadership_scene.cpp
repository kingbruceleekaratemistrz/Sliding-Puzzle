#include "leadership_scene.h"

LeadershipScene::LeadershipScene(int x, int y, int w, int h)
{
    setSceneRect(x, y, w, h);
    exit_button_ = new MyButton("./assets/main_menu/button5.png", 460, 540);
    addItem(exit_button_);
}

MyButton *LeadershipScene::getButton()
{
    return exit_button_;
}
