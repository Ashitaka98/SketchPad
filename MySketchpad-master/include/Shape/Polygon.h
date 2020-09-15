#ifndef POLYGON_H
#define POLYGON_H
#include"include/Shape/Shape.h"
#include<QVector>

class Polygon:public Shape{
public:
    Polygon(DrawingArea *a);
    ~Polygon();

    QImage* draw();
    QImage* dispose();

    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);

    void setDeg(int);

    bool contain(const QPoint &);
    void move(const QPoint& p);
    void addScaleFactor(int factor);

    QVector<QPoint*>& getPoints();
    void pushPoint(QPoint* point);
    void popPoint();

    void close();
    bool isClosed;

private:
    QVector<QPoint*> originPoints;
};

#endif // POLYGON_H
