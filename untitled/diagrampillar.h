#ifndef DIAGRAMPILLAR_H
#define DIAGRAMPILLAR_H
#include <QGraphicsRectItem>
#include <QPen>
#include <QRect>
#include <QPoint>
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
    QPoint pos();
    void setSizeBrickTile(int w,int h);
    void setSizeTopTile(int w,int h);
    void setSizeBottomTile(int w,int h);
    void setHeight(int h);//+
    void setInsert(int side, int insert);
    void setTop(bool enable=false);//
    void setTopColor(QString nameColor);
    void setBottom(bool enable=false);//
    void showSide(int side);//+
    void setRowColor(int indexRow, QString nameColor);//****
    void setRowColorAll(QString nameColor);//
    void setPazzleColor(bool enable=false);
    void setRowPazzleColor(QString nameColorAngle1, QString nameColorAngle2);
    int row();
    int boundingRectHeight();
    QList<QGraphicsRectItem*> update();
private:
    SettingItem *settingItem;
    QGraphicsRectItem *graphicTileTop;
    QGraphicsRectItem *graphicTileBottom;
    QList<QGraphicsRectItem*> graphicsTileBricks;
    QList<QString> colorTileBricks;
    QString colorTileTop;
    QString namecolorPazzleAngle1;
    QString namecolorPazzleAngle2;
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
    bool enablePazzle;
    SIDE side;
    QGraphicsRectItem *createItem(int width,int height);
    //****
    void setRowColor(int indexRow,SettingItem::COLOR_BRICK *colorAngleBrick,SettingItem::COLOR_BRICK *colorAngleInsert);
    void setPazzleColor(QString color1, QString color2);
    void updateColorsTileBricks();
    void setPosGraphicTileTop(int x,int y);
    void setPosGraphicTileBricks(int x,int y);
    void setPosGraphicTileBottom(int x,int y);
    void clearGraphicsTileBricks();
};

#endif // DIAGRAMPILLAR_H
