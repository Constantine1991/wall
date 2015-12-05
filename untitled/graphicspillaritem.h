#ifndef GRAPHICSPILLARITEM_H
#define GRAPHICSPILLARITEM_H
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QMenu>
#include <QObject>
#include <QHash>
#include "propertiesitem.h"
#include "graphicswallitem.h"

class GraphicsPillarItem:public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 1 };
       enum SIDETYPE{
           SIDE_FRONT      =   0,
           SIDE_BACK       =   1,
           SIDE_LIFT       =   2,
           SIDE_RIGHT      =   3
       };
       enum BOTTOMTYPE{
           BOTTOM_DEAF         =   0, //Глухое
           BOTTOM_BEGINEND     =   1, // Начальное/конечное
           BOTTOM_PASSAGE      =   2, // Проходное
           BOTTOM_ANGLETWO     =   3, //Угловое двойное
           BOTTOM_ANGLETHREE   =   4 // Угловое тройное
       };
       GraphicsPillarItem(QMenu *menuItem=0,QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
       ~GraphicsPillarItem();
       int type() const{
           return Type;
       }
       void addWall(GraphicsWallItem *lineWall,bool point);
       void removeWall(GraphicsWallItem *item);
       int isWall();
       QList<GraphicsWallItem*> itemsWall();
       void setText(QString caption);
       QString text();
       void setHeight(int height);
       void setHeightSide(SIDETYPE sideType,int height);
       void setHeightSide(int side,int height);
       void setBottomTypeEnable(bool enable);
       void setBottomType(int type);
       void clearColorRow();
       void addColorRow(QString color);
       void setCountColorRow(int count);
       void setColorRow(int row,QString color);
       void setColorRow(QList<QString> color);
       void setTop(bool top);
       void setTopColor(QString color);
       void setPazzle(bool pazzle);
       void setColorPazzle(int number,QString color);
       void setGraphicsPillarItem(GraphicsPillarItem *graphicsItem);
       int height();
       QPointF centre();
       int heightSide(SIDETYPE sideType);
       int heightSide(int side);
       int isAutoBottomType();
       int isBottomType();
       bool isBottomTypeEnable();
       bool isTop();
       int countColorRow();
       QString colorRow(int row);
       QList<QString> colorListRow();
       QString topColor();
       bool isPazzle();
       QString colorPazzle(int number);
       QMenu *menuitem();
       void backUp();
       void clearBackUp();
       void setEnabledBackUp(bool value);
       void setPosition(QPointF pos);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    QMenu *menuItem;
    QGraphicsTextItem *itemText;
    QString textPillar;
    int heightPillar;
    bool topPillar;
    int heightSidePillar[4];
    QString colorTopPillar;
    QList<QString> colorRowPillar;
    bool pazzlePillar;
    QString colorPazzlePillar[2];
    BOTTOMTYPE bottomTypePillar;
    bool bottomTypeEnablePillar;
    QHash<GraphicsWallItem*,bool> listWall;
    QList<QPointF> lastPos;
    bool mouseRelease;
    bool enabledBackUp;
    bool isBackUp;
};

#endif // GRAPHICSPILLARITEM_H
