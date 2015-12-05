#ifndef CALCULATE_H
#define CALCULATE_H
//column - столб
//fence - забор
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
    int count_brick; //Количестко бриков рядовых
    int count_brick_dob; //Количестко бриков рядовых доборных
    int count_cover; //Количество крышек
};

struct COLUMN {
    COLUMN(){
        this->count_brick_angle=0;
        this->count_brick_angle_1=0;
        this->count_brick_angle_2=0;
        this->count_brick_angle_3=0;
        this->count_brick_angle_4=0;
    }
    int count_brick_angle; //Количество бриков угловых
    int count_brick_angle_1; //Количество бриков угловых примыкание первой стороны
    int count_brick_angle_2; //Количество бриков угловых примыкание второй стороны
    int count_brick_angle_3; //Количество бриков угловых примыкание третьей стороны
    int count_brick_angle_4; //Количество бриков угловых примыкание четвертой стороны
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
    //Количество материала на забор
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

    ///Количество материала на столб
    COLUMN GetCountOnColumn(int HeightPillar,int* Insert,int CountSide);
    int getCountBrickAngle(int heightInsert);
    bool BrickAngleBottom(int indexRow,int heightInsert);
    bool BrickAngleTop(int indexRow,int heightPillar,int heightInsert);
    //---------------------------------------------------------------

    //Количество поддонов брик угловой
    int GetCountBrickAngleOnPallet(int Count);
    //Количество поддонов брик угловой примыкание
    int GetCountBrickAnglePrimOnPallet(int Count);
    //Количество поддонов для крышки столба
    int GetCountCoverColumnOnPallet(int Count);
    //Количество поддонов для брика рядового
    int GetCountBrickOnPallet(int Count);
    //Количество поддонов брик рядовых доборных
    int GetCountBrickDobOnPallet(int Count);
    //Количество поддонов для крышек полотна
    int GetCountCoverOnPallet(int Count);
    int GetCountBaseOnPallet(int Count);
private:
    SettingItem *itemSetting;

};

#endif // CALCULATE_H
