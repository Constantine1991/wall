#ifndef DIAGRAMVIEWFRONTITEM_H
#define DIAGRAMVIEWFRONTITEM_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
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
    void showText(bool show);
    void setPosText(int x,int y,int offsetY);
    void draw(DRAWITEM drawItem);
private:
    QGraphicsScene *scene;
    void resizeRectScene(int width,int height);
    void createItemsText(int count);
    QGraphicsTextItem *text(int x,int y,QString caption);
    void clearItemText();
    int widthScene;
    int heightScene;
    QList<QGraphicsTextItem*> itemText;
    int pos_x;
    int pos_y;
    int offsetY;
    bool showItemText;
};

#endif // DIAGRAMVIEWFRONTITEM_H
