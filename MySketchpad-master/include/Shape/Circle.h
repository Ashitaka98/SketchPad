#ifndef CIRCLE_H
#define CIRCLE_H
#include"include/Shape/Shape.h"

class Circle:public Shape{
public:
    Circle(DrawingArea *a);
    ~Circle();

    QImage* draw();
    QImage *dispose();

    QImage* drawWithControlPoints();
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint &p);

    bool contain(const QPoint &p);
    void move(const QPoint &p);
    void addScaleFactor(int factor);

    void setCenter(QPoint c);
    QPoint getCenter();

    void setRadius(int r);
    int getRadius();


private:
    int radius;
};

#endif // CIRCLE_H
