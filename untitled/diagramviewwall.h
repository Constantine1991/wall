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
    //������ ��������� �����
    void setGraphicsWall(int width,int height,bool topWall=false);
    void setWidthWall(int width);
    void setHeightWall(int height);
    void setSetting(SettingItem *itemSetting);
    // �������� ������ �������
    void setEnableTopWall(bool enable,QColor color);
    //������ ���� ���� �����
    void setColorRowWall(int number, QColor color);
    // ������ ���� ����� ���� ����
    void setColorAllRawWall(QColor colorAllRow);
    // �������� ����������� �������
    void setEnableColorPazzle(bool enable,QColor color1,QColor color2);
    // ��������� ���� ��������� ������
    QColor getColorRow(int numberRow);
    // ���������� ��� ����� ������������� �������
    QList<QColor> getColorAllRow();
    // ���������� ���������� ����� � �����
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
    void clearScene();// ������� �����
    void createWall();// �������� ������� �����
    void createPazzleWall();//�������� ��������� �����
    void createPillar();// �������� ������
    void rendering();// ���������� ����� �����
    QGraphicsScene *GraphicsSceneWall;
    int row; // ���������� ����� �����
    //----------------------//
    int widthWall; // ����� �����
    int heightWall;// ������ �����
    bool topWall;// ������ �������
    QColor colorTop;// ���� ������ �������
    QList<QColor> colorRow;// ����� ����� �����
    bool pazzle; // �������
    QColor color1; // ���� 1 ��� �������
    QColor color2; // ���� 2 ��� �������
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
