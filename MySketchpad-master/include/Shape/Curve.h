#ifndef CURVE_H
#define CURVE_H

#include "include/Shape/Shape.h"

class Curve:public Shape{
public:
    Curve(DrawingArea *d);
    ~Curve();

    QImage* draw();
    QImage* dispose();

    QImage* drawWithControlPoints();
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);

    void setDeg(int);
    int  getDeg();

    bool contain(const QPoint&);
    void move(const QPoint& p);
    void addScaleFactor(int factor);

    void pushPoint(const QPoint& p);
    void popPoint();

    bool finished;

private:
    QVector<QPoint*> originPoints;
};

#endif // CURVE_H
