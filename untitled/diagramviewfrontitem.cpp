#include "diagramviewfrontitem.h"
#include "QDebug"

DiagramViewFrontItem::DiagramViewFrontItem(QWidget *parent):QGraphicsView(parent)
{
    this->scene=new QGraphicsScene();
    this->setScene(this->scene);
}

DiagramViewFrontItem::~DiagramViewFrontItem()
{
    if(!this->scene->items().isEmpty())
    {
        qDebug()<<"~DiagramViewFrontItem delete objects";
        this->scene->items().clear();
    }
}

void DiagramViewFrontItem::setRectScene(int w, int h)
{
    this->widthScene=w;
    this->heightScene=h;
    this->scene->setSceneRect(0,0,w,h);
}

void DiagramViewFrontItem::draw(DiagramViewFrontItem::DRAWITEM drawItem)
{ 
    if(!this->scene->items().isEmpty())
        this->scene->items().clear();
    if(drawItem==DiagramViewFrontItem::ITEM_PILLAR || drawItem==DiagramViewFrontItem::ITEM_PILLAR_WALL)
    {
        this->resizeRectScene(this->scene->sceneRect().width(),this->graphicPillar.boundingRectHeight());
        this->graphicPillar.setPos(this->graphicPillar.pos().x(),this->scene->sceneRect().height());
        foreach(QGraphicsRectItem *item,this->graphicPillar.update())
            this->scene->addItem(item);
    }
    if(drawItem==DiagramViewFrontItem::ITEM_WALL || drawItem==DiagramViewFrontItem::ITEM_PILLAR_WALL)
    {
        this->resizeRectScene(this->graphicWall.boundingRectWidth(),this->scene->sceneRect().height());
        foreach(QGraphicsRectItem *item,this->graphicWall.update())
            this->scene->addItem(item);
    }
}

void DiagramViewFrontItem::resizeRectScene(int width, int height)
{
    if(this->heightScene<height)
        this->scene->setSceneRect(0,0,this->scene->sceneRect().width(),height);
    else this->scene->setSceneRect(0,0,this->scene->sceneRect().width(),this->heightScene);
    if(this->scene->sceneRect().width()<width)
        this->scene->setSceneRect(0,0,width,this->scene->sceneRect().height());
    else this->scene->setSceneRect(0,0,this->widthScene,this->scene->sceneRect().height());
}
