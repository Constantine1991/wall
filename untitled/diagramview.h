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
#include <QDomDocument>
#include <QDomElement>
#include <QXmlStreamReader>
//----------------------//
#include "listitem.h"
#include "graphicspillaritem.h"
#include "graphicswallitem.h"
#include "graphicswicketitem.h"
#include "calculate.h"
#include "excelexport.h"
#include "interval.h"
#include "groupitem.h"
#include "graphicslineitem.h"
//---------WINDOW FORMS---------------//
#include "propertiespillarwindow.h"
#include "propertieswallwindow.h"
//-----------------------------------//

class DiagramView:public QGraphicsView
{
Q_OBJECT
private:
    QGraphicsScene *pDiagramScene;
    GroupItem *group;
    QList<GroupItem*> listGroup;
    QList<QGraphicsItem*> objectBackUp;
    TYPEITEM typeITEM;
    int currentIdItem;
    bool mousePrees;
    int widthGroup;
    QGraphicsItem *itemGraphicsChange;
    QGraphicsLineItem *lineWall;
    QGraphicsLineItem *lineFilling;
    QGraphicsEllipseItem *linePoint1;
    QGraphicsEllipseItem *linePoint2;
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
    QPointF centerItem(QGraphicsItem *itemGraphics);
    void AppendBrickColorPazzle(QList<COLORBRICK*> *colorBrick,int countColor,QString namedColor);
    void Filling(GraphicsPillarItem *a, GraphicsPillarItem *b, float interval);
    QPointF rotatePoint(QPointF center, QPointF point, float angle);
    bool coliding(QGraphicsItem *Object,QPointF point);
    void deleteFilling();
    void collidingGroup(QPointF point);
    void savePillar(QDomDocument *document, QDomElement *parent, GraphicsPillarItem *pillar);
    void loadPillar(QXmlStreamReader *xml,GraphicsPillarItem *pillar);
    void setLastPosObject();
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
    void setTypeItem(TYPEITEM type, int interval);
    void ClearScene();
    void SaveDiagramScene(QString nameFile);
    bool LoadDiagramScene(QString nameFile);
    void PrintDiagram();
    void PrintContract();
    void setSettingItem(SETTINGS *itemSetting);
    void SaveSettingItem();
    SETTINGS *LoadSettingItem();
    bool pillarBottom;
    bool Rigel;
    bool Fundament;
public slots:
    void closeProperties(TYPEITEM itemType, bool all);
signals:
    void itemMoveScene(QPointF point);
    void mouseRelease();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // DIAGRAMVIEW_H
