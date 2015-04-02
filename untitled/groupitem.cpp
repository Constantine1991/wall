#include "groupitem.h"
#include "QDebug"

GroupItem::GroupItem(QObject *parent):QObject(parent)
{
    this->rotation=0;
    this->type=GroupItem::ITEM_NONE;
    this->isMouseRelease=false;
    this->isBackUp=false;
}

QList<QGraphicsItem*> GroupItem::create(TYPEGROUP type, QMenu *menu)
{
    this->type=type;
    QList<QGraphicsItem*> result;
    GraphicsPillarItem *pillar1=new GraphicsPillarItem(menu);
    GraphicsPillarItem *pillar2=new GraphicsPillarItem(menu);
    GraphicsPillarItem *pillar3=new GraphicsPillarItem(menu);
    result.append(pillar1);
    result.append(pillar2);
    switch(this->type)
    {
        case GroupItem::ITEM_WICKET:{
            GraphicsWicketItem *wicket=new GraphicsWicketItem(menu);
            result.append(wicket);
            delete pillar3;
            break;
        }
        case GroupItem::ITEM_GATE1:{
            GraphicsGate1Item *gate1=new GraphicsGate1Item(menu);
            result.append(gate1);
            delete pillar3;
            break;
        }
        case GroupItem::ITEM_GATE2:{
           GraphicsGate2Item *gate2=new GraphicsGate2Item(menu);
           result.append(gate2);
           delete pillar3;
           break;
        }
        case GroupItem::ITEM_WICKET_WICKET:{
            GraphicsWicketItem *w1=new GraphicsWicketItem(menu);
            GraphicsWicketItem *w2=new GraphicsWicketItem(menu);
            result.append(pillar3);
            result.append(w1);
            result.append(w2);
            break;
        }
        case GroupItem::ITEM_WICKET_GATE1:{
            GraphicsWicketItem *w=new GraphicsWicketItem(menu);
            GraphicsGate1Item *g1=new GraphicsGate1Item(menu);
            result.append(pillar3);
            result.append(w);
            result.append(g1);
            break;
        }
        case GroupItem::ITEM_WICKET_GATE2:{
            GraphicsWicketItem *w=new GraphicsWicketItem(menu);
            GraphicsGate2Item *g2=new GraphicsGate2Item(menu);
            result.append(pillar3);
            result.append(w);
            result.append(g2);
            break;
        }
        case GroupItem::ITEM_GATE1_GATE1:{
            GraphicsGate1Item *g0=new GraphicsGate1Item(menu);
            GraphicsGate1Item *g1=new GraphicsGate1Item(menu);
            result.append(pillar3);
            result.append(g0);
            result.append(g1);
            break;
        }
        case GroupItem::ITEM_GATE1_GATE2:{
            GraphicsGate1Item *g1=new GraphicsGate1Item(menu);
            GraphicsGate2Item *g2=new GraphicsGate2Item(menu);
            result.append(pillar3);
            result.append(g1);
            result.append(g2);
            break;
        }
        case GroupItem::ITEM_GATE1_WICKET:{
            GraphicsGate1Item *g1=new GraphicsGate1Item(menu);
            GraphicsWicketItem *w=new GraphicsWicketItem(menu);
            result.append(pillar3);
            result.append(g1);
            result.append(w);
            break;
        }
        case GroupItem::ITEM_GATE2_GATE2:{
            GraphicsGate2Item *g0=new GraphicsGate2Item(menu);
            GraphicsGate2Item *g2=new GraphicsGate2Item(menu);
            result.append(pillar3);
            result.append(g0);
            result.append(g2);
            break;
        }
        case GroupItem::ITEM_GATE2_GATE1:{
            GraphicsGate2Item *g2=new GraphicsGate2Item(menu);
            GraphicsGate1Item *g1=new GraphicsGate1Item(menu);
            result.append(pillar3);
            result.append(g2);
            result.append(g1);
            break;
        }
        case GroupItem::ITEM_GATE2_WICKET:{
            GraphicsGate2Item *g2=new GraphicsGate2Item(menu);
            GraphicsWicketItem *w=new GraphicsWicketItem(menu);
            result.append(pillar3);
            result.append(g2);
            result.append(w);
            break;
        }
        default:break;
    }
    return result;
}

void GroupItem::createGroup(TYPEGROUP type,QMenu *menu, QGraphicsScene *scene)
{
    QList<QGraphicsItem*> newGroup=this->create(type,menu);
    this->group.clear();
    this->group.append(newGroup);
    scene->addItem(this->group.at(0));
    scene->addItem(this->group.at(1));
    scene->addItem(this->group.at(2));
    if(this->group.count()==5)
    {
        scene->addItem(this->group.at(3));
        scene->addItem(this->group.at(4));
    }
}

void GroupItem::createGroup(GroupItem *g1, GroupItem *g2, QMenu *menu, QGraphicsScene *scene)
{
    GroupItem::TYPEGROUP t1=g1->isType();
    GroupItem::TYPEGROUP t2=g2->isType();
    QList<QGraphicsItem*> newGroup;
    if(t1==GroupItem::ITEM_WICKET && t2==GroupItem::ITEM_WICKET)
    {
        newGroup=this->create(GroupItem::ITEM_WICKET_WICKET,menu);
        GraphicsWicketItem *wicketG1=qgraphicsitem_cast<GraphicsWicketItem*>(g1->items().at(2));
        GraphicsWicketItem *wicketG2=qgraphicsitem_cast<GraphicsWicketItem*>(g2->items().at(2));
        GraphicsWicketItem *newWicket1=qgraphicsitem_cast<GraphicsWicketItem*>(newGroup.at(3));
        GraphicsWicketItem *newWicket2=qgraphicsitem_cast<GraphicsWicketItem*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newWicket2->setText(QString::number(wicketG2->value()));
    }
    if(t1==GroupItem::ITEM_WICKET && t2==GroupItem::ITEM_GATE1)
    {
        newGroup=this->create(GroupItem::ITEM_WICKET_GATE1,menu);
        GraphicsWicketItem *wicketG1=qgraphicsitem_cast<GraphicsWicketItem*>(g1->items().at(2));
        GraphicsGate1Item *g1G2=qgraphicsitem_cast<GraphicsGate1Item*>(g2->items().at(2));
        GraphicsWicketItem *newWicket1=qgraphicsitem_cast<GraphicsWicketItem*>(newGroup.at(3));
        GraphicsGate1Item *newg1=qgraphicsitem_cast<GraphicsGate1Item*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    if(t1==GroupItem::ITEM_WICKET && t2==GroupItem::ITEM_GATE2)
    {
        newGroup=this->create(GroupItem::ITEM_WICKET_GATE2,menu);
        GraphicsWicketItem *wicketG1=qgraphicsitem_cast<GraphicsWicketItem*>(g1->items().at(2));
        GraphicsGate2Item *g1G2=qgraphicsitem_cast<GraphicsGate2Item*>(g2->items().at(2));
        GraphicsWicketItem *newWicket1=qgraphicsitem_cast<GraphicsWicketItem*>(newGroup.at(3));
        GraphicsGate2Item *newg1=qgraphicsitem_cast<GraphicsGate2Item*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    if(t1==GroupItem::ITEM_GATE1 && t2==GroupItem::ITEM_GATE1)
    {
        newGroup=this->create(GroupItem::ITEM_GATE1_GATE1,menu);
        GraphicsGate1Item *wicketG1=qgraphicsitem_cast<GraphicsGate1Item*>(g1->items().at(2));
        GraphicsGate1Item *g1G2=qgraphicsitem_cast<GraphicsGate1Item*>(g2->items().at(2));
        GraphicsGate1Item *newWicket1=qgraphicsitem_cast<GraphicsGate1Item*>(newGroup.at(3));
        GraphicsGate1Item *newg1=qgraphicsitem_cast<GraphicsGate1Item*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    if(t1==GroupItem::ITEM_GATE1 && t2==GroupItem::ITEM_GATE2)
    {
        newGroup=this->create(GroupItem::ITEM_GATE1_GATE2,menu);
        GraphicsGate1Item *wicketG1=qgraphicsitem_cast<GraphicsGate1Item*>(g1->items().at(2));
        GraphicsGate2Item *g1G2=qgraphicsitem_cast<GraphicsGate2Item*>(g2->items().at(2));
        GraphicsGate1Item *newWicket1=qgraphicsitem_cast<GraphicsGate1Item*>(newGroup.at(3));
        GraphicsGate2Item *newg1=qgraphicsitem_cast<GraphicsGate2Item*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    if(t1==GroupItem::ITEM_GATE1 && t2==GroupItem::ITEM_WICKET)
    {
        newGroup=this->create(GroupItem::ITEM_GATE1_WICKET,menu);
        GraphicsGate1Item *wicketG1=qgraphicsitem_cast<GraphicsGate1Item*>(g1->items().at(2));
        GraphicsWicketItem *g1G2=qgraphicsitem_cast<GraphicsWicketItem*>(g2->items().at(2));
        GraphicsGate1Item *newWicket1=qgraphicsitem_cast<GraphicsGate1Item*>(newGroup.at(3));
        GraphicsWicketItem *newg1=qgraphicsitem_cast<GraphicsWicketItem*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    if(t1==GroupItem::ITEM_GATE2 && t2==GroupItem::ITEM_WICKET)
    {
        newGroup=this->create(GroupItem::ITEM_GATE2_WICKET,menu);
        GraphicsGate2Item *wicketG1=qgraphicsitem_cast<GraphicsGate2Item*>(g1->items().at(2));
        GraphicsWicketItem *g1G2=qgraphicsitem_cast<GraphicsWicketItem*>(g2->items().at(2));
        GraphicsGate2Item *newWicket1=qgraphicsitem_cast<GraphicsGate2Item*>(newGroup.at(3));
        GraphicsWicketItem *newg1=qgraphicsitem_cast<GraphicsWicketItem*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    if(t1==GroupItem::ITEM_GATE2 && t2==GroupItem::ITEM_GATE2)
    {
        newGroup=this->create(GroupItem::ITEM_GATE2_GATE2,menu);
        GraphicsGate2Item *wicketG1=qgraphicsitem_cast<GraphicsGate2Item*>(g1->items().at(2));
        GraphicsGate2Item *g1G2=qgraphicsitem_cast<GraphicsGate2Item*>(g2->items().at(2));
        GraphicsGate2Item *newWicket1=qgraphicsitem_cast<GraphicsGate2Item*>(newGroup.at(3));
        GraphicsGate2Item *newg1=qgraphicsitem_cast<GraphicsGate2Item*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    if(t1==GroupItem::ITEM_GATE2 && t2==GroupItem::ITEM_GATE1)
    {
        newGroup=this->create(GroupItem::ITEM_GATE2_GATE1,menu);
        GraphicsGate2Item *wicketG1=qgraphicsitem_cast<GraphicsGate2Item*>(g1->items().at(2));
        GraphicsGate1Item *g1G2=qgraphicsitem_cast<GraphicsGate1Item*>(g2->items().at(2));
        GraphicsGate2Item *newWicket1=qgraphicsitem_cast<GraphicsGate2Item*>(newGroup.at(3));
        GraphicsGate1Item *newg1=qgraphicsitem_cast<GraphicsGate1Item*>(newGroup.at(4));
        newWicket1->setText(QString::number(wicketG1->value()));
        newg1->setText(QString::number(g1G2->value()));
    }
    GraphicsPillarItem *PillarG1=qgraphicsitem_cast<GraphicsPillarItem*>(g1->items().at(0));
    GraphicsPillarItem *newPillar=qgraphicsitem_cast<GraphicsPillarItem*>(newGroup.at(0));
    newPillar->setGraphicsPillarItem(PillarG1);
    for(int i=0;i<2;i++)
    {
        GraphicsPillarItem *PillarG2=qgraphicsitem_cast<GraphicsPillarItem*>(g2->items().at(i));
        newPillar=qgraphicsitem_cast<GraphicsPillarItem*>(newGroup.at(i+1));
        newPillar->setGraphicsPillarItem(PillarG2);
    }
    foreach(QGraphicsItem *item,newGroup)
        scene->addItem(item);
    this->group.clear();
    this->group.append(newGroup);
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

GroupItem::TYPEGROUP GroupItem::isType()
{
    return this->type;
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

void GroupItem::setBoundingLine(QLineF line)
{
    this->boundingLine.setP1(line.p1());
    this->boundingLine.setP2(line.p2());
    QPointF centreLine=this->centre();
    this->boundingLine.setP1(this->rotatePoint(centreLine,this->boundingLine.p1(),this->rotation));
    this->boundingLine.setP2(this->rotatePoint(centreLine,this->boundingLine.p2(),this->rotation));
}

void GroupItem::setPos(GroupItem::TYPEGROUP typeItem,QGraphicsItem *p1,QGraphicsItem *p2,QGraphicsItem *c,QLineF line)
{
    GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(p1);
    GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(p2);
    pillar1->setPos(line.p1());
    pillar2->setPos(line.p2());
    switch(typeItem)
    {
        case GroupItem::ITEM_WICKET:{

            GraphicsWicketItem *wicket=qgraphicsitem_cast<GraphicsWicketItem*>(c);
            wicket->setPosition(this->centreLine(line));
            break;
        }
        case GroupItem::ITEM_GATE1:{

            GraphicsGate1Item *gate1=qgraphicsitem_cast<GraphicsGate1Item*>(c);
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
            GraphicsGate2Item *gate2=qgraphicsitem_cast<GraphicsGate2Item*>(c);
            QPointF p1=this->rotatePoint(pillar1->centre(),
                                         QPointF(pillar1->centre().x()+pillar1->boundingRect().width()/2,
                                                 pillar1->centre().y()),this->rotation);
            QPointF p2=this->rotatePoint(pillar2->centre(),
                                         QPointF(pillar2->centre().x()-pillar2->boundingRect().width()/2,
                                                 pillar2->centre().y()),this->rotation);
            gate2->setPosition(p1,p2);
            break;
        }
        default:break;
    }
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
    switch(this->type)
    {
        case ITEM_WICKET:{
            this->setBoundingLine(QLineF(QPointF(point.x()-40,point.y()),
                                         QPointF(point.x()+40,point.y())));
            this->setPos(ITEM_WICKET,this->group.at(0),this->group.at(1),this->group.at(2),this->boundingLine);
            break;
        }
        case ITEM_GATE1:{
            this->setBoundingLine(QLineF(QPointF(point.x()-40,point.y()),
                                         QPointF(point.x()+40,point.y())));
            this->setPos(ITEM_GATE1,this->group.at(0),this->group.at(1),this->group.at(2),this->boundingLine);
            break;
        }
        case ITEM_GATE2:{
            this->setBoundingLine(QLineF(QPointF(point.x()-40,point.y()),
                                         QPointF(point.x()+40,point.y())));
            this->setPos(ITEM_GATE2,this->group.at(0),this->group.at(1),this->group.at(2),this->boundingLine);
            break;
        }
        case ITEM_WICKET_WICKET:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_WICKET,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_WICKET,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_WICKET_GATE1:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_WICKET,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_GATE1,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_WICKET_GATE2:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_WICKET,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_GATE2,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_GATE1_GATE1:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_GATE1,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_GATE1,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_GATE1_GATE2:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_GATE1,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_GATE2,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_GATE1_WICKET:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_GATE1,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_WICKET,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_GATE2_WICKET:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_GATE2,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_WICKET,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_GATE2_GATE2:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_GATE2,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_GATE2,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        case ITEM_GATE2_GATE1:{
            this->setBoundingLine(QLineF(QPointF(point.x()-80,point.y()),
                                         QPointF(point.x()+80,point.y())));
            QLineF line;
            line.setP1(this->boundingLine.p1());
            line.setP2(this->centre());
            this->setPos(ITEM_GATE2,this->group.at(0),this->group.at(1),this->group.at(3),line);
            line.setP1(line.p2());
            line.setP2(this->boundingLine.p2());
            this->setPos(ITEM_GATE1,this->group.at(1),this->group.at(2),this->group.at(4),line);
            break;
        }
        default:break;
    }
}

void GroupItem::setPosItem(QPointF point, QGraphicsItem *item)
{
    if(this->type==GroupItem::ITEM_NONE)
        return;
    int at=this->group.indexOf(item);
    at=at==0?1:-1;
    if((int)this->type<3)
        this->setBoundingLine(QLineF(point,QPointF(point.x()+80*at,point.y())));
    else this->setBoundingLine(QLineF(point,QPointF(point.x()+160*at,point.y())));
    this->setPos(this->centre());
}

QPointF GroupItem::pos()
{
    return this->centre();
}

void GroupItem::setType(GroupItem::TYPEGROUP type)
{
    this->type=type;
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
        case GroupItem::ITEM_WICKET_WICKET:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsWicketItem *w1=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsWicketItem *w2=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_WICKET_GATE1:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsWicketItem *w1=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsGate1Item *w2=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_WICKET_GATE2:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsWicketItem *w1=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsGate2Item *w2=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE1_GATE1:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsGate1Item *w1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsGate1Item *w2=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE1_GATE2:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsGate1Item *w1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsGate2Item *w2=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE1_WICKET:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsGate1Item *w1=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsWicketItem *w2=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE2_WICKET:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsGate2Item *w1=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsWicketItem *w2=qgraphicsitem_cast<GraphicsWicketItem*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE2_GATE2:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsGate2Item *w1=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsGate2Item *w2=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
        case GroupItem::ITEM_GATE2_GATE1:{
            GraphicsPillarItem *pillar3=qgraphicsitem_cast<GraphicsPillarItem*>(this->group.at(2));
            pillar3->setPos(this->rotatePoint(pillar3->centre(),pillar3->pos(),this->rotation));
            pillar3->setRotation(this->rotation);
            GraphicsGate2Item *w1=qgraphicsitem_cast<GraphicsGate2Item*>(this->group.at(3));
            w1->setRotate(this->rotation);
            GraphicsGate1Item *w2=qgraphicsitem_cast<GraphicsGate1Item*>(this->group.at(4));
            w2->setRotate(this->rotation);
            break;
        }
    default:break;
    }
    this->setPos(this->centre());
}

int GroupItem::rot()
{
    return this->rotation;
}

void GroupItem::itemMoveScene(QPointF point)
{
    if(this->type==GroupItem::ITEM_WICKET || this->type==GroupItem::ITEM_GATE1 || this->type==GroupItem::ITEM_GATE2)
        if(this->group.at(0)->isSelected()||this->group.at(1)->isSelected())
        {
            this->setPos(point);
            return;
        }
    if(this->group.at(0)->isSelected()||this->group.at(1)->isSelected()||this->group.at(2)->isSelected())
        this->setPos(point);
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
