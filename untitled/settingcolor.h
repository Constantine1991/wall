#ifndef SETTINGCOLOR_H
#define SETTINGCOLOR_H
#include <QFile>
#include <QImage>

class SettingColor
{
public:
    enum COLOR_BRICK_TYPE{// ���� ������
        COLOR_BRICK_PILLAR_TOP              = 0, // ������ ������
        COLOR_BRICK_PILLAR_BOTTOM           = 1, // ��������� ������
        COLOR_BRICK_PILLAR_BIG              = 2, // ���� �������
        COLOR_BRICK_PILLAR_SMALL            = 3, // ���� ������� ���������

        COLOR_BRICK_WALL_TOP                = 4, // ������ �������
        COLOR_BRICK_WALL_BOTTOM             = 5, // ������
        COLOR_BRICK_WALL_BIG                = 6, // ���� �������
        COLOR_BRICK_WALL_SMALL              = 7, // ���� ������� ��������
        COLOR_BRICK_TYPE_ALL                = 8, // ���-�� �����
        COLOR_BRICK_TYPE_NONE               = -1 // ��� �����������
    };
    enum CHANGE{// ������� ���������
        CHANGE_APPEND               = 1, // ����������
        CHANGE_REMOVE               = 2, // ��������
        CHANGE_NONE                 = 0 // ��� ���������
    };
    struct COLOR_BRICK{
        COLOR_BRICK();
        COLOR_BRICK(QString nameColor,QString nameImage1,QImage image1);
        COLOR_BRICK(QString nameColor,QString nameImage1,QImage image1,QString nameImage2,QImage image2);
        COLOR_BRICK(COLOR_BRICK const &brick);
        COLOR_BRICK operator =(COLOR_BRICK brick);
        bool operator ==(COLOR_BRICK const brick);
        QString nameColor;
        QString nameImage1;
        QImage image1;
        QString nameImage2;
        QImage image2;
        SettingColor::CHANGE change;
    };
    SettingColor();
    ~SettingColor();
    bool append(SettingColor::COLOR_BRICK_TYPE type, COLOR_BRICK brick);
    void remove(SettingColor::COLOR_BRICK_TYPE type,QString nameColorImage);
    SettingColor::COLOR_BRICK_TYPE colorType(QString name);//���������� ��� ����� �� ��������
    SettingColor::COLOR_BRICK_TYPE colorType(int type);//���������� ��� ����� �� ������������
    QString nameType(SettingColor::COLOR_BRICK_TYPE type);//���������� ��� ����� �� ����
    QString nameType(int type);//���������� ��� ����� �� ������������
    SettingColor::COLOR_BRICK *colorBrick(SettingColor::COLOR_BRICK_TYPE type,QString nameColor);
    QList<SettingColor::COLOR_BRICK*> colorBrick(SettingColor::COLOR_BRICK_TYPE type);
    void dontSave();
protected:
    bool saveColorBrick(QDataStream *outFile);
    void loadColorBrick(QDataStream *inFile);
private:
    struct NAME_TYPE{//��� � �������� ���� �����
        NAME_TYPE();
        NAME_TYPE(SettingColor::COLOR_BRICK_TYPE type,QString name);
        NAME_TYPE operator=(NAME_TYPE name_type);
        SettingColor::COLOR_BRICK_TYPE type;
        QString name;
    };
    //������ ����� � �������� ����� �����
    NAME_TYPE namedType[(int)SettingColor::COLOR_BRICK_TYPE_ALL];
    //������ ���������� ����������� ������
    QString pathColorBrick[(int)SettingColor::COLOR_BRICK_TYPE_ALL];
    //������ ������� �������� ����� � �������� ������
    QList<SettingColor::COLOR_BRICK*> allColorBrick[(int)SettingColor::COLOR_BRICK_TYPE_ALL];
    bool saveImage();

};

#endif // SETTINGCOLOR_H
