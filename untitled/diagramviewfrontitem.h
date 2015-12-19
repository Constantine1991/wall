#ifndef DIAGRAMVIEWFRONTITEM_H
#define DIAGRAMVIEWFRONTITEM_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "diagrampillar.h"
#include "diagramwall.h"

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
    DiagramWall graphicWall;
    DiagramViewFrontItem(QWidget *parent=0);
    ~DiagramViewFrontItem();
    void setRectScene(int w,int h);
    void draw(DRAWITEM drawItem);
private:
    QGraphicsScene *scene;
    void resizeRectScene(int width,int height);
    int widthScene;
    int heightScene;
};

#endif // DIAGRAMVIEWFRONTITEM_H
