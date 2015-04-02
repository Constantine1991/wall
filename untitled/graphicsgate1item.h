#ifndef GRAPHICSGATE1ITEM_H
#define GRAPHICSGATE1ITEM_H
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QPointF>
#include <QMenu>
#include <QLine>
#include "propertiesitem.h"

class GraphicsGate1Item:public QGraphicsTextItem
{
public:
    enum {Type=UserType + 4};
    GraphicsGate1Item(QMenu *menu=0,QGraphicsItem *parent=0,QGraphicsScene *scene=0);
    ~GraphicsGate1Item();
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
    QMenu *menu;
    int widthGate;
};

#endif // GRAPHICSGATE1ITEM_H
