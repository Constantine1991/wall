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
        case GroupItem::ITEM_GATE1:{
            GraphicsPillarItem *pillar1=new GraphicsPillarItem(menu);
            GraphicsPillarItem *pillar2=new GraphicsPillarItem(menu);
            GraphicsGate1Item *gate1=new GraphicsGate1Item();
            this->group.append(pillar1);
            this->group.append(pillar2);
            this->group.append(gate1);
            scene->addItem(pillar1);
            scene->addItem(pillar2);
            scene->addItem(gate1);
            break;
        }
    }
}

bool GroupItem::isWicket(QGraphicsItem *item)
{
    if(item==this->group.at(2))
        return true;
    return false;
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
            break;
        }
        case GroupItem::ITEM_GATE1:{
            GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(0));
            GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(1));
            GraphicsGate1Item *gate1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(2));
            pillar1->setPos(point.x()-20,point.y());
            pillar2->setPos(point.x()+20,point.y());
            gate1->setPosition(QPointF(pillar1->centre().x()+pillar1->boundingRect().width()/2,pillar1->centre().y()),
                               QPointF(pillar2->centre().x()-pillar2->boundingRect().width()/2,pillar2->centre().y()));
            break;
        }
    }
}

void GroupItem::itemMoveScene(QPointF point)
{
    switch(this->type)
    {
        case GroupItem::ITEM_WICKET:{
            if(this->group.at(0)->isSelected())
                this->setPos(QPointF(point.x()+20,point.y()));
            if(this->group.at(1)->isSelected())
                this->setPos(QPointF(point.x()-20,point.y()));
            break;
        }
    }
}
