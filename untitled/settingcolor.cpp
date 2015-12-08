#include "settingcolor.h"
#include "QDebug"
SettingColor::COLOR_BRICK::COLOR_BRICK()
{
    this->change=SettingColor::CHANGE_NONE;
    this->nameColor="";
    this->nameImage1="";
    this->nameImage2="";
}

SettingColor::COLOR_BRICK::COLOR_BRICK(QString nameColor, QString nameImage1, QImage image1)
{
    this->nameColor=nameColor;
    this->nameImage1=nameImage1;
    this->image1=image1;
    this->change=SettingColor::CHANGE_NONE;
}

SettingColor::COLOR_BRICK::COLOR_BRICK(QString nameColor, QString nameImage1, QImage image1, QString nameImage2, QImage image2)
{
    this->nameColor=nameColor;
    this->nameImage1=nameImage1;
    this->image1=image1;
    this->nameImage2=nameImage2;
    this->image2=image2;
    this->change=SettingColor::CHANGE_NONE;
}

SettingColor::COLOR_BRICK::COLOR_BRICK(const COLOR_BRICK &brick)
{
    this->nameColor=brick.nameColor;
    this->nameImage1=brick.nameImage1;
    this->image1=brick.image1;
    this->nameImage2=brick.nameImage2;
    this->image2=brick.image2;
    this->change=brick.change;
}

SettingColor::COLOR_BRICK SettingColor::COLOR_BRICK::operator =(SettingColor::COLOR_BRICK brick)
{
    this->nameColor=brick.nameColor;
    this->nameImage1=brick.nameImage1;
    this->image1=brick.image1;
    this->nameImage2=brick.nameImage2;
    this->image2=brick.image2;
    this->change=brick.change;
    return *this;
}

bool SettingColor::COLOR_BRICK::operator ==(SettingColor::COLOR_BRICK brick)
{
    if(this->nameColor==brick.nameColor && this->nameImage1==brick.nameImage1 && this->image1==brick.image1 &&
       this->nameImage2==brick.nameImage2 && this->image2==brick.image2)
        return true;
    return false;
}

SettingColor::NAME_TYPE::NAME_TYPE()
{
    this->type=SettingColor::COLOR_BRICK_TYPE_NONE;
    this->name="";
}

SettingColor::NAME_TYPE::NAME_TYPE(SettingColor::COLOR_BRICK_TYPE type, QString name)
{
    this->type=type;
    this->name=name;
}

SettingColor::NAME_TYPE SettingColor::NAME_TYPE::operator =(SettingColor::NAME_TYPE name_type)
{
    this->type=name_type.type;
    this->name=name_type.name;
    return *this;
}

SettingColor::SettingColor()
{
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_PILLAR_TOP]="Color\\Pillar\\top\\";
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_PILLAR_BOTTOM]="Color\\Pillar\\bottom\\";
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_PILLAR_BIG]="Color\\Pillar\\big\\";
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_PILLAR_SMALL]="Color\\Pillar\\small\\";
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_WALL_TOP]="Color\\Wall\\top\\";
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_WALL_BOTTOM]="Color\\Wall\\bottom\\";
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_WALL_BIG]="Color\\Wall\\big\\";
    this->pathColorBrick[(int)SettingColor::COLOR_BRICK_WALL_SMALL]="Color\\Wall\\small\\";

    this->namedType[(int)SettingColor::COLOR_BRICK_PILLAR_TOP]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_PILLAR_TOP,QString::fromLocal8Bit("Крышка столба"));
    this->namedType[(int)SettingColor::COLOR_BRICK_PILLAR_BOTTOM]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_PILLAR_BOTTOM,QString::fromLocal8Bit("Основание столба"));
    this->namedType[(int)SettingColor::COLOR_BRICK_PILLAR_BIG]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_PILLAR_BIG,QString::fromLocal8Bit("Брик угловой"));
    this->namedType[(int)SettingColor::COLOR_BRICK_PILLAR_SMALL]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_PILLAR_SMALL,QString::fromLocal8Bit("Брик угловой вставка"));
    this->namedType[(int)SettingColor::COLOR_BRICK_WALL_TOP]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_WALL_TOP,QString::fromLocal8Bit("Крышка полотна"));
    this->namedType[(int)SettingColor::COLOR_BRICK_WALL_BOTTOM]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_WALL_BOTTOM,QString::fromLocal8Bit("Ригель"));
    this->namedType[(int)SettingColor::COLOR_BRICK_WALL_BIG]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_WALL_BIG,QString::fromLocal8Bit("Брик рядовой"));
    this->namedType[(int)SettingColor::COLOR_BRICK_WALL_SMALL]=SettingColor::NAME_TYPE(SettingColor::COLOR_BRICK_WALL_SMALL,QString::fromLocal8Bit("Брик рядовой доборный"));
}

SettingColor::~SettingColor()
{
}

SettingColor::COLOR_BRICK_TYPE SettingColor::colorType(QString name)
{
    for(int i=0;(int)SettingColor::COLOR_BRICK_TYPE_ALL;i++)
        if(this->namedType[i].name==name)
            return this->namedType[i].type;
    return SettingColor::COLOR_BRICK_TYPE_NONE;
}

SettingColor::COLOR_BRICK_TYPE SettingColor::colorType(int type)
{
    if(((int)SettingColor::COLOR_BRICK_TYPE_NONE<type) && ((int)SettingColor::COLOR_BRICK_TYPE_ALL>type))
        return this->namedType[type].type;
    return SettingColor::COLOR_BRICK_TYPE_NONE;
}

QString SettingColor::nameType(SettingColor::COLOR_BRICK_TYPE type)
{
    if(type==SettingColor::COLOR_BRICK_TYPE_NONE || type==SettingColor::COLOR_BRICK_TYPE_NONE)
        return QString("");
    return this->namedType[(int)type].name;
}

QString SettingColor::nameType(int type)
{
    if(((int)SettingColor::COLOR_BRICK_TYPE_NONE<type) && ((int)SettingColor::COLOR_BRICK_TYPE_ALL>type))
        return this->namedType[type].name;
    return QString("");
}

bool SettingColor::append(SettingColor::COLOR_BRICK_TYPE type, SettingColor::COLOR_BRICK brick)
{
    if(type==SettingColor::COLOR_BRICK_TYPE_NONE || type==SettingColor::COLOR_BRICK_TYPE_NONE)
        return false;
    foreach(SettingColor::COLOR_BRICK *b,this->allColorBrick[(int)type])
    {
        if(brick.nameImage2.isEmpty())
        {
            if(b->nameColor==brick.nameColor || b->nameImage1==brick.nameImage1)
                return false;
        }else{
            if(b->nameColor==brick.nameColor || b->nameImage1==brick.nameImage1 || b->nameImage2==brick.nameImage2)
                return false;
        }
    }
    brick.change=SettingColor::CHANGE_APPEND;
    this->allColorBrick[(int)type].append(new SettingColor::COLOR_BRICK(brick));
    return true;
}

void SettingColor::remove(SettingColor::COLOR_BRICK_TYPE type, QString nameColor)
{
    if(type==SettingColor::COLOR_BRICK_TYPE_NONE || type==SettingColor::COLOR_BRICK_TYPE_NONE)
        return;
    foreach(SettingColor::COLOR_BRICK *color,this->allColorBrick[(int)type])
        if(color->nameColor==nameColor)
        {
            color->change=SettingColor::CHANGE_REMOVE;
            break;
        }
}

SettingColor::COLOR_BRICK *SettingColor::colorBrick(SettingColor::COLOR_BRICK_TYPE type, QString nameColor)
{
    if(type==SettingColor::COLOR_BRICK_TYPE_NONE || type==SettingColor::COLOR_BRICK_TYPE_NONE)
        return NULL;
    foreach(SettingColor::COLOR_BRICK *brick,this->allColorBrick[(int)type])
        if(brick->nameColor==nameColor)
            return brick;
    return NULL;
}

QList<SettingColor::COLOR_BRICK *> SettingColor::colorBrick(SettingColor::COLOR_BRICK_TYPE type)
{
    QList<SettingColor::COLOR_BRICK*> empty;
    if(type==SettingColor::COLOR_BRICK_TYPE_NONE || type==SettingColor::COLOR_BRICK_TYPE_NONE)
        return empty;
    return this->allColorBrick[(int)type];
}

void SettingColor::dontSave()
{
    for(int i=0;i<(int)SettingColor::COLOR_BRICK_TYPE_ALL;i++)
    {
        foreach(SettingColor::COLOR_BRICK *brick,this->allColorBrick[i])
        {
            if(brick->change==SettingColor::CHANGE_NONE)
                continue;
            if(brick->change==SettingColor::CHANGE_REMOVE)
                brick->change=SettingColor::CHANGE_NONE;
            if(brick->change==SettingColor::CHANGE_APPEND)
            {
                this->allColorBrick[i].removeAt(this->allColorBrick[i].indexOf(brick));
                delete brick;
            }
        }
    }
}

bool SettingColor::saveImage()
{
    for(int i=0;i<(int)SettingColor::COLOR_BRICK_TYPE_ALL;i++)
        foreach(SettingColor::COLOR_BRICK *brick,this->allColorBrick[i])
        {
            if(brick->change==SettingColor::CHANGE_REMOVE)
            {
                QFile::remove(this->pathColorBrick[i]+brick->nameImage1+".png");
                if((i==(int)SettingColor::COLOR_BRICK_PILLAR_BIG) || (i==(int)SettingColor::COLOR_BRICK_PILLAR_SMALL)||
                   (i==(int)SettingColor::COLOR_BRICK_PILLAR_BOTTOM))
                    QFile::remove(this->pathColorBrick[i]+brick->nameImage2+".png");
                this->allColorBrick[i].removeAt(this->allColorBrick[i].indexOf(brick));
            }
            if(brick->change==SettingColor::CHANGE_APPEND)
            {
                brick->image1.save(this->pathColorBrick[i]+brick->nameImage1+".png");
                if((i==(int)SettingColor::COLOR_BRICK_PILLAR_BIG) || (i==(int)SettingColor::COLOR_BRICK_PILLAR_SMALL)||
                   (i==(int)SettingColor::COLOR_BRICK_PILLAR_BOTTOM))
                    brick->image2.save(this->pathColorBrick[i]+brick->nameImage2+".png");
            }

        }
    return true;
}

bool SettingColor::saveColorBrick(QDataStream *outFile)
{
    if(!this->saveImage())
        return false;
    for(int i=0;i<(int)SettingColor::COLOR_BRICK_TYPE_ALL;i++)
    {
        *outFile<<this->allColorBrick[i].count();
        foreach(SettingColor::COLOR_BRICK *brick,this->allColorBrick[i])
            if(((int)SettingColor::COLOR_BRICK_PILLAR_BIG==i) ||((int)SettingColor::COLOR_BRICK_PILLAR_SMALL==i)||
               ((int)SettingColor::COLOR_BRICK_PILLAR_BOTTOM==i))
                *outFile<<brick->nameColor<<brick->nameImage1<<brick->nameImage2;
            else *outFile<<brick->nameColor<<brick->nameImage1;
    }
    return true;
}

void SettingColor::loadColorBrick(QDataStream *inFile)
{
    for(int i=0;i<(int)SettingColor::COLOR_BRICK_TYPE_ALL;i++)
    {
        int countColor=0;
        *inFile>>countColor;
        for(int j=0;j<countColor;j++)
        {
            QString nameColor;
            QString nameImage1;
            if(((int)SettingColor::COLOR_BRICK_PILLAR_BIG==i) ||((int)SettingColor::COLOR_BRICK_PILLAR_SMALL==i)||
               ((int)SettingColor::COLOR_BRICK_PILLAR_BOTTOM==i))
            {
                QString nameImage2;
                *inFile>>nameColor>>nameImage1>>nameImage2;
                qDebug()<<"Load Image:"<<nameColor<<nameImage1<<nameImage2;
                this->allColorBrick[i].append(new SettingColor::COLOR_BRICK(nameColor,nameImage1,
                                                                            QImage(this->pathColorBrick[i]+nameImage1+".png"),
                                                                            nameImage2,
                                                                            QImage(this->pathColorBrick[i]+nameImage2+".png")));
            } else {
                *inFile>>nameColor>>nameImage1;
                qDebug()<<"Load Image:"<<nameColor<<nameImage1;
                this->allColorBrick[i].append(new SettingColor::COLOR_BRICK(nameColor,nameImage1,
                                                                            QImage(this->pathColorBrick[i]+nameImage1+".png")));
            }
        }
    }
}
