#include "settings_scene.h"
#include "my_label.h"
#include "my_check_box.h"
#include "my_text_box.h"
#include "my_select_box.h"
#include "my_button.h"
#include "my_radio_box.h"


SettingsScene::SettingsScene(QPoint resolution)
{
    setSceneRect(0, 0, resolution.x(), resolution.y());

    qreal scale_x = resolution.x() / 1920;
    qreal scale_y = resolution.y() / 1080;

    QPixmap pixmap = loadPixmap("./assets/settings/background.png", resolution);
    addItem(new QGraphicsPixmapItem(pixmap));

    QRectF tmp_rect = QRectF(715*scale_x, 0, 490*scale_x, 125*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Ustawienia"), 75));

    tmp_rect = QRectF(400*scale_x, 150*scale_y, 400*scale_x, 75*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Ustawienia aplikacji"), 34));

    tmp_rect = QRectF(460*scale_x, 230*scale_y, 167*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Pełny ekran"), 23));

    tmp_rect = QRectF(400*scale_x, 290*scale_y, 400*scale_x, 75*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Ustawienia gry"), 34));

    tmp_rect = QRectF(460*scale_x, 370*scale_y, 400*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Domyślna nazwa gracza"), 23));       

    tmp_rect = QRectF(460*scale_x, 420*scale_y, 400*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Domyślny rozmiar planszy"), 23));

    tmp_rect = QRectF(460*scale_x, 470*scale_y, 400*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Domyślny maksymalny czas"), 23));

    tmp_rect = QRectF(460*scale_x, 520*scale_y, 220*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Motyw kolorów"), 23));

    tmp_rect = QRectF(460*scale_x, 570*scale_y, 220*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Motyw kafelków"), 23));

    tmp_rect = QRectF(460*scale_x, 620*scale_y, 230*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Tryb obrazkowy"), 23));

    tmp_rect = QRectF(490*scale_x, 730*scale_y, 370*scale_x, 38*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Wyświetl numery kafelków"), 23));

    tmp_rect = QRectF(965*scale_x, 710*scale_y, 53*scale_x, 18*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Naciśnij"), 11));

    tmp_rect = QRectF(1049*scale_x, 710*scale_y, 60*scale_x, 18*scale_y);
    addItem(new MyLabel(tmp_rect, QString("Trzymaj"), 11));


    tmp_rect = QRectF(683*scale_x, 230*scale_y, 40*scale_x, 40*scale_y);
    addItem(new MyCheckBox(tmp_rect));

    addItem(new MyTextBox(873*scale_x, 370*scale_y));

    tmp_rect = QRectF(873*scale_x, 420*scale_y, 200*scale_x, 46*scale_y);
    addItem(new MySelectBox(tmp_rect, MySelectBox::BOARD_SIZE, 2, 20));

    tmp_rect = QRectF(873*scale_x, 470*scale_y, 200*scale_x, 46*scale_y);
    addItem(new MySelectBox(tmp_rect, MySelectBox::TIME, 10, 3600));

    tmp_rect = QRectF(734*scale_x, 620*scale_y, 40*scale_x, 40*scale_y);
    addItem(new MyCheckBox(tmp_rect));

    tmp_rect = QRectF(972*scale_x, 730*scale_y, 40*scale_x, 40*scale_y);
    MyRadioBox *r_box_1 = new MyRadioBox(tmp_rect);
    MyRadioBox *r_box_2 = new MyRadioBox(tmp_rect.adjusted(85*scale_x, 0, 85*scale_x, 0));
    connect(r_box_1, SIGNAL(click()), r_box_2, SLOT(onClick()));
    connect(r_box_2, SIGNAL(click()), r_box_1, SLOT(onClick()));
    addItem(r_box_1);
    addItem(r_box_2);

    tmp_rect = QRectF(490*scale_x, 680*scale_y, 180*scale_x, 40*scale_y);
    buttons_.append(new MyButton(tmp_rect, "Dodaj obraz"));
    addItem(buttons_[0]);

    tmp_rect = QRectF(972*scale_x, 950*scale_y, 100*scale_x, 40*scale_y);
    buttons_.append(new MyButton(tmp_rect, "Anuluj"));
    addItem(buttons_[1]);

    tmp_rect = QRectF(1082*scale_x, 950*scale_y, 100*scale_x, 40*scale_y);
    buttons_.append(new MyButton(tmp_rect, "Zapisz"));
    addItem(buttons_[2]);

    tmp_rect = QRectF(1192*scale_x, 950*scale_y, 210*scale_x, 40*scale_y);
    buttons_.append(new MyButton(tmp_rect, "Zapisz i wyjdź"));
    addItem(buttons_[3]);       
}

QList<MyButton*> SettingsScene::getButtons()
{
    return buttons_;
}

QPixmap SettingsScene::loadPixmap(QString path, QPoint resolution)
{
    if (resolution == QPoint(1920, 1080))
        return QPixmap(path);

    QPixmap pixmap(path);
    qreal width = pixmap.width() * resolution.x() / 1920;
    qreal height = pixmap.height() * resolution.y() / 1080;
    return pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}
