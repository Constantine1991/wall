#ifndef DIAGRAMWALL_H
#define DIAGRAMWALL_H
#include <QGraphicsRectItem>
#include <QImage>
#include <QBrush>
#include <QBrush>
#include <QPen>
#include <QSize>
#include "propertiesitem.h"
#include "calculate.h"

class DiagramWall
{
public:
    DiagramWall();
    ~DiagramWall();
    void setSettingItem(SettingItem *settingItem);
    void setSizeTileTop(int width,int height);
    void setSizeTileBrick(int width,int height);
    void setSizeTileBottom(int width,int height);
    void setPos(int x,int y);
    void setHeight(int height);
    void setWidth(int width);
    void setTop(bool enable=false);
    void setColorTop(QString nameColor);
    void setBootom(bool enable=false);
    void setColorRow(int indexRow,QString nameColor);
    void setColorRow(QList<QString> colors);
    void setColorRowAll(QString nameColor);
    void setPazzle(bool enable=false);
    void setColorPazzle(QString nameColor1,QString nameColor2);
    QString colorRow(int indexRow);
    QList<QString> colorRow();
    int boundingRectWidth();
    int row();
    QList<QGraphicsRectItem *> update();
private:
    SettingItem *settingItem;
    QGraphicsRectItem * graphicsTops;
    QGraphicsRectItem *graphicsBottom;
    QList<QGraphicsRectItem *> graphicBricks;
    int pos_x;
    int pos_y;
    int width;
    int height;
    QSize sizeTileTop;
    QSize sizeTileBrick;
    QSize sizeTileBottom;
    QList<QString> colorsBricks;
    QString nameColorPazzle1;
    QString nameColorPazzle2;
    bool pazzle;

    SettingItem::COLOR_BRICK *indexColor(int indexRow,int indexCol,SettingItem::COLOR_BRICK_TYPE type);
    void clearTileBricks();
    QGraphicsRectItem *createItem(int width,int height);
    void updateBricks();
    void updateTops();
    void updateBottom();

};

#endif // DIAGRAMWALL_H
