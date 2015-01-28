#ifndef GROUPITEM_H
#define GROUPITEM_H
#include <QObject>
#include <QGraphicsScene>
#include <QMouseEvent>
#include "graphicspillaritem.h"
#include "graphicswicketitem.h"

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
/*
public slots:
    void itemMoveScene(QPointF point);*/
private:
    TYPEGROUP type;
    QList<QGraphicsItem*> group;
};

#endif // GROUPITEM_H
