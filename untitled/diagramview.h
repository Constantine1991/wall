#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QKeyEvent>
#include <qmath.h>
#include <QDir>
#include <QPrinter>
#include <QPrintDialog>
#include <qmath.h>
#include <QFileDialog>
//----------------------//
#include "listitem.h"
#include "graphicspillaritem.h"
#include "graphicswallitem.h"
#include "graphicswicketitem.h"
#include "calculate.h"
#include "excelexport.h"
#include "interval.h"
#include "groupitem.h"
//---------WINDOW FORMS---------------//
#include "propertiespillarwindow.h"
#include "propertieswallwindow.h"
#include "typecomponent.h"
//-----------------------------------//

class DiagramView:public QGraphicsView
{
Q_OBJECT
private:
    QGraphicsScene *pDiagramScene;
    GroupItem *group;
    QList<GroupItem*> listGroup;
    TYPEITEM typeITEM;
    int currentIdItem;
    bool mousePrees;
    QGraphicsItem *itemGraphicsChange;
    QGraphicsLineItem *lineWall;
    QGraphicsLineItem *lineFilling;
    SETTINGS *itemSetting;
    QMenu *MenuItem;
    QAction *Rotate_45Action;
    QAction *Rotate_90Action;
    QAction *Rotate_180Action;
    QAction *DeleteItem;
    void CreateMenuItem();
    QGraphicsItem *itemToScene(TYPEITEM typeItem,QPointF point);
    void AppendItem(GroupItem::TYPEGROUP typeGroup, QPointF point);
    QGraphicsItem *AppendItem(TYPEITEM typeItem,QPointF point);
    float distancePointToPoint(QPointF point1,QPointF point2);
    void itemChangeScene(int idItem);
    void RotateItem(int Angle);
    void changeLine(ITEM *parentItem, QGraphicsItem *itemGraphics);
    QPointF centerItem(QGraphicsItem *itemGraphics);
    void AppendBrickColorPazzle(QList<COLORBRICK*> *colorBrick,int countColor,QString namedColor);
    void Filling(QGraphicsItem *a, QGraphicsItem *b, float interval);
    QPointF rotatePoint(QPointF center, QPointF point, float angle);
    bool coliding(QGraphicsItem *Object,QPointF point);
    GraphicsPillarItem *createPillar(QPoint pointScene);
    GraphicsWallItem *createWall(QPointF pointSceneA, QPointF pointSceneB);
    void appendChildObject(QGraphicsItem *a,QGraphicsItem *b,QGraphicsItem *l);
    void deleteFilling();
    void changeGroup(GroupItem *g1,GroupItem g2);
    void collidingGroup(QPointF point);
private slots:
    void RotateItem_45();
    void RotateItem_90();
    void RotateItem_180();
    void Delete_Item();
    void setInterval(float interval,bool empty);
public:
    DiagramView(QWidget *parent=0);
    ~DiagramView();
    void setTypeItem(TYPEITEM type);
    void ClearScene();
    void SaveDiagramScene(QString nameFile);
    bool LoadDiagramScene(QString nameFile);
    void PrintDiagram();
    void PrintContract(bool girth, bool tray);
    void setSettingItem(SETTINGS *itemSetting);
    void SaveSettingItem();
    SETTINGS *LoadSettingItem();
    bool pillarBottom;
    bool Rigel;
    bool Fundament;
public slots:
    void closeProperties(TYPEITEM itemType, bool all);
    void component(TYPEITEM typeItem,int width);
signals:
    void itemMoveScene(QPointF point);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // DIAGRAMVIEW_H
