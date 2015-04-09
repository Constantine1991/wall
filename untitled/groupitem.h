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
        ITEM_GATE2          = 2 //Ворота откатные
    };
    GroupItem(QObject *parent=0);
    void createGroup(TYPEGROUP type,QMenu *menu,QGraphicsScene *scene);
    void addGroup(TYPEGROUP type,QString value,QMenu *menu,QGraphicsScene *scene);
    void addGroup(GroupItem *group,QMenu *menu,QGraphicsScene *scene);
    QList<TYPEGROUP> types();
    QList<QGraphicsItem*> items();
    void setPos(QPointF point);
    void setPosItem(QPointF point,QGraphicsItem *item);
    QPointF pos();
    bool isItem(QGraphicsItem *item);

    void setRotate(int angle);
    int rot();
    void backUp();
public slots:
    void itemMoveScene(QPointF point);
    void mouseRelease();
private:
    QList<QGraphicsItem*> create(TYPEGROUP type,QMenu *menu);
    void setBoundingLine(QLineF line);
    QPointF rotatePoint(QPointF center, QPointF point,float angle);
    QPointF centre();
    QPointF centreLine(QLineF line);
    QList<TYPEGROUP> type;
    QList<QGraphicsItem*> group;
    QLineF boundingLine;
    int rotation;
    QList<QPointF> lastPos;
    bool isMouseRelease;
    bool isBackUp;
};

#endif // GROUPITEM_H
