#ifndef RECTALLOCATION_H
#define RECTALLOCATION_H
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <qmath.h>

class RectAllocation:public QGraphicsPolygonItem
{
public:
    RectAllocation(QGraphicsItem *parent=0,QGraphicsScene *scene=0);
    void setArea(QPointF p1,QPointF p2);
    void setPosArea(QPointF p);
    QPointF posArea();
private:
    QPointF pointLeft;
};

#endif // RECTALLOCATION_H
