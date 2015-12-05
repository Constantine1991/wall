#ifndef CALCULATE_H
#define CALCULATE_H
//column - �����
//fence - �����
#include "propertiesitem.h"
#include <QList>
#include <QColor>
#include <qmath.h>
struct FENCE {
    FENCE(){
        this->count_brick=0;
        this->count_brick_dob=0;
        this->count_cover=0;
    }
    int count_brick; //���������� ������ �������
    int count_brick_dob; //���������� ������ ������� ��������
    int count_cover; //���������� ������
};

struct COLUMN {
    COLUMN(){
        this->count_brick_angle=0;
        this->count_brick_angle_1=0;
        this->count_brick_angle_2=0;
        this->count_brick_angle_3=0;
        this->count_brick_angle_4=0;
    }
    int count_brick_angle; //���������� ������ �������
    int count_brick_angle_1; //���������� ������ ������� ���������� ������ �������
    int count_brick_angle_2; //���������� ������ ������� ���������� ������ �������
    int count_brick_angle_3; //���������� ������ ������� ���������� ������� �������
    int count_brick_angle_4; //���������� ������ ������� ���������� ��������� �������
};

struct COLORBRICKWALL {
    QList<int> colorBrickBigWall;
    QList<int> colorBrickSmallWall;
};

typedef COLORBRICKWALL COLORBRICKPILLAR;

class Calculate
{
public:
    Calculate(SettingItem *itemSetting);
    //���������� ��������� �� �����
    FENCE GetCountOnFence(int WidthWall, int HeightWall, bool topWall);
    int coverWall(int widthWall);
    COLORBRICKWALL colorBrickWall(int width, int height);
    COLORBRICKWALL colorListBrickWall(int width, int height);
    COLORBRICKPILLAR colorBrickPillar(int height,int *insert);
    COLORBRICKPILLAR colorListBrickPillar(int height,int *insert);
    int colBrickBigWall(int widthWall);
    int rowBrickBigWall(int heightWall);
    bool isBrickRD(int widthWall);
    //---------------------------------------------------------------

    ///���������� ��������� �� �����
    COLUMN GetCountOnColumn(int HeightPillar,int* Insert,int CountSide);
    int getCountBrickAngle(int heightInsert);
    bool BrickAngleBottom(int indexRow,int heightInsert);
    bool BrickAngleTop(int indexRow,int heightPillar,int heightInsert);
    //---------------------------------------------------------------

    //���������� �������� ���� �������
    int GetCountBrickAngleOnPallet(int Count);
    //���������� �������� ���� ������� ����������
    int GetCountBrickAnglePrimOnPallet(int Count);
    //���������� �������� ��� ������ ������
    int GetCountCoverColumnOnPallet(int Count);
    //���������� �������� ��� ����� ��������
    int GetCountBrickOnPallet(int Count);
    //���������� �������� ���� ������� ��������
    int GetCountBrickDobOnPallet(int Count);
    //���������� �������� ��� ������ �������
    int GetCountCoverOnPallet(int Count);
    int GetCountBaseOnPallet(int Count);
private:
    SettingItem *itemSetting;

};

#endif // CALCULATE_H
