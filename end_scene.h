#ifndef ENDSCENE_H
#define ENDSCENE_H

#include <QGraphicsScene>

#include "my_button.h"

class EndScene : public QGraphicsScene
{
private:
    QList<MyButton*> buttons_;
public:
    EndScene(QPointF resolution, QPixmap background, QPoint result);
    MyButton *getButton(int i);

    enum { NEW_GAME, BACK_TO_MENU };
};

#endif // ENDSCENE_H
