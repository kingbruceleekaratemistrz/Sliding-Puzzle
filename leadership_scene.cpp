#include "leadership_scene.h"

#include <QObject>
#include <QSettings>

#include "score_parser.h"
#include "my_button.h"

LeadershipScene::LeadershipScene(QPoint resolution)
{
    setSceneRect(0, 0, resolution.x(), resolution.y());
    setBackgroundBrush(QImage("./assets/leaderboard/background.png").scaled(width(), height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

    qreal sx = resolution.x()/1920.0;
    qreal sy = resolution.y()/1080.0;

    QSettings settings("config.ini", QSettings::IniFormat);

    boardsize_sb_ = new MySelectBox(QRectF(711*sx, 166*sy, 143*sx, 40*sy), MySelectBox::BOARD_SIZE, 2, 20, settings.value("boardsize").toInt(), 23*sy, 5*sy);
    connect(boardsize_sb_, &MySelectBox::click, this, [this]{ loadLabels(); reloadPageSelect(); });
    addItem(boardsize_sb_);

    username_tb_ = new MyTextBox(QRectF(1235*sx, 166*sy, 150*sx, 40*sy), "", 20*sy, 5*sx);
    addItem(username_tb_);

    QPixmap pixmap("./assets/leaderboard/reload.png");
    qreal pw = pixmap.width() * resolution.x() / 1920.0;
    qreal ph = pixmap.height() * resolution.y() / 1080.0;
    reload_pb_ = new MyPixmapButton(pixmap.scaled(pw, ph, Qt::IgnoreAspectRatio, Qt::SmoothTransformation), 1467*sx, 161*sy);
    connect(reload_pb_, &MyPixmapButton::click, this, [this]{ loadLabels(); });
    addItem(reload_pb_);

    current_page_ = 1;
    loadLabels();

    pages_sb_ = new MySelectBox(QRectF(892*sx, 842*sy, 143*sx, 40*sy), MySelectBox::PAGES, 1, pages_num_, 1, 23*sy, 5*sy);
    connect(pages_sb_, &MySelectBox::click, this, [this]{ current_page_ = pages_sb_->val(); loadLabels(); });
    addItem(pages_sb_);

    exit_button_ = new MyButton(QRectF(834*sx, 908*sy, 260*sx, 50*sy), "Wróć do menu", 30*sy);
    addItem(exit_button_);
}

void LeadershipScene::reloadPageSelect()
{
    removeItem(pages_sb_);
    delete pages_sb_;
    qreal sx = width()/1920.0;
    qreal sy = height()/1080.0;
    pages_sb_ = new MySelectBox(QRectF(892*sx, 842*sy, 143*sx, 40*sy), MySelectBox::PAGES, 1, pages_num_, 1, 23*sy, 5*sy);
    connect(pages_sb_, &MySelectBox::click, this, [this]{ current_page_ = pages_sb_->val(); loadLabels(); });
    addItem(pages_sb_);
}

void LeadershipScene::loadLabels()
{
    int board_size = boardsize_sb_->val();
    QString username = username_tb_->toPlainText();
    if (username.isEmpty())
    {
        results_ = ScoreParser::readScores(board_size);
    }
    else
    {
        results_ = ScoreParser::readScores(board_size, username);
    }

    pages_num_ = qCeil(results_.count() / 14.0);

    for (auto label : score_lables_)
    {
        removeItem(label);
        delete label;
    }
    score_lables_.clear();

    qreal sx = width()/1920.0;
    qreal sy = height()/1080.0;
    QRectF rects[3] = {
        QRectF(528*sx, 282*sy, 380*sx, 38*sy),
        QRectF(910*sx, 282*sy, 248*sx, 38*sy),
        QRectF(1160*sx, 282*sy, 248*sx, 38*sy)
    };

    QList<QList<QString>> sublist = results_.mid((current_page_-1)*14);
    if (sublist.count() > 14)
        sublist = sublist.mid(0, 14);
    for (auto result : sublist)
    {
        score_lables_.push_back(new MyLabel(rects[0], result[1], Qt::AlignLeft | Qt::AlignVCenter, 18));
        score_lables_.push_back(new MyLabel(rects[1], result[2], Qt::AlignCenter, 18));
        int min = int(result[3].toInt()/60);
        int sec = result[3].toInt()%60;
        QString time_str = QString::number(min).rightJustified(2, '0')+":"+QString::number(sec).rightJustified(2,'0');
        score_lables_.push_back(new MyLabel(rects[2], time_str, Qt::AlignCenter, 18));
        rects[0].adjust(0, 38*sy, 0, 38*sy);
        rects[1].adjust(0, 38*sy, 0, 38*sy);
        rects[2].adjust(0, 38*sy, 0, 38*sy);
    }
    for (auto label : score_lables_)
    {
        addItem(label);
    }
}

MyButton *LeadershipScene::getButton()
{
    return exit_button_;
}
