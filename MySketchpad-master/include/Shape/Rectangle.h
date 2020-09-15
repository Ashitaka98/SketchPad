#ifndef RECTANGLE_H
#define RECTANGLE_H
#include"include/Shape/Shape.h"

class Rectangle:public Shape{
public:
    Rectangle(DrawingArea *d);
    ~Rectangle();

    QImage* draw();

    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);

    bool contain(const QPoint &);

    QPoint topLeft(){return *points[0];}
    QPoint bottomRight(){return *points[3];}

    void setRect(const QPoint &p1, const QPoint &p2);
};

#endif // RECTANGLE_H
