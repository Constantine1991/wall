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
    GraphicsWallItem(QMenu *menuItem,QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    int type() const{
        return Type;
    }
    void setText(QString caption);
    QPointF centre();
    void setLinePoint(QPointF p1,QPointF p2);
    void setHeight(int height);
    int height();
    void setWidth(int width);
    int width();
    void setTop(bool top);
    bool isTop();
    void setColorTop(COLOR color);
    COLOR colorTop();
    void setPazzle(bool pazzle);
    bool isPazzle();
    void setColorPazzle(int pazzle,COLOR color);
    COLOR colorPazzle(int pazzle);
    void addColorRow(COLOR color);
    void setColorRow(int row,COLOR color);
    void setColorRowList(QList<COLOR> colorList);
    COLOR colorRow(int row);
    QList<COLOR> colorListRow();
    bool isEmptyColorRow();
    int countColorRow();
    void clearColorRow();
    void setDecoreid(int decoreid);
    int isDecoreid();
    void setColorDecoreid(COLOR color);
    COLOR colorDecoreid();
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
    COLOR wallColorTop;
    bool wallPazzle;
    COLOR wallColorPazzle[2];
    QList<COLOR> wallColorRow;
    int wallDecoreid;
    COLOR wallColorDecoreid;
    bool wallGirthRail;
};

#endif // GRAPHICSWALLITEM_H
