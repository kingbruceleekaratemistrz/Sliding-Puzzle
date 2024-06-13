#ifndef ENDSCENE_H
#define ENDSCENE_H

#include <QObject>
#include <QGraphicsScene>

class EndScene : public QGraphicsScene
{
public:
    EndScene(QPointF resolution, QPixmap background);
};

#endif // ENDSCENE_H
