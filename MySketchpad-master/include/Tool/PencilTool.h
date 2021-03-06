#ifndef PENCILTOOL_H
#define PENCILTOOL_H

#include"include/Tool/Tool.h"
#include <QDebug>

class PencilTool:public Tool
{
public:
    PencilTool(DrawingArea* d):Tool(d){qDebug()<<"PencilTool constructor";}

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // PENCIL_H
