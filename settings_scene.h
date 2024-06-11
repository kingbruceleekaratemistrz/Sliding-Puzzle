#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <QGraphicsScene>

#include "my_button.h"

class SettingsScene : public QGraphicsScene
{
private:
    QList<MyButton*> buttons_;
private:
    QPixmap loadPixmap(QString path, QPoint resolution);    
public:
    SettingsScene(QPoint resolution);
    QList<MyButton*> getButtons();
};

#endif // SETTINGSSCENE_H
