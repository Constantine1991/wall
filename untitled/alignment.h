#ifndef ALIGNMENT_H
#define ALIGNMENT_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include "graphicspillaritem.h"

class Alignment
{
public:
    void setScene(QGraphicsScene *scene);
    void alignmentLengthPillar(int length,QList<QGraphicsItem*> items);
    void alignmentAnglePillar(int angle, QList<QGraphicsItem*> listItem);
private:
    struct subVertex{
        subVertex(){
            this->sub=NULL;
            this->angle=0;
        }
        subVertex(GraphicsPillarItem *sub,float angle){
            this->sub=sub;
            this->angle=angle;
        }
        GraphicsPillarItem *sub;
        float angle;
    };
    struct firstVertex{
        firstVertex(){
            this->first=NULL;
            this->child.clear();
        }
        GraphicsPillarItem *first;
        QList<subVertex> child;
    };
    QList<firstVertex> changePosPillar;
    QGraphicsScene *scene;
    QList<QGraphicsItem*> itemScene;
    void appendVertex(GraphicsPillarItem *parentPillar);
    float normalVector2D(QPointF vector2d);
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
};

#endif // ALIGNMENT_H
