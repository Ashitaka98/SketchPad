#include"include/Tool/Tool.h"
#include"include/Shape/Shape.h"
#include "include/DrawingArea.h"
#include <QDebug>

Tool::Tool(DrawingArea *d):mDrawingArea(d){
    //qDebug()<<"Tool constructor";

    shape = nullptr;
    isMoving = false;
}

Tool::~Tool(){}

QImage* Tool::getBaseImage(){
    return mDrawingArea->mBaseImage;
}

QImage* Tool::getRenderImage(){
    return mDrawingArea->mRenderImage;
}

QPen* Tool::getPen(){
    return mDrawingArea->mPen;
}

QColor Tool::getFillColor(){
    return mDrawingArea->fillColor();
}

void Tool::setRenderImage(QImage* renderImage){
    if(mDrawingArea->mRenderImage!=nullptr)
        delete mDrawingArea->mRenderImage;
    mDrawingArea->mRenderImage = renderImage;
}

void Tool::setBaseImage(QImage* baseImage){
    *(mDrawingArea->mBaseImage) = *baseImage;
}

//记载在画板上画过的shapes
void Tool::addShape(Shape* s){
    mDrawingArea->shapes.push_back(s);
}

void Tool::finish(){}
