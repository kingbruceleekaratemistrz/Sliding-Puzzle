#include "my_label.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>

MyLabel::MyLabel(QRectF rect, QString text, int font_size) : text_(text), font_size_(font_size)
{
    setRect(rect);
    setFlag(QGraphicsItem::ItemIsFocusable);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(1);
    setGraphicsEffect(effect);
}

void MyLabel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setFont(QFont("Irish Grover", font_size_));
    painter->setPen(QColor(0, 14, 63));
    painter->drawText(rect(), Qt::AlignLeft, text_);
}

QString MyLabel::text()
{
    return text_;
}

void MyLabel::setText(QString text)
{
    text_ = text;
    update();
}
