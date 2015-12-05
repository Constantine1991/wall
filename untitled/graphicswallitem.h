#ifndef GRAPHICSWALLITEM_H
#define GRAPHICSWALLITEM_H
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QPen>
#include <QMenu>
#include <QList>
#include "propertiesitem.h"

class GraphicsWallItem:public QGraphicsLineItem
{
public:
    enum { Type = UserType + 2 };
    GraphicsWallItem(QMenu *menuItem=0,QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    int type() const{
        return Type;
    }
    void setText(QString caption);
    QPointF centre();
    void setLinePoint(QPointF p1,QPointF p2);
    QPointF posP1();
    QPointF posP2();
    void setHeight(int height);
    int height();
    void setWidth(int width);
    int width();
    void setTop(bool top);
    bool isTop();
    void setColorTop(QString color);
    QString colorTop();
    void setPazzle(bool pazzle);
    bool isPazzle();
    void setColorPazzle(int pazzle,QString color);
    QString colorPazzle(int pazzle);
    void addColorRow(QString color);
    void setColorRow(int row,QString color);
    void setColorRowList(QList<QString> colorList);
    QString colorRow(int row);
    QList<QString> colorListRow();
    bool isEmptyColorRow();
    int countColorRow();
    void clearColorRow();
    void setDecoreid(int decoreid);
    int isDecoreid();
    void setColorDecoreid(QString color);
    QString colorDecoreid();
    void setGirthRail(bool girth);
    bool isGirthRail();
    void setGraphicsWallItem(GraphicsWallItem *wall);
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
private:
    QMenu *menuItem;
    QGraphicsTextItem *itemText;
    void updatePosText();
    int wallHeight;
    int wallWidth;
    bool wallTop;
    QString wallColorTop;
    bool wallPazzle;
    QString wallColorPazzle[2];
    QList<QString> wallColorRow;
    int wallDecoreid;
    QString wallColorDecoreid;
    bool wallGirthRail;
};

#endif // GRAPHICSWALLITEM_H
