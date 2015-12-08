#ifndef DIAGRAMPILLAR_H
#define DIAGRAMPILLAR_H
#include <QGraphicsRectItem>
#include <QPen>
#include <QRect>
#include "propertiesitem.h"


class DiagramPillar
{
public:
    enum SIDE{
        FRONT       =   0,
        BACK        =   1,
        LEFT        =   2,
        RIGHT       =   3
    };
    DiagramPillar();
    ~DiagramPillar();
    void setSettingItem(SettingItem *settingItem);
    void setPos(int x,int y);
    void setSizeBrickTile(int w,int h);
    void setSizeTopTile(int w,int h);
    void setSizeBottomTile(int w,int h);
    void setHeight(int h);//+
    void setInsert(SIDE side,int insert);
    void setTop(bool enable=false);//+
    void setTopColor(QString nameColor);
    void setBottom(bool enable=false);//+
    void showSide(SIDE side);//+
    //void setRowColor(int row,QString nameColor);//+
    //void setColor(QString nameColor);//+
    void clear();
    int row();
    QList<QGraphicsRectItem*> graphics();
private:
    SettingItem *settingItem;
    QGraphicsRectItem *graphicTileTop;
    QGraphicsRectItem *graphicTileBottom;
    QList<QGraphicsRectItem*> graphicsTileBricks;
    QList<QString> colors;
    int x;
    int y;
    int tileBrickWidth;
    int tileBrickHeight;
    int tileTopWidth;
    int tileTopHeight;
    int tileBottomWidth;
    int tileBottomHeight;
    int height;
    int insert[4];
    SIDE side;
    bool enableTop;
    bool enableBottom;
    QGraphicsRectItem *createItem(int width,int height);
    void setPosGraphicTileTop(int x,int y);
    void setPosGraphicTileBricks(int x,int y);
    void setPosGraphicTileBottom(int x,int y);
    void clearGraphicsTileBricks();
};

#endif // DIAGRAMPILLAR_H
