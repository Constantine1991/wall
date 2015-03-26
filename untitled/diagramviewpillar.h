#ifndef DIAGRAMVIEWPILLAR_H
#define DIAGRAMVIEWPILLAR_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <QList>
#include <qmath.h>

class DiagramViewPillar:public QGraphicsView
{
public:
    enum RENDERINGSIDE{
        FRONT       =   0,
        RIGHT       =   3,
        BACK        =   1,
        LEFT        =   2
    };
    DiagramViewPillar(QWidget *parent=0);
    void setHeight(int height);
    void setInsertTop(int insertTop);
    void setInsertBottom(int insertBottom);
    void setColorRow(int index, QColor color);
    void setColorAllRow(QColor color);
    void setEnabledTop(bool enable=false);
    void setEnabledBottom(bool enable=false);
    void setColorTop(QColor color);
    void setEnabledPazzle(bool enable,QColor color1,QColor color2);
    QColor colorRow(int index);
    int row();
    int heightBrick;
    void setRenderingSide(int renderingSide=0);
private:
    void createPillar();
    void createPillarPazzle();
    void rendering();
    QGraphicsScene *graphicsScene;
    RENDERINGSIDE renderingSide;
    int height;
    int insertTop;
    int insertBottom;
    bool top;
    QColor colorTop;
    bool pazzle;
    QColor colorPazzle1;
    QColor colorPazzle2;
    QList<QColor> color;
    bool bottom;
};

#endif // DIAGRAMVIEWPILLAR_H
