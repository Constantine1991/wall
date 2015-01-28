#ifndef GRAPHICSWICKETITEM_H
#define GRAPHICSWICKETITEM_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QLineF>
#include <QPointF>
#include <qmath.h>
#include "propertiesitem.h"

class GraphicsWicketItem: public QGraphicsLineItem
{
public:
    enum {Type=UserType + 3};
    GraphicsWicketItem(QGraphicsItem *parent=0,QGraphicsScene *scene=0);
    ~GraphicsWicketItem();
    int type() const{
        return Type;
    }
    void setPosition(QPointF pos);
    void setRotate();
    void setText(QString text);
private:
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF centre();
    QGraphicsTextItem *text;
    int width;
    int rot;
};

#endif // GRAPHICSWICKETITEM_H
