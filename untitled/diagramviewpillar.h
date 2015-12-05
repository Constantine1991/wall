#ifndef DIAGRAMVIEWPILLAR_H
#define DIAGRAMVIEWPILLAR_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsPolygonItem>
#include <QList>
#include <qmath.h>
#include "propertiesitem.h"

class DiagramViewPillar:public QGraphicsView
{
public:
    enum RENDERINGSIDE{
        FRONT       =   0,
        RIGHT       =   3,
        BACK        =   1,
        LEFT        =   2
    };
    enum SIZEGRAPHIC{
        TOP_HEIGHT      = 50,
        TOP_WIDTH       = 100,
        BIG_HEIGHT      = 50,
        BIG_WIDTH       = 50,
        SMALL_HEIGHT    = 50,
        SMAL_WIDTH      = 25,
        BOTTOM_HEIGHT   = 50,
        BOTTOM_WIDTH    = 200
    };

    DiagramViewPillar(QWidget *parent=0);
    void setHeight(int height);//Задать высоту столба
    void setInsertBottom(int insertBottom);//Задать высоту паза
    void setInsertTop(int insertTop);
    void setColorRow(int index, QBrush color);//Задать цвет ряда столба по индексу
    void setColorAllRow(QBrush color);//Задать цвет всем рядам стоба
    void setEnabledTop(bool enable=false);//Вкл./выкл. прорисовку крышки столба
    void setEnabledBottom(bool enable=false);//Вкл./выкл. прорисовку основания столба
    void setColorTop(QBrush color);//Задать цвет столба
    void setEnabledPazzle(bool enable,QBrush color1,QBrush color2);//Вкл./выкл. прорисовку мазайки и задать цвета
    QBrush colorRow(int index);
    int row();
    int heightBrick;
    void setRenderingSide(int renderingSide=0);
private:

    //void drawPillar(int );
    void createPillar();
    void createPillarPazzle();
    void rendering();
    QGraphicsScene *graphicsScene;
    RENDERINGSIDE renderingSide;
    int height;
    int insertTop;
    int insertBottom;
    bool top;
    QBrush colorTop;
    bool pazzle;
    QBrush colorPazzle1;
    QBrush colorPazzle2;
    QList<QBrush> color;
    bool bottom;
};

#endif // DIAGRAMVIEWPILLAR_H
