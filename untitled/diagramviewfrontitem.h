#ifndef DIAGRAMVIEWFRONTITEM_H
#define DIAGRAMVIEWFRONTITEM_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "diagrampillar.h"

class DiagramViewFrontItem:public QGraphicsView
{
public:
    enum DRAWITEM{
        ITEM_PILLAR         = 1,
        ITEM_WALL           = 2,
        ITEM_PILLAR_WALL    = 3,
        ITEM_NONE           = 0
    };
    DiagramPillar graphicPillar;
    DiagramViewFrontItem(QWidget *parent=0);
    ~DiagramViewFrontItem();
    void setRectScene(int w,int h);
    void draw(DRAWITEM drawItem);
private:
    QGraphicsScene *scene;
};

#endif // DIAGRAMVIEWFRONTITEM_H
