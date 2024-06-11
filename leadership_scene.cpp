#include "leadership_scene.h"

LeadershipScene::LeadershipScene(QPoint resolution)
{
    setSceneRect(0, 0, resolution.x(), resolution.y());
    // exit_button_ = new MyButton("./assets/main_menu/button5.png", 460, 540, resolution);
    // addItem(exit_button_);
}

MyPixmapButton *LeadershipScene::getButton()
{
    return exit_button_;
}
