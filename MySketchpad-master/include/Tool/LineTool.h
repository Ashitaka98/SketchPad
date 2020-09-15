#ifndef LINETOOL_H
#define LINETOOL_H

#include"include/Tool/Tool.h"
#include"include/Shape/Line.h"
#include<QPen>
#include<QMouseEvent>
#include<QImage>

class LineTool:public Tool
{
public:
    LineTool(DrawingArea *d);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void finish();
};

#endif // LINE_H
