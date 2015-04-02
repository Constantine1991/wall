#ifndef GRAPHICSGATE2ITEM_H
#define GRAPHICSGATE2ITEM_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPointF>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include "propertiesitem.h"

class GraphicsGate2Item:public QGraphicsTextItem
{
public:
    enum {Type=UserType + 5};
    GraphicsGate2Item(QMenu *menu=0,QGraphicsItem *parent=0,QGraphicsScene *scene=0);
    ~GraphicsGate2Item();
    int type() const{
        return Type;
    }
    void setPosition(QPointF p1,QPointF p2);
    QPointF posP1();
    QPointF posP2();
    void setRotate(int angle);
    int rotationGate();
    void setText(QString text);
    int value();
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QGraphicsTextItem *text;
    QGraphicsLineItem *mirrorLine;
    QGraphicsLineItem *topLine;
    QMenu *menu;
    int widthGate;
    int width;
    int rotP1;
    int rotP2;
    int rotP3;
};

#endif // GRAPHICSGATE2ITEM_H
