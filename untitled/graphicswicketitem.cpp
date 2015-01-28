#include "graphicswicketitem.h"

GraphicsWicketItem::GraphicsWicketItem(QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsLineItem(parent,scene)
{
    this->width=50;
    this->rot=-45;
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    QPointF p2=this->rotatePoint(QPointF(0,0),QPointF(0,this->width),this->rot);
    this->setLine(QLineF(QPointF(0,0),p2));
    this->text=new QGraphicsTextItem(" ");
    this->text->setPos(50,0);
}

GraphicsWicketItem::~GraphicsWicketItem()
{
}

void GraphicsWicketItem::setPosition(QPointF pos)
{
    QPointF p2=this->rotatePoint(pos,QPointF(pos.x()+this->width,pos.y()),this->rot);
    this->text->setPos(pos.x()-this->width,pos.y());
}

QPointF GraphicsWicketItem::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}
