#include "main_menu_scene.h"

MainMenuScene::MainMenuScene(QPoint resolution)
{
    setSceneRect(0, 0, resolution.x(), resolution.y());

    if (resolution != QPoint(1920, 1080))
    {
        QPixmap pixmap("./assets/main_menu/background.png");
        qreal width = pixmap.width() * resolution.x() / 1920;
        qreal height = pixmap.height() * resolution.y() / 1080;
        pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        addItem(new QGraphicsPixmapItem(pixmap));
    }
    else
        addItem(new QGraphicsPixmapItem(QPixmap("./assets/main_menu/background.png")));


    for (int i = 0; i < 5; i++)
    {
        QString path = QString::fromStdString("./assets/main_menu/button"+std::to_string(i+1)+".png");
        QPixmap pixmap(path);
        qreal x = 690;
        qreal y = 420 + i*120;
        if (resolution != QPoint(1920, 1080))
        {
            x = x * resolution.x() / 1920;
            y = y * resolution.y() / 1080;
            qreal width = pixmap.width() * resolution.x() / 1920;
            qreal height = pixmap.height() * resolution.y() / 1080;
            pixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        }
        buttons_.push_back(new MyPixmapButton(pixmap, x, y));
        addItem(buttons_[i]);
    }
}

MyPixmapButton *MainMenuScene::getButton(int i)
{
    return buttons_[i];
}

