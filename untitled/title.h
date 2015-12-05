#ifndef TITLE_H
#define TITLE_H
#include <QGraphicsScene>
#include "graphicspillaritem.h"

class Title
{
public:
    Title();
    void setDiagramScene(QGraphicsScene *scene);
    void show();
    void hide();
private:
    GraphicsPillarItem *pillar;
    GraphicsWallItem *wall;
    QGraphicsTextItem *lableTop;
    QGraphicsTextItem *labelRight;
    QGraphicsTextItem *labelPillar1;
    QGraphicsTextItem *labelPillar2;
    QGraphicsTextItem *labelWall1;
    QGraphicsTextItem *labelWall2;
    QGraphicsScene *scene;
};

#endif // TITLE_H
