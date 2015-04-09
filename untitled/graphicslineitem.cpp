#include "graphicslineitem.h"
#include "QDebug"

GraphicsLineItem::GraphicsLineItem(QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsLineItem(parent,scene)
{
    this->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges,false);
    this->text=new QGraphicsTextItem("0",this);
    this->line1=new QGraphicsLineItem(this);
    this->line1->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->line1->setFlag(QGraphicsItem::ItemIsSelectable,false);
    this->line1->setFlag(QGraphicsItem::ItemSendsGeometryChanges,false);
    this->line2=new QGraphicsLineItem(this);
    this->line2->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->line2->setFlag(QGraphicsItem::ItemIsSelectable,false);
    this->line2->setFlag(QGraphicsItem::ItemSendsGeometryChanges,false);
}

void GraphicsLineItem::setPoints(QPointF p1, QPointF p2, QGraphicsScene *scene)
{
    GraphicsPillarItem *pillar1=this->pillar(p1,scene);
    GraphicsPillarItem *pillar2=this->pillar(p2,scene);
    if(pillar1==NULL ||pillar2==NULL)
        return;
    this->setLine(QLineF(p1,p2));
    QPointF point=this->rotatePoint(pillar1->centre(),QPointF(pillar1->centre().x()+50,pillar1->y()),
                                    this->rotationLocalCoords()+90);
    this->line1->setLine(QLineF(pillar1->centre(),point));
    point=this->rotatePoint(pillar2->centre(),QPointF(pillar2->centre().x()+50,pillar2->y()),
                            this->rotationLocalCoords()+90);
    this->line2->setLine(QLineF(pillar2->centre(),point));
    this->setLine(QLineF(this->line1->line().p2(),this->line2->line().p2()));
    this->text->setPlainText(QString::number(this->width(pillar1,pillar2,scene)));
    this->updatePosText();
    scene->addItem(this);
}

QPointF GraphicsLineItem::rotatePoint(QPointF center, QPointF point, float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

QPointF GraphicsLineItem::center()
{
    return QPointF((this->line().p1().x()+this->line().p2().x())/2,(this->line().p1().y()+this->line().p2().y())/2);
}

float GraphicsLineItem::rotationLocalCoords()
{
    QPointF p1=this->line().p1();
    QPointF p2=this->line().p2();
    float angle=::atan2(p1.y()-p2.y(),p1.x()-p2.x())/PI*180;
    angle=angle<0?angle+360:angle;
    return angle;
}

void GraphicsLineItem::updatePosText()
{

    QPointF centreLine=this->center();
    this->text->setRotation(this->rotationLocalCoords()+180);
    this->text->setPos(centreLine);
}

GraphicsPillarItem *GraphicsLineItem::pillar(QPointF pos, QGraphicsScene *scene)
{
    QList<QGraphicsItem*> listItem=scene->items(pos);
    if(!listItem.isEmpty())
        foreach(QGraphicsItem *item,listItem)
            if(item->type()==GraphicsPillarItem::Type)
                return qgraphicsitem_cast<GraphicsPillarItem*>(item);
    return NULL;
}

int GraphicsLineItem::width(GraphicsPillarItem *p1, GraphicsPillarItem *p2, QGraphicsScene *scene)
{
    QPolygonF bounding;
    bounding.append(this->rotatePoint(p1->centre(),QPointF(p1->centre().x()+p1->boundingRect().width()/2,p1->centre().y()),
                                      this->rotationLocalCoords()+90));
    bounding.append(this->rotatePoint(p1->centre(),QPointF(p1->centre().x()+p1->boundingRect().width()/2,p1->centre().y()),
                                      this->rotationLocalCoords()-90));
    bounding.append(this->rotatePoint(p2->centre(),QPointF(p2->centre().x()+p1->boundingRect().width()/2,p2->centre().y()),
                                      this->rotationLocalCoords()-90));
    bounding.append(this->rotatePoint(p2->centre(),QPointF(p2->centre().x()+p2->boundingRect().width()/2,p2->centre().y()),
                                      this->rotationLocalCoords()+90));
    int w=0;
    QList<QGraphicsItem*> objects=scene->items(bounding);
    foreach(QGraphicsItem *item,objects)
        switch(item->type())
        {
            case GraphicsWallItem::Type:{
                GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(item);
                bool isValidatePillar1=this->isPillar(objects,wall->line().p1());
                bool isValidatePillar2=this->isPillar(objects,wall->line().p2());
                if(isValidatePillar1 && isValidatePillar2)
                    w+=wall->width()==0?0:wall->width()+35;
                break;
            }
            case GraphicsGate1Item::Type:{
                GraphicsGate1Item *gate1=qgraphicsitem_cast<GraphicsGate1Item*>(item);
                w+=gate1->value()==0?0:gate1->value()+35;
                break;
            }
            case GraphicsGate2Item::Type:{
                GraphicsGate2Item *gate2=qgraphicsitem_cast<GraphicsGate2Item*>(item);
                w+=gate2->value()==0?0:gate2->value()+35;
                break;
            }
            case GraphicsWicketItem::Type:{
                GraphicsWicketItem *wicket=qgraphicsitem_cast<GraphicsWicketItem*>(item);
                w+=wicket->value()==0?0:wicket->value()+35;
                break;
            }
            default: break;
        }
    return w;
}

bool GraphicsLineItem::isPillar(QList<QGraphicsItem*> items, QPointF point)
{
    if(!items.isEmpty())
    {
        foreach(QGraphicsItem *item,items)
            if(item->type()==GraphicsPillarItem::Type)
            {
                GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
                if(((pillar->centre().x()+pillar->boundingRect().width()/2)>=point.x())&&
                   ((pillar->centre().x()-pillar->boundingRect().width()/2)<=point.x())&&
                   ((pillar->centre().y()+pillar->boundingRect().height()/2)>=point.y())&&
                   ((pillar->centre().y()-pillar->boundingRect().height()/2)<=point.y()))
                    return true;
            }
    }
    return false;
}
