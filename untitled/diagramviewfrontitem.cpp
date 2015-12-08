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
    this->scene->setSceneRect(0,0,w,h);
}

void DiagramViewFrontItem::draw(DiagramViewFrontItem::DRAWITEM drawItem)
{ 
    if(!this->scene->items().isEmpty())
        this->scene->items().clear();
    if(drawItem==DiagramViewFrontItem::ITEM_PILLAR)
        foreach(QGraphicsRectItem *item,this->graphicPillar.graphics())
            this->scene->addItem(item);
}
