#include "propertiesitem.h"

SettingItem::SettingItem():SettingColor()
{
    this->heightBrickAngle=1;
    this->heightBrickR=1;
    this->maxWidthBrickR=1;
    this->maxWidthGirth=1;
    this->minWidthBrickR=1;
    this->minWidthGirth=1;
    this->widthWallTop=1;


}

SettingItem::~SettingItem()
{

}

bool SettingItem::save()
{
    QFile saveFile("setting.dat");
    if(!saveFile.open(QIODevice::WriteOnly))
        return false;
    QDataStream outFile(&saveFile);
    outFile<<this->minWidthBrickR<<this->maxWidthBrickR<<this->heightBrickR<<this->heightBrickAngle<<
             this->maxWidthGirth<<this->minWidthGirth<<widthWallTop;
    if(!this->saveColorBrick(&outFile))
    {
        saveFile.close();
        return false;
    }
    saveFile.close();
    return true;
}

bool SettingItem::load()
{
    QFile loadFile("setting.dat");
    if(!loadFile.open(QIODevice::ReadOnly))
        return false;
    QDataStream inFile(&loadFile);
    inFile>>this->minWidthBrickR>>this->maxWidthBrickR>>this->heightBrickR>>this->heightBrickAngle>>
            this->maxWidthGirth>>this->minWidthGirth>>widthWallTop;
    this->loadColorBrick(&inFile);
    loadFile.close();
    return true;
}
