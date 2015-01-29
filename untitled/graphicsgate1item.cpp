#include "graphicsgate1item.h"

GraphicsGate1Item::GraphicsGate1Item(QGraphicsItem *parent,QGraphicsScene *scene)
    :QGraphicsLineItem(parent,scene)
{
    this->width=50;
    this->rotP1=130;
    this->rotP2=50;
    this->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->childGate=new QGraphicsLineItem(this);
    this->childGate->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->childGate->setFlag(QGraphicsItem::ItemIsSelectable,false);
    this->text=new QGraphicsTextItem("5000",this);
}

GraphicsGate1Item::~GraphicsGate1Item()
{
}

void GraphicsGate1Item::setText(QString text)
{
    this->text->setPlainText(text);
}

void GraphicsGate1Item::setPosition(QPointF p1, QPointF p2)
{
    QPointF point2=this->rotatePoint(p1,QPointF(p1.x()+this->width,p1.y()),this->rotP1);
    this->setLine(QLineF(p1,point2));
    this->text->setPos(this->centre());
    point2=this->rotatePoint(p2,QPointF(p2.x()+this->width,p2.y()),this->rotP2);
    this->childGate->setLine(QLineF(p2,point2));
}

QPointF GraphicsGate1Item::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

QPointF GraphicsGate1Item::centre()
{
    return QPointF((this->line().p1().x()+this->line().p2().x())/2,(this->line().p1().y()+this->line().p2().y())/2);
}
