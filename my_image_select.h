#ifndef MYIMAGESELECT_H
#define MYIMAGESELECT_H

#include <QGraphicsRectItem>

class MyImageSelect : public QGraphicsRectItem
{
private:
    QPixmap current_image_;
public:
    MyImageSelect();
};

#endif // MYIMAGESELECT_H
