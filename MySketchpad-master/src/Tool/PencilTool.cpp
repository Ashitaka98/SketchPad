#include "include/Tool/PencilTool.h"
#include "include/MyPainter.h"
#include <QDebug>

#include<qdebug.h>

void PencilTool::mousePressEvent(QMouseEvent *event){
    qDebug()<<"pencil pressed!"<<drawStartPoint;
    drawStartPoint = event->localPos().toPoint();
}

void PencilTool::mouseMoveEvent(QMouseEvent *event){
    //painter.drawLine(drawStartPoint, event->localPos());
    //qDebug()<<"pencilTool::mouseMoveEvent";

    QImage *paintingImage = new QImage(*getBaseImage());
    MyPainter painter(paintingImage, getPen());

    int x1 = drawStartPoint.x(), y1 = drawStartPoint.y(), x2 = event->localPos().toPoint().x(), y2 = event->localPos().toPoint().y();
    painter.drawLine(x1, y1, x2, y2);

    setRenderImage(paintingImage);
    setBaseImage(paintingImage);

    drawStartPoint = event->localPos().toPoint();

    //注意，什么时候应该delete paintingImage这个指针呢？

    //奇怪的是，按照程序理解：
    //每次鼠标移动，都会new一个paintingImage，然后在上面作画，然后保存到baseImage
    //那么最后保存的baseImage应该是最后一次移动的画面啊
    //但实际上保存的是整体的画面

    //明白了，是因为每次都获得上次的baseImage，在上次的基础上画的
    //new QImage(*getBaseImage());
    //那这样写的开销真的好大，但是没办法

}

void PencilTool::mouseReleaseEvent(QMouseEvent *event){
    UNUSED(event);
    return;
}
