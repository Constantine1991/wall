#include "diagramviewfrontitem.h"
#include "QDebug"

DiagramViewFrontItem::DiagramViewFrontItem(QWidget *parent):QGraphicsView(parent)
{
    this->scene=new QGraphicsScene();
    this->setScene(this->scene);
    this->showItemText=false;
}

DiagramViewFrontItem::~DiagramViewFrontItem()
{
    if(!this->scene->items().isEmpty())
    {
        qDebug()<<"~DiagramViewFrontItem delete objects";
        this->scene->items().clear();
    }
    this->clearItemText();
}

void DiagramViewFrontItem::setRectScene(int w, int h)
{
    this->widthScene=w;
    this->heightScene=h;
    this->scene->setSceneRect(0,0,w,h);
}

void DiagramViewFrontItem::showText(bool show)
{
    this->showItemText=show;
}

void DiagramViewFrontItem::setPosText(int x, int y, int offsetY)
{
    this->pos_x=x;
    this->pos_y=y;
    this->offsetY=offsetY;
}

void DiagramViewFrontItem::draw(DiagramViewFrontItem::DRAWITEM drawItem)
{ 
    if(!this->scene->items().isEmpty())
        this->scene->items().clear();
    if(this->showItemText)
    {
        this->clearItemText();
        if(drawItem==DiagramViewFrontItem::ITEM_PILLAR)
            this->createItemsText(this->graphicPillar.row());
        if(drawItem==DiagramViewFrontItem::ITEM_WALL || drawItem==DiagramViewFrontItem::ITEM_PILLAR_WALL)
            this->createItemsText(this->graphicWall.row());
        foreach(QGraphicsTextItem *text,this->itemText)
            this->scene->addItem(text);
    }
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

void DiagramViewFrontItem::createItemsText(int count)
{
    int offsetY=this->pos_y-this->offsetY;
    for(int i=0;i<count;i++)
    {
        this->itemText.append(this->text(this->pos_x,offsetY,QString::number(i+1)));
        offsetY-=this->offsetY;
    }
}

QGraphicsTextItem *DiagramViewFrontItem::text(int x, int y,QString caption)
{
    QGraphicsTextItem *item=new QGraphicsTextItem(caption);
    item->setPos(x,y);
    return item;
}

void DiagramViewFrontItem::clearItemText()
{
    if(this->itemText.isEmpty())
        return;
    foreach(QGraphicsTextItem *text,this->itemText)
        delete text;
    this->itemText.clear();
}
