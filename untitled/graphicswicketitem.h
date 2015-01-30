#ifndef GRAPHICSWICKETITEM_H
#define GRAPHICSWICKETITEM_H

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QLineF>
#include <QPointF>
#include <QMenu>
#include <qmath.h>
#include "propertiesitem.h"

class GraphicsWicketItem: public QGraphicsLineItem
{
public:
    enum {Type=UserType + 3};
    GraphicsWicketItem(QMenu *menuItem=0,QGraphicsItem *parent=0,QGraphicsScene *scene=0);
    ~GraphicsWicketItem();
    int type() const{
        return Type;
    }
    void setPosition(QPointF pos);
    void setRotate(int angle);
    void setText(QString text);
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF centre();
    void updateText();
    QGraphicsTextItem *text;
    QMenu *menu;
    int width;
    int rot;
};

#endif // GRAPHICSWICKETITEM_H
