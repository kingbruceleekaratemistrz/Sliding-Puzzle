#include "my_text_box.h"

#include <QFont>
#include <QPainter>
#include <QKeyEvent>

MyTextBox::MyTextBox(qreal x, qreal y, QString text, int font_size, int arc)
{
    arc_ = (arc > 1) ? arc : 1;
    setPos(x, y);
    setTextInteractionFlags(Qt::TextEditorInteraction);
    setFont(QFont("Irish Grover", font_size));
    setPlainText(text);
}

void MyTextBox::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
        event->accept();
    else if (toPlainText().length() < 24 || event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete || event->key() == Qt::Key_Left || event->key() == Qt::Key_Right)
        QGraphicsTextItem::keyPressEvent(event);
    else
        event->accept();
}

void MyTextBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QRectF bounding_rect = boundingRect();
    QPainterPath path;
    path.addRoundedRect(bounding_rect, arc_, arc_);
    path.addRoundedRect(bounding_rect.adjusted(arc_, arc_, -arc_, -arc_), arc_, arc_);
    painter->setPen(QColor(0, 14, 63));
    painter->fillPath(path, QColor(0, 14, 63));
    painter->drawPath(path);
    QGraphicsTextItem::paint(painter, option, widget);
}

QPainterPath MyTextBox::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

QRectF MyTextBox::boundingRect() const
{
    QRectF bounding_rect = QGraphicsTextItem::boundingRect();
    if (bounding_rect.width() <= 200)
        bounding_rect.setWidth(200);
    return bounding_rect;
}
