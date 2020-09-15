#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include"include/Tool/Tool.h"
#include"include/DrawingArea.h"

class SelectTool:public Tool{
public:
    SelectTool(DrawingArea *d);
    ~SelectTool();

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void finish();

    //返回的是枚举类型
    typename DrawingArea::ToolType getSelectdType(){return selectedTool;}

private:
    typename DrawingArea::ToolType selectedTool;
};

#endif // SELECTTOOL_H
