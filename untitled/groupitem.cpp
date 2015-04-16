#include "groupitem.h"
#include "QDebug"

GroupItem::GroupItem(QObject *parent):QObject(parent)
{
    this->rotation=0;
    this->isMouseRelease=false;
    this->isBackUp=false;
}

QList<QGraphicsItem*> GroupItem::create(TYPEGROUP type, QMenu *menu)
{
    QList<QGraphicsItem*> result;
    GraphicsPillarItem *pillar1=new GraphicsPillarItem(menu);
    result.append(pillar1);
    switch(type)
    {
        case GroupItem::ITEM_WICKET:{
            GraphicsWicketItem *wicket=new GraphicsWicketItem(menu);
            result.append(wicket);
            break;
        }
        case GroupItem::ITEM_GATE1:{
            GraphicsGate1Item *gate1=new GraphicsGate1Item(menu);
            result.append(gate1);
            break;
        }
        case GroupItem::ITEM_GATE2:{
           GraphicsGate2Item *gate2=new GraphicsGate2Item(menu);
           result.append(gate2);
           break;
        }
        default:break;
    }
    GraphicsPillarItem *pillar2=new GraphicsPillarItem(menu);
    result.append(pillar2);
    return result;
}

void GroupItem::createGroup(TYPEGROUP type,QMenu *menu, QGraphicsScene *scene)
{
    QList<QGraphicsItem*> newGroup=this->create(type,menu);
    this->type.clear();
    this->type.append(type);
    this->group.clear();
    this->group.append(newGroup);
    foreach(QGraphicsItem *item,this->group)
        scene->addItem(item);
}

void GroupItem::addGroup(GroupItem::TYPEGROUP type, QString value, QMenu *menu, QGraphicsScene *scene)
{
    QList<QGraphicsItem*> appendGroup=this->create(type,menu);
    this->type.append(type);
    switch(type)
    {
        case GroupItem::ITEM_WICKET:{
            GraphicsWicketItem *object=qgraphicsitem_cast<GraphicsWicketItem*>(appendGroup.at(1));
            object->setText(value);
            break;
        }
        case GroupItem::ITEM_GATE1:{
            GraphicsGate1Item *object=qgraphicsitem_cast<GraphicsGate1Item*>(appendGroup.at(1));
            object->setText(value);
            break;
        }
        case GroupItem::ITEM_GATE2:{
            GraphicsGate2Item *object=qgraphicsitem_cast<GraphicsGate2Item*>(appendGroup.at(1));
            object->setText(value);
            break;
        }
        default:break;
    }
    appendGroup.removeAt(0);
    this->group.append(appendGroup);
    foreach(QGraphicsItem *item,appendGroup)
        scene->addItem(item);
}

void GroupItem::addGroup(GroupItem *group, QMenu *menu, QGraphicsScene *scene)
{
    QList<QGraphicsItem*> appendGroup;
    foreach(GroupItem::TYPEGROUP t,group->types())
    {
        appendGroup.append(this->create(t,menu));
        this->type.append(t);
    }
    appendGroup.removeAt(0);
    for(int i=1;i<group->items().count()-1;i++)
    {
        switch(group->items().at(i)->type())
        {
            case GraphicsPillarItem::Type:{
                GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(appendGroup.at(i-1));
                GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(group->items().at(i));
                pillar1->setGraphicsPillarItem(pillar2);
                break;
            }
            case GraphicsWicketItem::Type:{
                GraphicsWicketItem *object1=qgraphicsitem_cast<GraphicsWicketItem*>(appendGroup.at(i-1));
                GraphicsWicketItem *object2=qgraphicsitem_cast<GraphicsWicketItem*>(group->items().at(i));
                object1->setText(QString::number(object2->value()));
                break;
            }
            case GraphicsGate1Item::Type:{
                GraphicsGate1Item *object1=qgraphicsitem_cast<GraphicsGate1Item*>(appendGroup.at(i-1));
                GraphicsGate1Item *object2=qgraphicsitem_cast<GraphicsGate1Item*>(group->items().at(i));
                object1->setText(QString::number(object2->value()));
                break;
            }
            case GraphicsGate2Item::Type:{
                GraphicsGate2Item *object1=qgraphicsitem_cast<GraphicsGate2Item*>(appendGroup.at(i-1));
                GraphicsGate2Item *object2=qgraphicsitem_cast<GraphicsGate2Item*>(group->items().at(i));
                object1->setText(QString::number(object2->value()));
                break;
            }
            default:break;
        }
    }

    this->group.append(appendGroup);
    foreach(QGraphicsItem *item,appendGroup)
        scene->addItem(item);
}

QList<GroupItem::TYPEGROUP> GroupItem::types()
{
    return this->type;
}

bool GroupItem::isItem(QGraphicsItem *item)
{
    foreach(QGraphicsItem *itemGroup,this->group)
    if(item==itemGroup)
        return true;
    return false;
}

QList<QGraphicsItem*> GroupItem::items()
{
    return this->group;
}

void GroupItem::backUp()
{
    if(this->lastPos.isEmpty())
        return;
    this->isBackUp=true;
    this->setPos(this->lastPos.last());
    if(this->lastPos.count()>1)
        this->lastPos.removeLast();
    this->isBackUp=false;
}

void GroupItem::clearBackUp()
{
    this->lastPos.clear();
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
    if(this->lastPos.isEmpty()&&!this->isBackUp)
        this->lastPos.append(point);
    if(this->isMouseRelease&&!this->isBackUp)
    {
        this->lastPos.append(point);
        this->isMouseRelease=false;
    }
    this->setBoundingLine(QLineF(QPointF(point.x()-40*this->type.count(),point.y()),
                                 QPointF(point.x()+40*this->type.count(),point.y())));
    float angle=::atan2(this->boundingLine.p1().y()-this->boundingLine.p2().y(),
                        this->boundingLine.p1().x()-this->boundingLine.p2().x())/PI*180;
    angle=angle<0?angle+360:angle;
    angle=angle==0?180:angle;
    GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.first());
    pillar->setPosition(this->boundingLine.p1());
    pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.last());
    pillar->setPosition(this->boundingLine.p2());
    QPointF p=this->boundingLine.p1();
    for(int i=2;i<this->group.count()-1;i+=2)
    {
        pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(i));
        pillar->setPosition(this->rotatePoint(p,QPointF(p.x()-80,p.y()),angle));
        p=pillar->pos();
    }
    QLineF line;
    line.setP1(this->boundingLine.p1());
    for(int i=1;i<this->group.count()-1;i+=2)
    {
        line.setP2(this->rotatePoint(line.p1(),QPointF(line.p1().x()-80,line.p1().y()),angle));
        switch(this->group.at(i)->type())
        {
            case GraphicsWicketItem::Type:{
                GraphicsWicketItem  *wicket=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(i));
                wicket->setPosition(this->centreLine(line));
                break;
            }
            case GraphicsGate1Item::Type:{
                GraphicsGate1Item *gate1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(i));
                gate1->setPosition(line.p1(),line.p2());
                break;
            }
            case GraphicsGate2Item::Type:{
                GraphicsGate2Item *gate2=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(i));
                gate2->setPosition(line.p1(),line.p2());
                break;
            }
            default:break;
        }
        line.setP1(line.p2());
    }
}

void GroupItem::setOffsetPos(QPointF point,int offset)
{
    int lengthLineX=qAbs(this->boundingLine.p1().x()-this->boundingLine.p2().x());
    int lengthLineY=qAbs(this->boundingLine.p1().y()-this->boundingLine.p2().y());
    QLineF line;
    line.setP1(point);
    line.setP2(this->rotatePoint(point,QPointF(point.x()+lengthLineX+offset,
                                               point.y()),this->rotation));
    this->setPos(this->centreLine(line));
}

QPointF GroupItem::pos()
{    
    return this->centre();
}

void GroupItem::setRotate(int angle)
{
    this->rotation+=angle;
    this->rotation=this->rotation>360?this->rotation-360:this->rotation;
    for(int i=0;i<this->group.count();i+=2)
    {
      GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(i));
      pillar->setRotation(this->rotation);
      pillar->setPos(this->rotatePoint(pillar->centre(),pillar->pos(),this->rotation));
    }
    for(int i=1;i<this->group.count()-1;i+=2)
    {
        switch(this->group.at(i)->type())
        {
        case GraphicsWicketItem::Type:{
            GraphicsWicketItem *wicket=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(i));
            wicket->setRotate(this->rotation);
            break;
        }
        case GraphicsGate1Item::Type:{
            GraphicsGate1Item *gate1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(i));
            gate1->setRotate(this->rotation);
            break;
        }
        case GraphicsGate2Item::Type:{
            GraphicsGate2Item *gate2=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(i));
            gate2->setRotate(this->rotation);
            break;
        }
        default:break;
        }
    }
    this->setPos(this->centre());
}

int GroupItem::rot()
{
    return this->rotation;
}

void GroupItem::itemMoveScene(QPointF point)
{
    foreach(QGraphicsItem *item,this->group)
        if(item->type()==GraphicsPillarItem::Type && item->isSelected())
        {
            this->setPos(point);
            return;
        }
}

void GroupItem::mouseRelease()
{
    this->isMouseRelease=true;
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

QPointF GroupItem::centreLine(QLineF line)
{
    return QPointF((line.p1().x()+line.p2().x())/2,
                   (line.p1().y()+line.p2().y())/2);
}
