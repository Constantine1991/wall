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
           BOTTOM_DEAF         =   0, //������
           BOTTOM_BEGINEND     =   1, // ���������/��������
           BOTTOM_PASSAGE      =   2, // ���������
           BOTTOM_ANGLETWO     =   3, //������� �������
           BOTTOM_ANGLETHREE   =   4 // ������� �������
       };
       GraphicsPillarItem(QMenu *menuItem=0,QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
       ~GraphicsPillarItem();
       int type() const{
           return Type;
       }
       void addWall(GraphicsWallItem *lineWall,bool point);
       void removeWall(GraphicsWallItem *item);
       void setText(QString caption);
       QString text();
       void setHeight(int height);
       void setHeightSide(SIDETYPE sideType,int height);
       void setHeightSide(int side,int height);
       void setBottomTypeEnable(bool enable);
       void setBottomType(int type);
       void clearColorRow();
       void addColorRow(COLOR color);
       void setCountColorRow(int count);
       void setColorRow(int row,COLOR color);
       void setColorRow(QList<COLOR> color);
       void setTop(bool top);
       void setTopColor(COLOR color);
       void setPazzle(bool pazzle);
       void setColorPazzle(int number,COLOR color);
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
       COLOR colorRow(int row);
       QList<COLOR> colorListRow();
       COLOR topColor();
       bool isPazzle();
       COLOR colorPazzle(int number);
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
    COLOR colorTopPillar;
    QList<COLOR> colorRowPillar;
    bool pazzlePillar;
    COLOR colorPazzlePillar[2];
    BOTTOMTYPE bottomTypePillar;
    bool bottomTypeEnablePillar;
    QHash<GraphicsWallItem*,bool> listWall;
    QList<QPointF> lastPos;
    bool mouseRelease;
    bool enabledBackUp;
    bool isBackUp;
};

#endif // GRAPHICSPILLARITEM_H
