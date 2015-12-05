#ifndef PROPERTIESITEM_H
#define PROPERTIESITEM_H
#define PI  3.14159265358979323846

#include <QColor>
#include <QFile>
#include <QImage>
#include <QBrush>
#include <QList>
#include <qmath.h>

#include "settingcolor.h"

static int TableAngle[2][8]={{1,0,-1,-1,-1,0,1,1},
                             {1,1,1,0,-1,-1,-1,0}};

class SettingItem:public SettingColor{
public:
    enum TYPEITEM{ // ���� ��������
        ITEM_PILLAR                 = 1, //�����
        ITEM_WALL                   = 2, //�����
        ITEM_GATE_A                 = 3, //������ ���������
        ITEM_GATE_B                 = 4, //������ ��������
        ITEM_WICKET                 = 5, //�������
        ITEM_TEXT                   = 6,
        ITEM_FILLING                = 7,// �������������� ����������
        ITEM_LINE                   = 9,// �������
        ITEM_NONE                   = 0
    };



    int minWidthBrickR; //������ ����� �������� ���������
    int maxWidthBrickR; // ������ ����� ��������
    int heightBrickR; // ������ ����� ��������
    int heightBrickAngle; // ������ ����� �������� � ����� �������� ����������
    int maxWidthGirth; // ������������ ����� ������
    int minWidthGirth; // ����������� ����� ������
    int widthWallTop; // ������ ������ �������

    SettingItem();
    ~SettingItem();
    //��������� ����������� ���������
    bool save();
    //��������� ����������� ���������
    bool load();
};


typedef struct _COLORBRICK{
    _COLORBRICK(){}
    _COLORBRICK(int countBrick,QString namedColor){
        this->countBrick=countBrick;
        this->namedColor=namedColor;
    }
    int countBrick;
    QString namedColor;
}COLORBRICK;


#endif // PROPERTIESITEM_H
