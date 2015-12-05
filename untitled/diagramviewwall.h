#ifndef DIAGRAMVIEWWALL_H
#define DIAGRAMVIEWWALL_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QColor>
#include <QList>
#include <qmath.h>
#include "calculate.h"
#include "propertiesitem.h"
class DiagramViewWall:public QGraphicsView
{
    Q_OBJECT
public:
    DiagramViewWall(QWidget *parent=0);
    //задать параметры стены
    void setGraphicsWall(int width,int height,bool topWall=false);
    void setWidthWall(int width);
    void setHeightWall(int height);
    void setSetting(SettingItem *itemSetting);
    // Показать крышку полотна
    void setEnableTopWall(bool enable,QColor color);
    //задать цвет ряду стены
    void setColorRowWall(int number, QColor color);
    // задать всем рядам один цвет
    void setColorAllRawWall(QColor colorAllRow);
    // включить графическую мазайку
    void setEnableColorPazzle(bool enable,QColor color1,QColor color2);
    // Вовращает цвет указанной строки
    QColor getColorRow(int numberRow);
    // Возвращает все цвета принадлежащим строкам
    QList<QColor> getColorAllRow();
    // возвращает количество рядов в стене
    int countRow();
    int countColorRow();
    void setEnableDecoreit(bool d1,QColor colorD1,bool d2,QColor colorD2,bool d3,QColor colorD3);
    int heightBrick;
    int widthBrickR;
    int widthBrickRD;
    ///////////////////////////////////////////////
    void setHeightPillar(int height);
    void setTopPillar(bool top,QString color);
    void setPazzlePillar(bool pazzle,QString color1,QString color2);
    void setColorListPillar(QList<QString> colorList);
private:
    void clearScene();// очистка сцены
    void createWall();// создание обычной стены
    void createPazzleWall();//создание мазаечной стены
    void createPillar();// создание столба
    void rendering();// прорисовка сцены стены
    QGraphicsScene *GraphicsSceneWall;
    int row; // количество строк стены
    //----------------------//
    int widthWall; // длина стены
    int heightWall;// высота стены
    bool topWall;// крышка полотна
    QColor colorTop;// цвет крышки полотна
    QList<QColor> colorRow;// цвета рядов стены
    bool pazzle; // мазайка
    QColor color1; // цвет 1 для мазайки
    QColor color2; // цвет 2 для мазайки
    bool d1;
    QColor colorD1;
    bool d2;
    QColor colorD2;
    bool d3;
    QColor colorD3;
    Calculate *calc;
    int heightPillar;
    bool topPillar;
    QString colorTopPillar;
    bool pazzlePillar;
    QString colorPazzle1Pillar;
    QString colorPazzle2Pillar;
    QList<QString> colorList;
};

#endif // DIAGRAMVIEWWALL_H
