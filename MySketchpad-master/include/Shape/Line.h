#ifndef LINE_H
#define LINE_H
#include"include/Shape/Shape.h"
#include"include/Common.h"

class Line:public Shape{
    friend bool clipLine(Line*, int, int, int, int);
public:
    Line(DrawingArea *a);
    ~Line();

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

private:
    QVector<QPoint*> originPoints;
};

#endif // LINE_H
