#include "my_timer.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>
#include <QTimer>

MyTimer::MyTimer(QRectF rect, int font_size) : font_size_(font_size)
{
    setRect(rect);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(1);
    setGraphicsEffect(effect);
    sec_ = 0;
    min_ = 0;
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, &MyTimer::inc);
    timer_->start(1000);
}

void MyTimer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QString text = QString::number(min_).rightJustified(2, '0');
    text += ":";
    text += QString::number(sec_).rightJustified(2, '0');

    painter->setFont(QFont("Irish Grover", font_size_));
    painter->setPen(QColor(0, 14, 63));
    painter->drawText(rect(), Qt::AlignLeft, text);
}

int MyTimer::getTime()
{
    timer_->stop();
    return min_*60+sec_;
}

MyTimer::~MyTimer()
{
    delete timer_;
}

void MyTimer::inc()
{
    if (sec_ == 59)
    {
        min_++;
        sec_ = 0;
    }
    else
        sec_++;
    update();
}
