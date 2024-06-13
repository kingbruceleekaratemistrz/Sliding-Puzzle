#include "end_scene.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>
#include <QSettings>
#include <QLinearGradient>

#include "my_label.h"
#include "my_button.h"
#include "my_rounded_rect.h"

EndScene::EndScene(QPointF resolution, QPixmap background, QPoint result)
{
    setSceneRect(0, 0, resolution.x(), resolution.y());
    qreal sx = resolution.x()/1920.0;
    qreal sy = resolution.y()/1080.0;

    QGraphicsPixmapItem *pixmap_item = new QGraphicsPixmapItem(background);
    QGraphicsBlurEffect *effect = new QGraphicsBlurEffect();
    effect->setBlurRadius(30);
    pixmap_item->setGraphicsEffect(effect);
    addItem(pixmap_item);

    QSettings settings("config.ini", QSettings::IniFormat);
    QLinearGradient gradient(480*sx, 290*sy, 480*sx, 500*sy);
    gradient.setColorAt(0, QColor(109, 133, 255));
    gradient.setColorAt(1, QColor(29, 69, 172));
    addItem(new MyRoundedRect(QRectF(510*sx, 290*sy, 900*sx, 500*sy), QBrush(gradient), 20*sx));

    QString credit_text = "Gratulacje "+settings.value("username").toString()+"!";
    addItem(new MyLabel(QRectF(510*sx, 321*sy, 900*sx, 75*sy), credit_text, Qt::AlignCenter, 45*sy));
    QString move_count_text = "Liczba ruchów: "+QString::number(result.x());
    addItem(new MyLabel(QRectF(510*sx, 412*sy, 900*sx, 75*sy), move_count_text, Qt::AlignCenter, 45*sy));
    QString time_count_text = "Czas: "+QString::number(int(result.y()/60)).rightJustified(2, '0')+":"+QString::number(result.y()%60).rightJustified(2, '0');
    addItem(new MyLabel(QRectF(510*sx, 503*sy, 900*sx, 75*sy), time_count_text, Qt::AlignCenter, 45*sy));

    buttons_.push_back(new MyButton(QRectF(610*sx, 650*sy, 300*sx, 50*sy), "Nowa gra", 30*sy));
    addItem(buttons_.at(0));
    buttons_.push_back(new MyButton(QRectF(1010*sx, 650*sy, 300*sx, 50*sy), "Powrót do menu", 30*sy));
    addItem(buttons_.at(1));
}

MyButton* EndScene::getButton(int i)
{
    return buttons_.at(i);
}
