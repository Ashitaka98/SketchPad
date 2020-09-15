#ifndef ELLIPSE_H
#define ELLIPSE_H
#include"include/Shape/Shape.h"

class Ellipse:public Shape{
public:
    Ellipse(DrawingArea *a);

    QImage* draw();
    QImage* dispose();

    QImage* drawWithControlPoints();
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);

    void setDeg(int);
    int  getDeg();

    bool contain(const QPoint&);
    void move(const QPoint& p);
    void addScaleFactor(int factor);

    void setCenter(QPoint c);
    void setParameter(int rx, int ry);

private:
    int rx, ry;
};

#endif // ELLIPSE_H
