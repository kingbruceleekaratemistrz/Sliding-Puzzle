#include "settings_scene.h"
#include "my_label.h"
#include "my_check_box.h"
#include "my_text_box.h"
#include "my_select_box.h"
#include "my_button.h"
#include "my_radio_box.h"

#include <QFile>
#include <QSettings>

SettingsScene::SettingsScene(QPointF resolution)
{    
    setSceneRect(0, 0, resolution.x(), resolution.y());
    addItem(new QGraphicsPixmapItem(loadPixmap("./assets/settings/background.png", resolution)));

    qreal scale_x = resolution.x() / 1920;
    qreal scale_y = resolution.y() / 1080;

    initLabels(scale_x, scale_y);
    initCheckBoxes(scale_x, scale_y);
    initTextBoxes(scale_x, scale_y);
    initSelectBoxes(scale_x, scale_y);
    initRadioBoxes(scale_x, scale_y);
    initButtons(scale_x, scale_y);

    QSettings settings("config.ini", QSettings::IniFormat);
    QString path = "./assets/images/"+QString::number(settings.value("image").toInt())+".jpg";
    if (!QFile::exists(path))
        path = "./assets/images/"+QString::number(settings.value("image").toInt())+".png";
    if (!QFile::exists(path))
        path = "./assets/images/1.jpg";

    pixmap_item_ = new QGraphicsPixmapItem(QPixmap(path).scaled(200*scale_x, 200*scale_y, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    pixmap_item_->setPos(490*scale_x, 770*scale_y);
    addItem(pixmap_item_);
}

SettingsScene::~SettingsScene()
{
    for (auto b : buttons_)
        delete b;
    delete fullscreen_cb_;
    delete imagemode_cb_;
    delete username_tb_;
    delete boardsize_sb_;
    delete maxtime_sb_;
    delete hold_rb_;
    delete toggle_rb_;
}

void SettingsScene::saveSettings()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    settings.setValue("fullscreen", fullscreen_cb_->isChecked());
    settings.setValue("username", username_tb_->toPlainText());
    settings.setValue("boardsize", boardsize_sb_->val());
    settings.setValue("maxtime", maxtime_sb_->val());
    settings.setValue("imagemode", imagemode_cb_->isChecked());
    settings.setValue("showonhold", hold_rb_->isChecked());
    settings.setValue("image", image_sb_->val());
}

QList<MyButton*> SettingsScene::getButtons()
{
    return buttons_;
}

MyButton* SettingsScene::getButton(int i)
{
    return buttons_.at(i);
}

void SettingsScene::reload()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    fullscreen_cb_->setChecked(settings.value("fullscreen").toInt());
    imagemode_cb_->setChecked(settings.value("imagemode").toInt());
    username_tb_->setPlainText(settings.value("username").toString());
    boardsize_sb_->setVal(settings.value("boardsize").toInt());
    maxtime_sb_->setVal(settings.value("maxtime").toInt());
    hold_rb_->setChecked(settings.value("showonhold").toBool());
    toggle_rb_->setChecked(!settings.value("showonhold").toBool());
}

QPixmap SettingsScene::loadPixmap(QString path, QPointF resolution)
{
    if (resolution == QPointF(1920, 1080))
        return QPixmap(path);

    QPixmap pixmap(path);
    qreal width = pixmap.width() * resolution.x() / 1920;
    qreal height = pixmap.height() * resolution.y() / 1080;
    return pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void SettingsScene::initLabels(qreal sx, qreal sy)
{
    QRectF rect[14] = {
        QRectF(715*sx, 0*sy, 490*sx, 125*sy),
        QRectF(400*sx, 150*sy, 400*sx, 75*sy),
        QRectF(460*sx, 230*sy, 167*sx, 38*sy),
        QRectF(400*sx, 290*sy, 400*sx, 75*sy),
        QRectF(460*sx, 370*sy, 400*sx, 38*sy),
        QRectF(460*sx, 420*sy, 400*sx, 38*sy),
        QRectF(460*sx, 470*sy, 400*sx, 38*sy),
        QRectF(460*sx, 520*sy, 220*sx, 38*sy),
        QRectF(460*sx, 570*sy, 220*sx, 38*sy),
        QRectF(460*sx, 620*sy, 230*sx, 38*sy),
        QRectF(490*sx, 730*sy, 370*sx, 38*sy),
        QRectF(965*sx, 710*sy, 53*sx, 18*sy),
        QRectF(1049*sx, 710*sy, 60*sx, 18*sy),
        QRectF(873*sx, 730*sy, 54*sx, 38*sy)
    };
    int font_size[14] = { int(75*sy), int(34*sy), int(23*sy), int(34*sy), int(23*sy), int(23*sy), int(23*sy), int(23*sy), int(23*sy), int(23*sy), int(23*sy), int(11*sy), int(11*sy), int(23*sy) };
    QString text[14] = {
        "Ustawienia",
        "Ustawienia aplikacji",
        "Pełny ekran",
        "Ustawienia gry",
        "Domyślna nazwa gracza",
        "Domyślny rozmiar planszy",
        "Domyślny maksymalny czas",
        "Motyw kolorów",
        "Motyw kafelków",
        "Tryb obrazkowy",
        "Wyświetl numery kafelków",
        "Naciśnij",
        "Trzymaj",
        "alt"
    };
    for (int i = 0; i < 14; i++)
        addItem(new MyLabel(rect[i], text[i], Qt::AlignLeft, font_size[i]));
}

void SettingsScene::initCheckBoxes(qreal sx, qreal sy)
{
    QSettings settings("config.ini", QSettings::IniFormat);
    QRectF rect[2] = {
        QRectF(683*sx, 230*sy, 40*sx, 40*sy),
        QRectF(734*sx, 620*sy, 40*sx, 40*sy)
    };

    fullscreen_cb_ = new MyCheckBox(rect[0], settings.value("fullscreen").toBool(), 5*sx);
    addItem(fullscreen_cb_);

    imagemode_cb_ = new MyCheckBox(rect[1], settings.value("imagemode").toBool(), 5*sx);
    addItem(imagemode_cb_);
}

void SettingsScene::initTextBoxes(qreal sx, qreal sy)
{
    QSettings settings("config.ini", QSettings::IniFormat);
    username_tb_ = new MyTextBox(QRectF(873*sx, 370*sy, 200*sx, 40*sy), settings.value("username").toString(), 23*sy, 5*sx);
    addItem(username_tb_);

}

void SettingsScene::initSelectBoxes(qreal sx, qreal sy)
{
    QSettings settings("config.ini", QSettings::IniFormat);
    QRectF rect[3] = {
        QRectF(873*sx, 420*sy, 200*sx, 44*sy),
        QRectF(873*sx, 470*sy, 200*sx, 44*sy),
        QRectF(490*sx, 980*sy, 200*sx, 44*sy)
    };

    boardsize_sb_ = new MySelectBox(rect[0], MySelectBox::BOARD_SIZE, 2, 20, settings.value("boardsize").toInt(), 23*sy, 5*sy);
    addItem(boardsize_sb_);

    maxtime_sb_ = new MySelectBox(rect[1], MySelectBox::TIME, 0, 3600, settings.value("maxtime").toInt(), 23*sy, 5*sx);
    addItem(maxtime_sb_);

    image_sb_ = new MySelectBox(rect[2], MySelectBox::PAGES, 1, settings.value("numofimages").toInt(), settings.value("image").toInt(), 23*sy, 5*sx);
    connect(image_sb_, &MySelectBox::click, this, [this] { reloadImage(); });
    addItem(image_sb_);
}

void SettingsScene::reloadImage()
{
    removeItem(pixmap_item_);
    delete pixmap_item_;

    qreal sx = width()/1920.0;
    qreal sy = height()/1080.0;
    QSettings settings("config.ini", QSettings::IniFormat);

    QString path = "./assets/images/"+QString::number(image_sb_->val())+".jpg";
    if (!QFile::exists(path))
        path = "./assets/images/"+QString::number(image_sb_->val())+".png";
    if (!QFile::exists(path))
        path = "./assets/images/1.jpg";

    pixmap_item_ = new QGraphicsPixmapItem(QPixmap(path).scaled(200*sx, 200*sy, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    pixmap_item_->setPos(490*sx, 770*sy);
    addItem(pixmap_item_);
}

void SettingsScene::initRadioBoxes(qreal sx, qreal sy)
{
    QSettings settings("config.ini", QSettings::IniFormat);
    QRectF rect(972*sx, 730*sy, 40*sx, 40*sy);

    toggle_rb_ = new MyRadioBox(rect, !settings.value("showonhold").toBool(), 5*sx);
    hold_rb_ = new MyRadioBox(rect.adjusted(85*sx, 0, 85*sx, 0), settings.value("showonhold").toBool(), 5*sx);
    connect(hold_rb_, SIGNAL(click()), toggle_rb_, SLOT(onClick()));
    connect(toggle_rb_, SIGNAL(click()), hold_rb_, SLOT(onClick()));
    addItem(hold_rb_);
    addItem(toggle_rb_);
}

void SettingsScene::initButtons(qreal sx, qreal sy)
{
    QSettings settings("config.ini", QSettings::IniFormat);
    QRectF rect[4] = {
        QRectF(490*sx, 680*sy, 180*sx, 40*sy),
        QRectF(972*sx, 950*sy, 100*sx, 40*sy),
        QRectF(1082*sx, 950*sy, 100*sx, 40*sy),
        QRectF(1192*sx, 950*sy, 210*sx, 40*sy)
    };

    buttons_.append(new MyButton(rect[0], "Dodaj obraz", 23*sy));
    connect(buttons_[0], SIGNAL(click()), this, SLOT(openFileExplorer()));
    addItem(buttons_[0]);

    buttons_.append(new MyButton(rect[1], "Wyjdź", 23*sy));
    addItem(buttons_[1]);

    buttons_.append(new MyButton(rect[2], "Zapisz", 23*sy));
    connect(buttons_[2], SIGNAL(click()), this, SLOT(saveSettings()));
    addItem(buttons_[2]);

    buttons_.append(new MyButton(rect[3], "Zapisz i wyjdź", 23*sy));
    connect(buttons_[3], SIGNAL(click()), this, SLOT(saveSettings()));
    addItem(buttons_[3]);
}

#include <QFileDialog>

void SettingsScene::openFileExplorer()
{
    QSettings settings("config.ini", QSettings::IniFormat);
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Wybierz obrazek"), "/home/", tr("Obrazy  (*.jpg *.png)"));
    QPixmap pixmap(path);

    settings.setValue("numofimages", settings.value("numofimages").toInt()+1);
    QString new_path = "./assets/images/"+QString::number(settings.value("numofimages").toInt())+".png";
    QFile file(new_path);
    file.open(QIODevice::WriteOnly);
    pixmap.save(&file, "PNG");

    removeItem(image_sb_);
    delete image_sb_;
    qreal sx = width()/1920.0;
    qreal sy = height()/1080.0;
    settings.setValue("image", settings.value("numofimages").toInt());
    image_sb_ = new MySelectBox(QRectF(490*sx, 980*sy, 200*sx, 44*sy), MySelectBox::PAGES, 1, settings.value("numofimages").toInt(), settings.value("image").toInt(), 23*sy, 5*sx);
    connect(image_sb_, &MySelectBox::click, this, [this] { reloadImage(); });
    addItem(image_sb_);
    reloadImage();
}
