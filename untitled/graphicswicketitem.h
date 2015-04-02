#ifndef GRAPHICSWICKETITEM_H
#define GRAPHICSWICKETITEM_H

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QLineF>
#include <QPointF>
#include <QMenu>
#include <qmath.h>
#include "propertiesitem.h"

class GraphicsWicketItem: public QGraphicsTextItem
{
public:
    enum {Type=UserType + 3};
    GraphicsWicketItem(QMenu *menuItem=0,QGraphicsItem *parent=0,QGraphicsScene *scene=0);
    ~GraphicsWicketItem();
    int type() const{
        return Type;
    }
    void setPosition(QPointF pos);
    QPointF position();
    int rotationWicket();
    void setRotate(int angle);
    void setText(QString text);
    int value();
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF centre();
    QMenu *menu;
    int width;
    int widthWicket;
    int rot;
};

#endif // GRAPHICSWICKETITEM_H
