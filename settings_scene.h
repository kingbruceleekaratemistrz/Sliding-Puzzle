#ifndef SETTINGSSCENE_H
#define SETTINGSSCENE_H

#include <QObject>
#include <QGraphicsScene>

#include "my_button.h"
#include "my_check_box.h"
#include "my_text_box.h"
#include "my_select_box.h"
#include "my_radio_box.h"

class SettingsScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QList<MyButton*> buttons_;
    MyCheckBox *fullscreen_cb_;
    MyCheckBox *imagemode_cb_;
    MyTextBox *username_tb_;
    MySelectBox *boardsize_sb_;    
    MySelectBox *image_sb_;
    MyRadioBox *hold_rb_;
    MyRadioBox *toggle_rb_;
    QGraphicsPixmapItem *pixmap_item_;

public:
    enum { ADD_IMAGE, EXIT, SAVE, SAVE_AND_EXIT };
private:
    QPixmap loadPixmap(QString path, QPointF resolution);
    void initLabels(qreal sx, qreal sy);
    void initCheckBoxes(qreal sx, qreal sy);
    void initTextBoxes(qreal sx, qreal sy);
    void initSelectBoxes(qreal sx, qreal sy);
    void initRadioBoxes(qreal sx, qreal sy);
    void initButtons(qreal sx, qreal sy);
public:
    SettingsScene(QPointF resolution);
    ~SettingsScene();
    QList<MyButton*> getButtons();
    MyButton *getButton(int i);    
private:
    void reloadImage();
public slots:
    void saveSettings();
private slots:
    void openFileExplorer();
};

#endif // SETTINGSSCENE_H
