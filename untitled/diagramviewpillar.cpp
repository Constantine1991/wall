#include "diagramviewpillar.h"

DiagramViewPillar::DiagramViewPillar(QWidget *parent):QGraphicsView(parent)
{
    this->graphicsScene=new QGraphicsScene(QRectF(0,0,480,550));
    this->setScene(this->graphicsScene);
    this->height=0;
    this->insertBottom=0;
    this->insertTop=0;
    this->pazzle=false;
    this->top=false;
}

void DiagramViewPillar::setHeight(int height)
{
    this->height=height;
    this->rendering();
}

void DiagramViewPillar::setInsertBottom(int insertBottom)
{
    this->insertBottom=insertBottom;
    this->rendering();
}

void DiagramViewPillar::setInsertTop(int insertTop)
{
    this->insertTop=insertTop;
    this->rendering();
}

void DiagramViewPillar::setColorRow(int index, QColor color)
{
    this->color.removeAt(index-1);
    this->color.insert(index-1,color);
    this->rendering();
}

void DiagramViewPillar::setColorAllRow(QColor color)
{
    this->color.clear();
    for(int i=0;i<this->row();i++)
        this->color.append(color);
    this->rendering();
}

void DiagramViewPillar::setEnabledTop(bool top)
{
    this->top=top;
    this->rendering();
}

void DiagramViewPillar::setColorTop(QColor color)
{
    this->colorTop=color;
    this->rendering();
}

void DiagramViewPillar::setEnabledPazzle(bool enable, QColor color1, QColor color2)
{
    this->pazzle=enable;
    this->colorPazzle1=color1;
    this->colorPazzle2=color2;
    this->rendering();
}

QColor DiagramViewPillar::colorRow(int index)
{
    return this->color.at(index);
}

int DiagramViewPillar::row()
{
    return qFloor(this->height/this->heightBrick);
}

void DiagramViewPillar::setRenderingSide(int renderingSide)
{
    switch(renderingSide)
    {
        case 0:this->renderingSide=this->FRONT; break;
        case 1:this->renderingSide=this->BACK;break;
        case 2:this->renderingSide=this->LEFT;break;
        case 3:this->renderingSide=this->RIGHT;break;

    }
    this->rendering();
}

void DiagramViewPillar::createPillar()
{
    int y=this->graphicsScene->height()-50;
    int Row=this->row();
    for(int i=0;i<Row;i++)
    {
        QGraphicsRectItem *itemRowGraphics=new QGraphicsRectItem();
        itemRowGraphics->setBrush(QBrush(this->color.at(i)));
        itemRowGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        itemRowGraphics->setRect(225,y,100,25);
        QGraphicsTextItem *itemText=new QGraphicsTextItem(QString::number(i+1));
        this->graphicsScene->addItem(itemRowGraphics);
        itemText->setPos(205,y-5);
        this->graphicsScene->addItem(itemText);
        y-=25;
    }
    QGraphicsRectItem *itemInsertBottomGraphics=new QGraphicsRectItem();
    itemInsertBottomGraphics->setBrush(QBrush(Qt::gray));
    itemInsertBottomGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    itemInsertBottomGraphics->setRect(260,this->graphicsScene->height()-25-this->insertBottom/this->heightBrick*25,20,
                                      this->insertBottom/this->heightBrick*25);
    this->graphicsScene->addItem(itemInsertBottomGraphics);
    QGraphicsRectItem *itemInsertTopGraphics=new QGraphicsRectItem();
    itemInsertTopGraphics->setBrush(QBrush(Qt::gray));
    itemInsertTopGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    itemInsertTopGraphics->setRect(260,y+this->heightBrick,20,this->insertTop);
    this->graphicsScene->addItem(itemInsertTopGraphics);
    if(this->top)
    {
        QPolygonF polygon;
        polygon<<QPointF(55.0f,0.0f)<<QPointF(0.0f,25.0f)<<QPointF(110.0f,25.0f);
        QGraphicsPolygonItem *itemTopGraphics=new QGraphicsPolygonItem(polygon);
        itemTopGraphics->setBrush(QBrush(this->colorTop));
        itemTopGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        itemTopGraphics->setPos(220,y-1);
        this->graphicsScene->addItem(itemTopGraphics);
    }
}

void DiagramViewPillar::createPillarPazzle()
{
    int y=this->graphicsScene->height()-50;
    int Row=this->row();
    for(int i=0;i<Row;i++)
    {
        QGraphicsRectItem *itemGraphicsBrickSmall=new QGraphicsRectItem();
        QGraphicsRectItem *itemGraphicsBrickBig=new QGraphicsRectItem();
        itemGraphicsBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        itemGraphicsBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        if(i % 2 ==0)
        {
            if(this->renderingSide==this->FRONT || this->renderingSide==this->BACK)
                itemGraphicsBrickSmall->setBrush(QBrush(this->colorPazzle1));
            else itemGraphicsBrickSmall->setBrush(QBrush(this->colorPazzle2));
            itemGraphicsBrickSmall->setRect(225,y,25,25);
            if(this->renderingSide==this->FRONT || this->renderingSide==this->BACK)
                itemGraphicsBrickBig->setBrush(QBrush(this->colorPazzle2));
            else itemGraphicsBrickBig->setBrush(QBrush(this->colorPazzle1));
            itemGraphicsBrickBig->setRect(250,y,75,25);
        }else{
            if(this->renderingSide==this->FRONT || this->renderingSide==this->BACK)
                itemGraphicsBrickBig->setBrush(QBrush(this->colorPazzle2));
            else itemGraphicsBrickBig->setBrush(QBrush(this->colorPazzle1));
            itemGraphicsBrickBig->setRect(225,y,75,25);
            if(this->renderingSide==this->FRONT || this->renderingSide==this->BACK)
                itemGraphicsBrickSmall->setBrush(QBrush(this->colorPazzle1));
            else itemGraphicsBrickSmall->setBrush(QBrush(this->colorPazzle2));
            itemGraphicsBrickSmall->setRect(300,y,25,25);
        }
        this->graphicsScene->addItem(itemGraphicsBrickSmall);
        this->graphicsScene->addItem(itemGraphicsBrickBig);
        QGraphicsTextItem *itemText=new QGraphicsTextItem(QString::number(i+1));
        itemText->setPos(205,y-5);
        this->graphicsScene->addItem(itemText);
        y-=25;
    }
    QGraphicsRectItem *itemInsertBottomGraphics=new QGraphicsRectItem();
    itemInsertBottomGraphics->setBrush(QBrush(Qt::gray));
    itemInsertBottomGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    itemInsertBottomGraphics->setRect(260,this->graphicsScene->height()-25-this->insertBottom/this->heightBrick*25,20,
                                      this->insertBottom/this->heightBrick*25);
    this->graphicsScene->addItem(itemInsertBottomGraphics);
    QGraphicsRectItem *itemInsertTopGraphics=new QGraphicsRectItem();
    itemInsertTopGraphics->setBrush(QBrush(Qt::gray));
    itemInsertTopGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    itemInsertTopGraphics->setRect(260,y+25,20,this->insertTop);
    this->graphicsScene->addItem(itemInsertTopGraphics);
    if(this->top)
    {
        QPolygonF polygon;
        polygon<<QPointF(55.0f,0.0f)<<QPointF(0.0f,25.0f)<<QPointF(110.0f,25.0f);
        QGraphicsPolygonItem *itemTopGraphics=new QGraphicsPolygonItem(polygon);
        itemTopGraphics->setBrush(QBrush(this->colorTop));
        itemTopGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        itemTopGraphics->setPos(220,y-1);
        this->graphicsScene->addItem(itemTopGraphics);
    }
}

void DiagramViewPillar::rendering()
{
    this->graphicsScene->clear();
    if(this->height==0)
    {
        this->color.clear();
        return;
    }
    int rowPillar=this->row();
    if(!this->color.isEmpty())
        for(int i=0;i<rowPillar;i++)
            this->color.append(QColor(Qt::white));
    if(this->color.count()-1<rowPillar)
    {
        for(int i=this->color.count()-1;i<rowPillar;i++)
            this->color.append(QColor(Qt::white));
    }
    else for(int i=this->color.count()-1;i>rowPillar;i--)
            this->color.removeAt(i);
    if(rowPillar*25+(25*(int)this->top)<550)
        this->graphicsScene->setSceneRect(0,0,480,550);
    else this->graphicsScene->setSceneRect(0,0,480,rowPillar*25+(25*(int)this->top)+100);
    if(this->pazzle)
        this->createPillarPazzle();
    else this->createPillar();
}
