#ifndef LEADERSHIPSCENE_H
#define LEADERSHIPSCENE_H

#include <QGraphicsScene>

#include "my_pixmap_button.h"

class LeadershipScene : public QGraphicsScene
{
private:
    MyPixmapButton *exit_button_;
public:
    LeadershipScene(QPoint resolution);
    MyPixmapButton *getButton();
};

#endif // LEADERSHIPSCENE_H
