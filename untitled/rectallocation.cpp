#include "rectallocation.h"
#include "QDebug"

RectAllocation::RectAllocation(QGraphicsItem *parent, QGraphicsScene *scene):QGraphicsPolygonItem(parent,scene)
{
    this->setBrush(QBrush(Qt::NoBrush));
    this->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
}

void RectAllocation::setPosArea(QPointF p)
{
    this->pointLeft=p;
}

QPointF RectAllocation::posArea()
{
    return this->pointLeft;
}

void RectAllocation::setArea(QPointF p1,QPointF p2)
{
    QPolygonF rect;
    float mp1=::qSqrt((p1.x()*p1.x())+(p1.y()*p1.y()));
    float mp2=::qSqrt((p2.x()*p2.x())+(p2.y()*p2.y()));
    if(mp1<=mp2)
        rect<<p1<<QPointF(p1.x(),p2.y())<<p2<<QPointF(p2.x(),p1.y());
    else rect<<p1<<QPointF(p2.x(),p1.y())<<p2<<QPointF(p1.x(),p2.y());
    this->setPolygon(rect);
}
