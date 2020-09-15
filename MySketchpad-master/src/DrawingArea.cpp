#include <QPainter>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include "include/OFFViewer/OFFModel.h"
#include "include/OFFViewer/GLWidget.h"
#include "include/DrawingArea.h"
#include "include/Tools.h"
#include <QDebug>

DrawingArea::DrawingArea(QQuickItem *parent):
    QQuickPaintedItem (parent)
{
    qDebug()<<"DrawingArea constructor!";

    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

    mPen = new QPen();
    mPen->setCapStyle(Qt::RoundCap);
    mPen->setJoinStyle(Qt::RoundJoin);

    //默认无法编辑(绘画)
    mEditing = false;
    //默认旋转角度是0
    mDeg = 0;

    //this传递的就是DrawingArea类指针
    //构造函数顺序是先Tool的构造，再其派生类构造
    mTools[PENCIL]=new PencilTool(this);
    mTools[ERASER] = new EraserTool(this);
    mTools[CLIP] = new ClipTool(this);
    mTools[FILL] = new FillTool(this);
    mTools[SELECT] = new SelectTool(this);

    mTools[LINE] = new LineTool(this);
    mTools[CIRCLE] = new CircleTool(this);
    mTools[ELLIPSE] = new EllipseTool(this);
    mTools[POLYGON] = new PolygonTool(this);
    mTools[CURVE] = new CurveTool(this);
}

DrawingArea::~DrawingArea(){

    qDebug()<<"DrawingArea deconstructor!";
    for(auto it = shapes.begin(); it != shapes.end(); it++){
        delete *it;
    }
    shapes.clear();
    for(int i = 0; i < NONE+1; i++){
        if(mTools[i]!=nullptr){
            delete mTools[i];
            mTools[i]=nullptr;
        }
    }
    delete mBaseImage;
    delete mRenderImage;
    delete mPen;
}

QColor DrawingArea::fillColor()const{
    return mFillColor;
}

void DrawingArea::setFillColor(QColor color){
    qDebug()<<"DrawingArea setFillColor!";
    mFillColor = color;
    if(mTools[mCurrentType]!=nullptr && editing()){
        ToolType temp = mCurrentType;
        if(mCurrentType==SELECT){
            temp = dynamic_cast<SelectTool*>(mTools[SELECT])->getSelectdType();
        }
        if(mRenderImage!=nullptr)
            delete mRenderImage;
        mTools[temp]->getShape()->setFillColor(mFillColor);
        mRenderImage = mTools[temp]->getShape()->drawWithControlPoints();
        update();
    }
}

QColor DrawingArea::penColor()const{
    return mPen->color();
}

void DrawingArea::setPenColor(QColor color){
    qDebug()<<"DrawingArea setPenColor!";
    mPen->setColor(color);
    if(mTools[mCurrentType]!=nullptr && editing()){
        ToolType temp = mCurrentType;
        if(mCurrentType==SELECT){
            temp = dynamic_cast<SelectTool*>(mTools[SELECT])->getSelectdType();
        }
        mTools[temp]->getShape()->setBorderColor(color);
        if(mRenderImage!=nullptr)
            delete mRenderImage;
        mRenderImage = mTools[temp]->getShape()->drawWithControlPoints();
        update();
    }
    else if(mCurrentType == POLYGON){
        mTools[mCurrentType]->getShape()->setBorderColor(color);
        if(mRenderImage!=nullptr)
            delete mRenderImage;
        mRenderImage = mTools[mCurrentType]->getShape()->draw();
        update();
    }
}

int DrawingArea::penThickness()const{
    return mPen->width()-1;
}

void DrawingArea::setPenThickness(int thickness){
    qDebug()<<"DrawingArea setPenThickness!";
    if(mTools[mCurrentType]!=nullptr){
        mTools[mCurrentType]->finish();
        update();
    }
    mPen->setWidth(thickness+1);
}

bool DrawingArea::editing()const{
    return mEditing;
}

void DrawingArea::setEditing(bool editing){
    qDebug()<<"DrawingArea setEditing!";
    mEditing = editing;
    emit editingChanged();
}

int DrawingArea::deg()const{
    return mDeg;
}

void DrawingArea::setDeg(int deg){
    qDebug()<<"DrawingArea setDeg!";
    if(mTools[mCurrentType]!=nullptr && mEditing){
        ToolType temp = mCurrentType;
        if(mCurrentType==SELECT){
            temp = dynamic_cast<SelectTool*>(mTools[SELECT])->getSelectdType();
        }
        mTools[temp]->getShape()->setDeg(deg);
        if(mRenderImage!=nullptr)
            delete mRenderImage;
        mRenderImage = mTools[temp]->getShape()->drawWithControlPoints();
        update();
    }
    if(deg == mDeg)
        return;
    mDeg = deg;
    emit degChanged();
}

typename DrawingArea::ToolType DrawingArea::currentTool()const{
    return mCurrentType;}

void DrawingArea::setCurrentTool(ToolType tool){
    qDebug()<<"DrawingArea setCurrentTool!";
    mPreType = mCurrentType;
    mCurrentType = tool;

    qDebug()<<"之前的工具类型：" << mPreType<<" 现在的工具类型："<<mCurrentType;

    if(mCurrentType!=mPreType && mTools[mPreType] != nullptr){
        mTools[mPreType]->finish();
        update();
    }
}

void DrawingArea::paint(QPainter *painter){
    qDebug()<<"DrawingArea::paint";
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawImage(0,0,*mRenderImage);
}

void DrawingArea::init(){
    qDebug()<<"初始化baseImage宽高为"<<width()<<" "<<height();
    mBaseImage = new QImage(int(width()), int(height()), QImage::Format_ARGB32_Premultiplied);
    mBaseImage->fill("white");
    mRenderImage = new QImage(*mBaseImage);
    update();
}

void DrawingArea::clear(){
    if((mTools[mCurrentType]!=nullptr && mEditing)||mCurrentType == POLYGON)
        mTools[mCurrentType]->finish();
    mBaseImage->fill(QColor(255,255,255));
    if(mRenderImage != nullptr){
        delete mRenderImage;
    }
    mRenderImage = new QImage(*mBaseImage);
    for(auto it = shapes.begin(); it<shapes.end();it++){
        delete *it;
    }
    shapes.clear();
    update();
}

void DrawingArea::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::RightButton && mCurrentType != CURVE)
        return;
    if(mTools[mCurrentType] == nullptr)
        return;

    //c++的多态/虚函数
    mTools[mCurrentType]->mousePressEvent(event);
    update();
}

void DrawingArea::mouseMoveEvent(QMouseEvent *event){
    if(mTools[mCurrentType] == nullptr || event->button() == Qt::RightButton)
        return;
    mTools[mCurrentType]->mouseMoveEvent(event);
    update();
}

void DrawingArea::mouseReleaseEvent(QMouseEvent *event){
    if(mTools[mCurrentType] == nullptr || event->button() == Qt::RightButton)
        return;
    mTools[mCurrentType]->mouseReleaseEvent(event);
    update();
}

void DrawingArea::wheelEvent(QWheelEvent *event){
    int factor = event->delta()/120;
    if(editing()){
        ToolType temp = mCurrentType;
        if(mCurrentType==SELECT){
            temp = dynamic_cast<SelectTool*>(mTools[SELECT])->getSelectdType();
        }
        mTools[temp]->getShape()->addScaleFactor(factor);
        if(mRenderImage!=nullptr)
            delete mRenderImage;
        mRenderImage = mTools[temp]->getShape()->drawWithControlPoints();
        update();
    }
}

void DrawingArea::clip(const QPoint &tl, const QPoint & br){
    int xmin = tl.x(), ymin = tl.y();
    int xmax = br.x(), ymax = br.y();
    if(shapes.size() == 0){
        if(mRenderImage!=nullptr)
            delete mRenderImage;
        mRenderImage = new QImage(*mBaseImage);
        return;
    }
    auto it = shapes.begin();
    while(it < shapes.end()){
        if(typeid(**it) == typeid(Line)){
            if(mRenderImage != nullptr)
                delete mRenderImage;
            mRenderImage = (*it)->dispose();
            *mBaseImage = *mRenderImage;
            if(!clipLine(dynamic_cast<Line*>(*it), xmin, xmax, ymin, ymax)){
                delete *it;
                shapes.erase(it);
                continue;
            }
        }
        it++;
    }
    for(int i = 0; i < shapes.size(); i ++){
        if(mRenderImage != nullptr)
            delete mRenderImage;
        mRenderImage = shapes[i]->draw();
        *mBaseImage = *mRenderImage;
    }
    update();
}

void DrawingArea::save(){
    QString file = QFileDialog::getSaveFileName(nullptr, "Save Image", "./", "PNG (*.png)");
    if(!file.isNull()){
        if(mTools[mCurrentType]!=nullptr){
            mTools[mCurrentType]->finish();
            update();
        }
        mBaseImage->save(file, "PNG");
    }
}

void DrawingArea::load(){
    QString file = QFileDialog::getOpenFileName(nullptr, "Load Image", "./", "PNG(*.png)");
    if(!file.isNull()){
        if(mTools[mCurrentType]!=nullptr){
            mTools[mCurrentType]->finish();
            update();
        }
        shapes.clear();

        QImage temp(file, "PNG");
        mBaseImage->fill("white");
        QPainter painter(mBaseImage);
        painter.drawImage(0, 0, temp);
        if(mRenderImage!=nullptr){
            delete mRenderImage;
        }
        mRenderImage = new QImage(*mBaseImage);
        update();
    }
}

//2d->3d
void DrawingArea::displayOFF(){

    QString file = QFileDialog::getOpenFileName(nullptr, "Open File","./", "Off Files (*.off)");
    if(!file.isNull()){
        try{
            OFFModel *model = new OFFModel(file);
            QOpenGLWidget* glWidget = new GLWidget(nullptr, model);
            glWidget->show();
        }
        catch(const char* message) {
            QMessageBox::warning(nullptr, "Error", "An error occured while "
                    "processing file " + file + "<br><br>" + message);
        }
    }
}
