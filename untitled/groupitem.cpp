#include "groupitem.h"

GroupItem::GroupItem(QObject *parent):QObject(parent)
{
}

void GroupItem::createGroup(TYPEGROUP type, QMenu *menu, QGraphicsScene *scene)
{
    this->type=type;
    switch(type)
    {
        case GroupItem::ITEM_WICKET:{
            GraphicsPillarItem *pillar1=new GraphicsPillarItem(menu);
            GraphicsPillarItem *pillar2=new GraphicsPillarItem(menu);
            GraphicsWicketItem *wicket=new GraphicsWicketItem();
            this->group.append(pillar1);
            this->group.append(pillar2);
            this->group.append(wicket);
            scene->addItem(pillar1);
            scene->addItem(pillar2);
            scene->addItem(wicket);
            break;
        }
    }
}

void GroupItem::setPos(QPointF point)
{
    if(this->group.isEmpty())
        return;
    switch(this->type)
    {
        case GroupItem::ITEM_WICKET:{
            GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(0));
            GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(1));
            GraphicsWicketItem *wicket=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(2));
            pillar1->setPos(point.x()-20,point.y());
            pillar2->setPos(point.x()+20,point.y());
            wicket->setPosition(QPointF(pillar1->centre().x()+pillar1->boundingRect().width()/2,pillar1->centre().y()));
        }
    }
}
