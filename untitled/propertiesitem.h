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

typedef enum _SIDE{ // �������
    LEFT    = 1,
    RIGHT   = 2,
    FRONT   = 3,
    BACK    = 4
}SIDE;

typedef struct _INSERTPILLAR{ // ������� ������
    SIDE side;//������� ������
    int insertTop;// ������ ������� �������
    int insertBottom;//������ ������ �������
}INSERTPILLAR,*pINSERTPILLAR;

typedef struct _PALLAR{//�����
    int height;//������ ������
    pINSERTPILLAR insert; // ���� ������ ������
    bool top; // ������ ������
    QColor colorTop;//���� ������ ������
    QList<QColor> colorBlocks;//���� ������ ������
    bool pazzle;
    QColor colorPazzle1;
    QColor colorPazzle2;
}PILLAR,*pPILLAR;

typedef struct _WALL{ //�����
    int height; // ������
    int width;  // �����
    bool wallTop; // ������ �������
    QColor colorTop;//���� ������ �������
    QList<QColor> colorBlocks; // ���� ���� ������
    bool pazzle;//�������
    QColor colorPazzle1;
    QColor colorPazzle2;
    int d;
    QColor colorDicoreit;
}WALL,*pWALL;

typedef enum _TYPEITEM{ // ���� ��������
    ITEM_PILLAR      = 1, //�����
    ITEM_WALL        = 2, //�����
    ITEM_GATE_A      = 3, //������ ���������
    ITEM_GATE_B      = 4, //������ ��������
    ITEM_WICKET      = 5, //�������
    ITEM_TEXT        = 6,
    ITEM_FILLING     = 7,// �������������� ����������
    ITEM_LINE        = 9,// �������
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

typedef struct _ITEM{//�������������������
    int id; // ����������� ����������
    TYPEITEM type; // ��� ����������
    pPILLAR pillar;
    pWALL wall;
    QList<CHILD*> child;
}ITEM;

typedef struct _SETTINGS{//�������� �������� �����������
    _SETTINGS(){
        this->heightBrickAngle=1;
        this->heightBrickR=1;
        this->maxWidthBrickR=1;
        this->maxWidthGirth=1;
        this->minWidthBrickR=1;
        this->minWidthGirth=1;
        this->widthWallTop=1;
    }
    int minWidthBrickR; //������ ����� �������� ���������
    int maxWidthBrickR; // ������ ����� ��������
    int heightBrickR; // ������ ����� ��������
    int heightBrickAngle; // ������ ����� �������� � ����� �������� ����������
    int maxWidthGirth; // ������������ ����� ������
    int minWidthGirth; // ����������� ����� ������
    int widthWallTop; // ������ ������ �������
    QList<COLOR*> color; // ������ ������
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
