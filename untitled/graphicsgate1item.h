#ifndef GRAPHICSGATE1ITEM_H
#define GRAPHICSGATE1ITEM_H
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPoint>
#include <QLine>
#include "propertiesitem.h"

class GraphicsGate1Item:public QGraphicsLineItem
{
public:
    enum {Type=UserType + 4};
    GraphicsGate1Item(QGraphicsItem *parent=0,QGraphicsScene *scene=0);
    ~GraphicsGate1Item();
    int type() const{
        return Type;
    }
    void setPosition(QPointF p1,QPointF p2);
    void setRotate();
    void setText(QString text);
private:
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF centre();
    QGraphicsTextItem *text;
    QGraphicsLineItem *childGate;
    int width;
    int rotP1;
    int rotP2;
};

#endif // GRAPHICSGATE1ITEM_H
