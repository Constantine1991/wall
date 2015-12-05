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
    enum TYPEITEM{ // Типы объектов
        ITEM_PILLAR                 = 1, //Столб
        ITEM_WALL                   = 2, //Стена
        ITEM_GATE_A                 = 3, //Ворота распашные
        ITEM_GATE_B                 = 4, //Ворота откатные
        ITEM_WICKET                 = 5, //Калитка
        ITEM_TEXT                   = 6,
        ITEM_FILLING                = 7,// Автоматическое заполнение
        ITEM_LINE                   = 9,// Линейка
        ITEM_NONE                   = 0
    };



    int minWidthBrickR; //Ширина брика рядового доборного
    int maxWidthBrickR; // Ширина брика рядового
    int heightBrickR; // Высота брика рядового
    int heightBrickAngle; // Высота брика углового и брика углового примыкание
    int maxWidthGirth; // Максимальная длина ригеля
    int minWidthGirth; // Минимальная длина ригеля
    int widthWallTop; // Ширина крышки полотна

    SettingItem();
    ~SettingItem();
    //Сохранить добавленные настройки
    bool save();
    //Загрузить добавленные настройки
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
