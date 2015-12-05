#ifndef SETTINGCOLOR_H
#define SETTINGCOLOR_H
#include <QFile>
#include <QImage>

class SettingColor
{
public:
    enum COLOR_BRICK_TYPE{// типы бриков
        COLOR_BRICK_PILLAR_TOP              = 0, // Крышка столба
        COLOR_BRICK_PILLAR_BOTTOM           = 1, // Оснавание столба
        COLOR_BRICK_PILLAR_BIG              = 2, // Брик угловой
        COLOR_BRICK_PILLAR_SMALL            = 3, // Брик угловой проходной

        COLOR_BRICK_WALL_TOP                = 4, // Крышка полотна
        COLOR_BRICK_WALL_BOTTOM             = 5, // Ригель
        COLOR_BRICK_WALL_BIG                = 6, // Брик рядовой
        COLOR_BRICK_WALL_SMALL              = 7, // Брик рядовой доборный
        COLOR_BRICK_TYPE_ALL                = 8, // Кол-во типов
        COLOR_BRICK_TYPE_NONE               = -1 // тип отсутствует
    };
    enum CHANGE{// текущие изменения
        CHANGE_APPEND               = 1, // добавления
        CHANGE_REMOVE               = 2, // удаление
        CHANGE_NONE                 = 0 // нет изменений
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
    SettingColor::COLOR_BRICK_TYPE colorType(QString name);//Возвращает тип брика по названию
    SettingColor::COLOR_BRICK_TYPE colorType(int type);//Возвращает тип брика по индефикатору
    QString nameType(SettingColor::COLOR_BRICK_TYPE type);//Возвращает имя брика по типу
    QString nameType(int type);//Возвращает имя брика по индефикатору
    SettingColor::COLOR_BRICK *colorBrick(SettingColor::COLOR_BRICK_TYPE type,QString nameColor);
    QList<SettingColor::COLOR_BRICK*> colorBrick(SettingColor::COLOR_BRICK_TYPE type);
    void dontSave();
protected:
    bool saveColorBrick(QDataStream *outFile);
    void loadColorBrick(QDataStream *inFile);
private:
    struct NAME_TYPE{//тип и название типа брика
        NAME_TYPE();
        NAME_TYPE(SettingColor::COLOR_BRICK_TYPE type,QString name);
        NAME_TYPE operator=(NAME_TYPE name_type);
        SettingColor::COLOR_BRICK_TYPE type;
        QString name;
    };
    //массив типов и названия типов брика
    NAME_TYPE namedType[(int)SettingColor::COLOR_BRICK_TYPE_ALL];
    //массив директорий сохраняемых тайлов
    QString pathColorBrick[(int)SettingColor::COLOR_BRICK_TYPE_ALL];
    //массив списков хранящих тайлы и названия бриков
    QList<SettingColor::COLOR_BRICK*> allColorBrick[(int)SettingColor::COLOR_BRICK_TYPE_ALL];
    bool saveImage();

};

#endif // SETTINGCOLOR_H
