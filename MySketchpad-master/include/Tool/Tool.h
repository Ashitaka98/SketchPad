#ifndef TOOL_H
#define TOOL_H

#include<QImage>
#include<QMouseEvent>
#include<QPoint>
#include<QPen>
#include<QPainter>

class DrawingArea;
class Shape;

//used to supress "unused parameter" warnings
#define UNUSED(x) (void)(x)

class Tool
{
public:
    Tool(DrawingArea *d);
    virtual ~Tool();

    virtual void mousePressEvent(QMouseEvent *event)=0;
    virtual void mouseMoveEvent(QMouseEvent *event)=0;
    virtual void mouseReleaseEvent(QMouseEvent *event)=0;
    virtual void finish();

    Shape* getShape(){return shape;}
    void setShape(Shape* s){shape = s;}

protected:
    QImage *getBaseImage();
    QImage *getRenderImage();
    void setRenderImage(QImage* renderImage);
    void setBaseImage(QImage* baseImage);

    QPen *getPen();
    QColor getFillColor();
    void addShape(Shape* s);

    //成员变量有其他类的情况下，必须初始化(列表)
    DrawingArea *mDrawingArea;
    Shape *shape;

    QPoint moveStartPoint;
    QPoint drawStartPoint;
    QVector<QPoint*>::iterator editPoint;

    bool isMoving;
};

#endif // TOOL_H
