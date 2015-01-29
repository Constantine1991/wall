#include "graphicswicketitem.h"

GraphicsWicketItem::GraphicsWicketItem(QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsLineItem(parent,scene)
{
    this->width=50;
    this->rot=130;
    this->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    QPointF p2=this->rotatePoint(QPointF(0,0),QPointF(0,this->width),this->rot);
    this->setLine(QLineF(QPointF(0,0),p2));
    this->text=new QGraphicsTextItem("5000",this);
    this->text->setPos(50,0);
}

GraphicsWicketItem::~GraphicsWicketItem()
{
}

void GraphicsWicketItem::setText(QString text)
{
    this->text->setPlainText(text);
}

void GraphicsWicketItem::setPosition(QPointF pos)
{
    QPointF p2=this->rotatePoint(pos,QPointF(pos.x()+this->width,pos.y()),this->rot);
    this->setLine(QLineF(pos,p2));
    this->text->setPos(this->centre());
}

void GraphicsWicketItem::setRotate(int angle)
{
    this->rot=130+angle;
    this->text->setRotation(angle);
    this->setPosition(this->line().p1());
}

QPointF GraphicsWicketItem::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

QPointF GraphicsWicketItem::centre()
{
    return QPointF((this->line().p1().x()+this->line().p2().x())/2,(this->line().p1().y()+this->line().p2().y())/2);
}
