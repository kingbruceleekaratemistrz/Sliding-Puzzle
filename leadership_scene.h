#ifndef LEADERSHIPSCENE_H
#define LEADERSHIPSCENE_H

#include <QGraphicsScene>

#include "my_pixmap_button.h"
#include "my_select_box.h"
#include "my_text_box.h"
#include "my_label.h"
#include "my_button.h"

class LeadershipScene : public QGraphicsScene
{
private:
    int pages_num_;
    int current_page_;
    MySelectBox *boardsize_sb_;
    MySelectBox *pages_sb_;
    MyTextBox *username_tb_;
    MyPixmapButton *reload_pb_;
    MyButton *exit_button_;
    QList<QList<QString>> results_;
    QList<MyLabel*> score_lables_;
public:
    LeadershipScene(QPoint resolution);
    MyButton *getButton();
private:
    void loadLabels();
    void reloadPageSelect();
};

#endif // LEADERSHIPSCENE_H
