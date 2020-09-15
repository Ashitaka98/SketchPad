#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QQuickPaintedItem>
#include <QPen>
#include <QVector>
#include "include/Tool/Tool.h"

class Tool;
class Shape;
class SelectTool;

class DrawingArea : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
    Q_PROPERTY(ToolType currentTool READ currentTool WRITE setCurrentTool)
    Q_PROPERTY(int penThickness READ penThickness WRITE setPenThickness)
    Q_PROPERTY(bool editing READ editing WRITE setEditing NOTIFY editingChanged)
    Q_PROPERTY(int deg READ deg WRITE setDeg NOTIFY degChanged)
    Q_PROPERTY(QColor fillColor READ fillColor WRITE setFillColor)

    friend Tool;
    friend Shape;
    friend SelectTool;

public:
    //工具和形状栏
    enum ToolType{
        PENCIL = 0,
        ERASER,
        CLIP,
        FILL,
        LINE,
        CIRCLE,
        ELLIPSE,
        POLYGON,
        CURVE,
        SELECT,
        NONE
    };Q_ENUM(ToolType)

    DrawingArea(QQuickItem *parent = nullptr);
    ~DrawingArea();

    QColor penColor()const;
    void setPenColor(QColor color);

    QColor fillColor()const;
    void setFillColor(QColor color);

    int penThickness()const;
    void setPenThickness(int thickness);

    ToolType currentTool()const;
    void setCurrentTool(ToolType tool);

    bool editing()const;
    void setEditing(bool);

    int deg()const;
    void setDeg(int);

    void clip(const QPoint& tl, const QPoint& br);

    void paint(QPainter *painter);

signals:
    void editingChanged();
    void degChanged();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    Q_INVOKABLE void init();
    Q_INVOKABLE void clear();
    Q_INVOKABLE void displayOFF();
    Q_INVOKABLE void save();
    Q_INVOKABLE void load();

protected:
    QPen *mPen;
    QColor mFillColor;

    //好的coder在声明指针时，就要初始化
    QImage *mBaseImage = nullptr;
    //mBaseImage相当于是幕布，mRenderImage是备份
    QImage *mRenderImage = nullptr;

    ToolType mCurrentType = NONE, mPreType = NONE;
    //指针数组：数组里面存放的是指针,这些指针指向Tool类型变量
    Tool *mTools[NONE + 1] = {nullptr};

    QVector<Shape*> shapes;
    Shape *selected = nullptr;

    bool mEditing;
    int mDeg;
};

#endif // DRAWINGAREA_H
