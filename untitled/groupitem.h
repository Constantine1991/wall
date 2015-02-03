#ifndef GROUPITEM_H
#define GROUPITEM_H
#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "graphicspillaritem.h"
#include "graphicswicketitem.h"
#include "graphicsgate1item.h"
#include "graphicsgate2item.h"

class GroupItem:public QObject
{
    Q_OBJECT
public:
    enum TYPEGROUP{
        ITEM_WICKET         = 0, //Калитка
        ITEM_GATE1          = 1, //Ворота распашные
        ITEM_GATE2          = 2, //Ворота откатные
        ITEM_WICKET_GATE1   = 3,
        ITEM_GATE1_WICKET   = 4,
        ITEM_WICKET_GATE2   = 5
    };
    GroupItem(QObject *parent=0);
    void createGroup(TYPEGROUP type,QMenu *menu,QGraphicsScene *scene);
    void createGroup(GroupItem *g1,GroupItem *g2,QMenu *menu,QGraphicsScene *scene);
    void setPos(QPointF point);
    bool isItem(QGraphicsItem *item);
    QList<QGraphicsItem*> items();
    void setRotate(int angle);
    TYPEGROUP isType();
public slots:
    void itemMoveScene(QPointF point);
private:
    QList<QGraphicsItem*> create(TYPEGROUP type,QMenu *menu);
    void setBoundingLine(QLineF line);
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF centre();
    TYPEGROUP type;
    QList<QGraphicsItem*> group;
    QLineF boundingLine;
    int rotation;
};

#endif // GROUPITEM_H
