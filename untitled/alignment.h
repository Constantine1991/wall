#ifndef ALIGNMENT_H
#define ALIGNMENT_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QGraphicsItemGroup>
#include "graphicspillaritem.h"

class Alignment
{
public:
    void setScene(QGraphicsScene *scene);
    void alignmentLengthPillar(int length, QList<QGraphicsItem *> aligmentItem);
    void alignmentAnglePillar(int angle, QList<QGraphicsItem*> listItem);
private:
    struct Child{
        QGraphicsItem *child;
        float angleChildToParent;
    };
    struct Parent{
        QGraphicsItem *parent;
        QList<Child*> listChild;
    };
    QList<Alignment::Parent*> parentItem;
    QGraphicsScene *scene;
    float normalVector2D(QPointF vector2d);
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    float anglePointToPoint(QPointF p1,QPointF p2);
    bool coliding(QGraphicsItem *wallItem, QGraphicsItem *pillarItem);
    QList<Alignment::Child*> childToParent(QGraphicsItem *parent, QList<QGraphicsItem *> selectedItem);
    void av(QGraphicsItem *parent,QList<QGraphicsItem*> selectedItem);
};

#endif // ALIGNMENT_H
