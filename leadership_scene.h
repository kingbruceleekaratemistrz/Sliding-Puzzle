#ifndef LEADERSHIPSCENE_H
#define LEADERSHIPSCENE_H

#include <QGraphicsScene>

#include "my_button.h"

class LeadershipScene : public QGraphicsScene
{
private:
    MyButton *exit_button_;
public:
    LeadershipScene(int x, int y, int w, int h);
    MyButton *getButton();
};

#endif // LEADERSHIPSCENE_H
