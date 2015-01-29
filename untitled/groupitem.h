#ifndef GROUPITEM_H
#define GROUPITEM_H
#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "graphicspillaritem.h"
#include "graphicswicketitem.h"
#include "graphicsgate1item.h"

class GroupItem:public QObject
{
    Q_OBJECT
public:
    enum TYPEGROUP{
        ITEM_WICKET     = 0,
        ITEM_GATE1      = 1,
        ITEM_GATE2      = 2
    };
    GroupItem(QObject *parent=0);
    void createGroup(TYPEGROUP type,QMenu *menu,QGraphicsScene *scene);
    void setPos(QPointF point);
    bool isWicket(QGraphicsItem *item);
public slots:
    void setRotate(int angle);
    void itemMoveScene(QPointF point);
private:
    void setBoundingLine(QLineF line);
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF centre();
    TYPEGROUP type;
    QList<QGraphicsItem*> group;
    QLineF boundingLine;
    int rotation;
};

#endif // GROUPITEM_H
