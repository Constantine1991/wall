#ifndef GRAPHICSLINEITEM_H
#define GRAPHICSLINEITEM_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPointF>
#include <QRectF>
#include <QPolygonF>
#include "graphicsgate1item.h"
#include "graphicsgate2item.h"
#include "graphicspillaritem.h"
#include "graphicswallitem.h"
#include "graphicswicketitem.h"

class GraphicsLineItem:public QGraphicsLineItem
{
public:
    enum { Type = UserType + 6 };
    GraphicsLineItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    int type() const{
        return Type;
    }
    void setPoints(QPointF p1,QPointF p2,QGraphicsScene *scene);
private:
    QGraphicsTextItem *text;
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF center();
    float rotationLocalCoords();
    void updatePosText();
    GraphicsPillarItem *pillar(QPointF pos,QGraphicsScene *scene);
    int width(GraphicsPillarItem *p1, GraphicsPillarItem *p2, QGraphicsScene *scene);
    bool isPillar(QList<QGraphicsItem*> items,QPointF point);
};

#endif // GRAPHICSLINEITEM_H
