#include "end_scene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>

EndScene::EndScene(QPointF resolution, QPixmap background)
{
    setSceneRect(0, 0, resolution.x(), resolution.y());
    qreal sx = resolution.x()/1920.0;
    qreal sy = resolution.y()/1080.0;

    QGraphicsPixmapItem *pixmap_item = new QGraphicsPixmapItem(background);
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
    pixmap_item->setGraphicsEffect(effect);
    addItem(pixmap_item);

    // nowa klasa rounded rect
    // dodac labele "Gratulacje Player", "Liczba ruchów", "Czas"
    // dodac buttony "wróc do menu", "nowa gra"
}
