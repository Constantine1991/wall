#ifndef PROPERTIESITEM_H
#define PROPERTIESITEM_H
#define PI  3.14159265358979323846

#include <QColor>
#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <qmath.h>


struct COLOR{
    COLOR(){
        this->caption="";
        this->color=Qt::white;
    }
    COLOR(QColor color,QString caption){
        this->color=color;
        this->caption=caption;
    }
    COLOR(COLOR const &src)
    {
        this->color=src.color;
        this->caption=src.caption;
    }
    COLOR operator=(COLOR src)
    {
        this->color=src.color;
        this->caption=src.caption;
        return *this;
    }
    bool operator==(COLOR const &src)
    {
        if(this->color==src.color && this->caption==src.caption)
            return true;
        return false;
    }
    QColor color;
    QString caption;
};

typedef enum _SIDE{ // сторона
    LEFT    = 1,
    RIGHT   = 2,
    FRONT   = 3,
    BACK    = 4
}SIDE;

typedef struct _INSERTPILLAR{ // Вставки столба
    SIDE side;//Сторона столба
    int insertTop;// Высота верхней вставки
    int insertBottom;//Высота нижней вставки
}INSERTPILLAR,*pINSERTPILLAR;

typedef struct _PALLAR{//Столб
    int height;//Высота столба
    pINSERTPILLAR insert; // Пазы сторон столба
    bool top; // Крашка столба
    QColor colorTop;//Цвет крышки столба
    QList<QColor> colorBlocks;//Цвет блоков столба
    bool pazzle;
    QColor colorPazzle1;
    QColor colorPazzle2;
}PILLAR,*pPILLAR;

typedef struct _WALL{ //Стена
    int height; // Высота
    int width;  // Длина
    bool wallTop; // Крышка полотна
    QColor colorTop;//Цвет крышки полотна
    QList<QColor> colorBlocks; // цвет ряда блоков
    bool pazzle;//Мазайка
    QColor colorPazzle1;
    QColor colorPazzle2;
    int d;
    QColor colorDicoreit;
}WALL,*pWALL;

typedef enum _TYPEITEM{ // Типы объектов
    ITEM_PILLAR      = 1, //Столб
    ITEM_WALL        = 2, //Стена
    ITEM_GATE_A      = 3, //Ворота откатные
    ITEM_GATE_B      = 4, //Ворота распашные
    ITEM_WICKET      = 5, //Калитка
    ITEM_TEXT        = 6,
    ITEM_FILLING     = 7,// Автоматическое заполнение
    ITEM_LINE        = 9,// Линейка
    ITEM_UNIVER      = 10,
    ITEM_NONE        = 0
}TYPEITEM;

typedef struct _CHILD{
    _CHILD(int idChild,bool resize,QGraphicsItem *itemChild)
    {
        this->idChild=idChild;
        this->resize=resize;
        this->itemChild=itemChild;
    }
    int idChild;
    bool resize;
    QGraphicsItem *itemChild;
}CHILD;

typedef struct _ITEM{//описаниекомпонентов
    int id; // Индефикатор компонента
    TYPEITEM type; // Тип компонента
    pPILLAR pillar;
    pWALL wall;
    QList<CHILD*> child;
}ITEM;

typedef struct _SETTINGS{//Хранение настроек компонентов
    _SETTINGS(){
        this->heightBrickAngle=1;
        this->heightBrickR=1;
        this->maxWidthBrickR=1;
        this->maxWidthGirth=1;
        this->minWidthBrickR=1;
        this->minWidthGirth=1;
        this->widthWallTop=1;
    }
    int minWidthBrickR; //Ширина брика рядового доборного
    int maxWidthBrickR; // Ширина брика рядового
    int heightBrickR; // Высота брика рядового
    int heightBrickAngle; // Высота брика углового и брика углового примыкание
    int maxWidthGirth; // Максимальная длина ригеля
    int minWidthGirth; // Минимальная длина ригеля
    int widthWallTop; // Ширина крышки полотна
    QList<COLOR*> color; // Список цветов
}SETTINGS;

static int TableAngle[2][8]={{1,0,-1,-1,-1,0,1,1},
                             {1,1,1,0,-1,-1,-1,0}};
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
