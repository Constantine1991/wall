#include "groupitem.h"

GroupItem::GroupItem(QObject *parent):QObject(parent)
{
    this->rotation=0;
}

void GroupItem::createGroup(TYPEGROUP type, QMenu *menu, QGraphicsScene *scene)
{
    this->type=type;
    switch(type)
    {
        case GroupItem::ITEM_WICKET:{
            GraphicsPillarItem *pillar1=new GraphicsPillarItem(menu);
            GraphicsPillarItem *pillar2=new GraphicsPillarItem(menu);
            GraphicsWicketItem *wicket=new GraphicsWicketItem(menu);
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
            GraphicsGate1Item *gate1=new GraphicsGate1Item(menu);
            this->group.append(pillar1);
            this->group.append(pillar2);
            this->group.append(gate1);
            scene->addItem(pillar1);
            scene->addItem(pillar2);
            scene->addItem(gate1);
            break;
        }
        case GroupItem::ITEM_GATE2:{
            GraphicsPillarItem *pillar1=new GraphicsPillarItem(menu);
            GraphicsPillarItem *pillar2=new GraphicsPillarItem(menu);
            GraphicsGate2Item *gate2=new GraphicsGate2Item(menu);
            this->group.append(pillar1);
            this->group.append(pillar2);
            this->group.append(gate2);
            scene->addItem(pillar1);
            scene->addItem(pillar2);
            scene->addItem(gate2);
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

void GroupItem::setBoundingLine(QLineF line)
{
    this->boundingLine.setP1(line.p1());
    this->boundingLine.setP2(line.p2());
    QPointF centreLine=this->centre();
    this->boundingLine.setP1(this->rotatePoint(centreLine,this->boundingLine.p1(),this->rotation));
    this->boundingLine.setP2(this->rotatePoint(centreLine,this->boundingLine.p2(),this->rotation));
}

void GroupItem::setPos(QPointF point)
{
    if(this->group.isEmpty())
        return;
    GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(0));
    GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(1));
    switch(this->type)
    {
        case GroupItem::ITEM_WICKET:{
            this->setBoundingLine(QLineF(QPointF(point.x()-20,point.y()),
                                         QPointF(point.x()+20,point.y())));
            GraphicsWicketItem *wicket=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(2));
            pillar1->setPos(this->boundingLine.p1());
            pillar2->setPos(this->boundingLine.p2());
            wicket->setPosition(this->rotatePoint(pillar1->centre(),
                                                  QPointF(pillar1->centre().x()+pillar1->boundingRect().width()/2,
                                                          pillar1->centre().y()),this->rotation));
            break;
        }
        case GroupItem::ITEM_GATE1:{
            this->setBoundingLine(QLineF(QPointF(point.x()-20,point.y()),
                                         QPointF(point.x()+20,point.y())));
            GraphicsGate1Item *gate1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(2));
            pillar1->setPos(this->boundingLine.p1());
            pillar2->setPos(this->boundingLine.p2());
            QPointF p1=this->rotatePoint(pillar1->centre(),
                                         QPointF(pillar1->centre().x()+pillar1->boundingRect().width()/2,
                                                 pillar1->centre().y()),this->rotation);
            QPointF p2=this->rotatePoint(pillar2->centre(),
                                         QPointF(pillar2->centre().x()-pillar2->boundingRect().width()/2,
                                                 pillar2->centre().y()),this->rotation);
            gate1->setPosition(p1,p2);
            break;
        }
        case GroupItem::ITEM_GATE2:{
            this->setBoundingLine(QLineF(QPointF(point.x()-40,point.y()),
                                         QPointF(point.x()+40,point.y())));
            GraphicsGate2Item *gate2=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(2));
            pillar1->setPos(this->boundingLine.p1());
            pillar2->setPos(this->boundingLine.p2());
            QPointF p1=this->rotatePoint(pillar1->centre(),
                                         QPointF(pillar1->centre().x()+pillar1->boundingRect().width()/2,
                                                 pillar1->centre().y()),this->rotation);
            QPointF p2=this->rotatePoint(pillar2->centre(),
                                         QPointF(pillar2->centre().x()-pillar2->boundingRect().width()/2,
                                                 pillar2->centre().y()),this->rotation);
            gate2->setPosition(p1,p2);
            break;
        }
    }
}

void GroupItem::setRotate(int angle)
{
    this->rotation+=angle;
    this->rotation=this->rotation>360?this->rotation-360:this->rotation;
    GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(0));
    GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(1));
    QPointF centreLine=this->centre();
    this->boundingLine.setP1(this->rotatePoint(centreLine,this->boundingLine.p1(),this->rotation));
    this->boundingLine.setP2(this->rotatePoint(centreLine,this->boundingLine.p2(),this->rotation));
    pillar1->setPos(this->rotatePoint(pillar1->centre(),pillar1->pos(),this->rotation));
    pillar1->setRotation(this->rotation);
    pillar2->setPos(this->rotatePoint(pillar2->centre(),pillar2->pos(),this->rotation));
    pillar2->setRotation(this->rotation);
    switch(this->type)
    {
        case GroupItem::ITEM_WICKET:{
            GraphicsWicketItem *wicket=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(2));
            wicket->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE1:{
            GraphicsGate1Item *gate1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(2));
            gate1->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE2:{
            GraphicsGate2Item *gate2=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(2));
            gate2->setRotate(this->rotation);
            break;
        }
    }
    this->setPos(this->centre());
}

void GroupItem::itemMoveScene(QPointF point)
{
    switch(this->type)
    {
        case GroupItem::ITEM_WICKET:{
            if(this->group.at(0)->isSelected()||this->group.at(1)->isSelected())
                this->setPos(point);
            break;
        }
        case GroupItem::ITEM_GATE1:{
        if(this->group.at(0)->isSelected()||this->group.at(1)->isSelected())
            this->setPos(point);
            break;
        }
        case GroupItem::ITEM_GATE2:{
        if(this->group.at(0)->isSelected()||this->group.at(1)->isSelected())
            this->setPos(point);
            break;
        }
    }
}

QPointF GroupItem::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

QPointF GroupItem::centre()
{
    return QPointF((this->boundingLine.p1().x()+this->boundingLine.p2().x())/2,
                   (this->boundingLine.p1().y()+this->boundingLine.p2().y())/2);
}
