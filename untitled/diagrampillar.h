#ifndef DIAGRAMPILLAR_H
#define DIAGRAMPILLAR_H
#include <QGraphicsRectItem>
#include <QPen>
#include "propertiesitem.h"


class DiagramPillar
{
public:
    enum SIDE{
        FRONT       =   0,
        RIGHT       =   3,
        BACK        =   1,
        LEFT        =   2
    };
    DiagramPillar();
    void setHeightBrick(int heightBrick);
    void setHeight(int height);
    void setInsert(int insert);
    void setPos(float x,float y);
    void setPos(QPointF pos);
    void setTop(bool top);
    void setBottom(bool bottom);
    void setPazle(bool pazle);
    void setTopImage(QImage *img);
    void setBottomImage(QImage *front,QImage *back);

    QList<QGraphicsRectItem*> graphicPillar(SIDE side);
private:
    enum SEZIBRICKPILLAR{
        SIZE_TOP_HEIGHT         = 50,
        SIZE_TOP_WIDTH          = 100,
        SIZE_BIG_HEIGHT         = 25,
        SIZE_BIG_WIDTH          = 50,
        SIZE_SMALL_HEIGHT       = 25,
        SIZE_SMALL_WIDTH        = 25,
        SIZE_BOTTOM_HEIGHT      = 50,
        SIZE_BOTTOM_WIDTH       = 100
    };
};

#endif // DIAGRAMPILLAR_H
