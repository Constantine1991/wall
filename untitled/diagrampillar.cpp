#include "diagrampillar.h"
#include "QDebug"

DiagramPillar::DiagramPillar()
{
    this->graphicTileTop=NULL;
    this->graphicTileBottom=NULL;
    this->settingItem=NULL;
    this->enablePazzle=false;
}

DiagramPillar::~DiagramPillar()
{
    if(this->graphicTileTop!=NULL)
    {
        qDebug()<<"~DiagramPillar delete tile top";
        delete this->graphicTileTop;
    }
    if(this->graphicTileBottom!=NULL)
    {
        qDebug()<<"~DiagramPillar delete tile bottom";
        delete this->graphicTileBottom;
    }
    if(!this->graphicsTileBricks.isEmpty())
    {
        qDebug()<<"~DiagramPillar delete tile brick";
        this->clearGraphicsTileBricks();
    }
}

void DiagramPillar::setSettingItem(SettingItem *settingItem)
{
    this->settingItem=settingItem;
}

void DiagramPillar::setPos(int x, int y)
{
    this->x=x;
    this->y=y-40;//Смещение столба в вверх на 40
}

QPoint DiagramPillar::pos()
{
    return QPoint(this->x,this->y);
}

void DiagramPillar::setSizeBrickTile(int w, int h)
{
    this->tileBrickWidth=w;
    this->tileBrickHeight=h;
}

void DiagramPillar::setSizeTopTile(int w, int h)
{
    this->tileTopWidth=w;
    this->tileTopHeight=h;
}

void DiagramPillar::setSizeBottomTile(int w, int h)
{
    this->tileBottomWidth=w;
    this->tileBottomHeight=h;
}

void DiagramPillar::setHeight(int h)
{
    this->height=h;
    if(this->graphicsTileBricks.count()>(this->row()*2))
    {
        for(int i=this->graphicsTileBricks.count()-1;i>=(this->row()*2);i--)
        {
            delete this->graphicsTileBricks.last();
            this->graphicsTileBricks.removeLast();
        }
        for(int i=this->colorTileBricks.count();i>this->row();i--)
        {
            qDebug()<<"color count:"<<this->colorTileBricks.count()<<" row cout:"<<this->row();
            this->colorTileBricks.removeLast();
        }
        return;
    }
    for(int i=(this->graphicsTileBricks.count()/2);i<this->row();i++)
    {
        this->graphicsTileBricks.append(this->createItem(this->tileBrickWidth,this->tileBrickHeight));
        this->graphicsTileBricks.append(this->createItem(this->tileBrickWidth/2,this->tileBrickHeight));
        this->colorTileBricks.append(QString(""));
    }
}

void DiagramPillar::setInsert(int side, int insert)
{
    this->insert[side]=insert;
}

void DiagramPillar::setTop(bool enable)
{
    if(enable)
    {
        if(this->graphicTileTop==NULL)
            this->graphicTileTop=this->createItem(this->tileTopWidth,this->tileTopHeight);
    }
    else{
        if(this->graphicTileTop!=NULL)
        {
            delete this->graphicTileTop;
            this->graphicTileTop=NULL;
        }
    }
}

void DiagramPillar::setTopColor(QString nameColor)
{
    if(this->graphicTileTop==NULL)
    {
        qDebug()<<QString::fromLocal8Bit("Неудалось применить цвет к крышке столба т.к./n не выделанна память");
        return;
    }
    if(nameColor.isEmpty())
    {
        qDebug()<<QString::fromLocal8Bit("Неудалось применить цвет к крышке столба т.к./n не заданно имя цвета");
        return;
    }
    if(this->colorTileTop==nameColor)
        return;
    this->colorTileTop=nameColor;
    SettingItem::COLOR_BRICK *color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_TOP,this->colorTileTop);
    if(color==NULL)
    {
        qDebug()<<QString::fromLocal8Bit("Неудалось применить цвет к крышке столба т.к./n заданного цвета не существует");
        return;
    }
    this->graphicTileTop->setBrush(QBrush(color->image1.scaled(this->tileTopWidth,this->tileTopHeight)));
}

void DiagramPillar::setBottom(bool enable)
{
    if(enable)
    {
        if(this->graphicTileBottom==NULL)
            this->graphicTileBottom=this->createItem(this->tileBottomWidth,this->tileBottomHeight);
    }
    else{
        if(this->graphicTileBottom!=NULL)
        {
            delete this->graphicTileBottom;
            this->graphicTileBottom=NULL;
        }
    }
}

int DiagramPillar::row()
{
    return this->height/this->settingItem->heightBrickAngle;
}

int DiagramPillar::boundingRectHeight()
{
    return this->tileBottomHeight+this->row()*this->tileBrickHeight+this->tileTopHeight*2+40;
}

QString DiagramPillar::rowColor(int indexRow)
{
    if(indexRow>this->colorTileBricks.count())
        return QString("");
    return this->colorTileBricks.at(indexRow);
}

QList<QString> DiagramPillar::rowColor()
{
    return this->colorTileBricks;
}

void DiagramPillar::showSide(int side)
{
    switch(side)
    {
        case 0:this->side=DiagramPillar::FRONT; break;
        case 1:this->side=DiagramPillar::BACK;break;
        case 2:this->side=DiagramPillar::LEFT;break;
        case 3:this->side=DiagramPillar::RIGHT;break;
    }
}

void DiagramPillar::setRowColor(int indexRow, QString nameColor)
{
    if(nameColor.isEmpty())
    {
        qDebug()<<QString::fromLocal8Bit("Не удалось применить цвет к ряду столба/n т.к. цвет не указан");
        return;
    }
    if(indexRow<0 || indexRow>this->row())
    {
        qDebug()<<QString::fromLocal8Bit("Указанный индекс ряда не входит в диапазон рядов столба");
        return;
    }
    if(this->colorTileBricks.count()>=indexRow)
    {
        qDebug()<<"Insert color row";
        this->colorTileBricks.removeAt(indexRow-1);
        this->colorTileBricks.insert(indexRow-1,nameColor);
    }
//    qDebug()<<"setRowColor() count colors:"<<this->colorTileBricks.count();
}

void DiagramPillar::setRowColor(QList<QString> colorsTile)
{
    this->colorTileBricks.clear();
    this->colorTileBricks.append(colorsTile);
}

void DiagramPillar::setRowColorAll(QString nameColor)
{
    if(nameColor.isEmpty())
    {
        qDebug()<<QString::fromLocal8Bit("Не удалось применить цвет к ряду столба/n т.к. цвет не указан");
        return;
    }
    this->colorTileBricks.clear();
    for(int i=0;i<this->row();i++)
        this->colorTileBricks.append(nameColor);
}

void DiagramPillar::setPazzleColor(bool enable)
{
    this->enablePazzle=enable;

}

void DiagramPillar::setRowPazzleColor(QString nameColorAngle1, QString nameColorAngle2)
{
    if(nameColorAngle1.isEmpty() && nameColorAngle2.isEmpty())
    {
        qDebug()<<QString::fromLocal8Bit("Не удалось применить цвет к ряду столба/n т.к. цвет не указан");
        return;
    }
    this->namecolorPazzleAngle1=nameColorAngle1;
    this->namecolorPazzleAngle2=nameColorAngle2;
}

QList<QGraphicsRectItem*> DiagramPillar::update()
{
    QList<QGraphicsRectItem*> graphicItem;
    if(!this->graphicsTileBricks.isEmpty())
    {
        this->updateColorsTileBricks();
        this->setPosGraphicTileBricks(this->x,this->y);
        graphicItem.append(this->graphicsTileBricks);
    } else
        return graphicItem;
    if(this->graphicTileBottom!=NULL)
    {
        this->updateColorBottom();
        this->setPosGraphicTileBottom(this->x,this->y);
        graphicItem.append(this->graphicTileBottom);
    }
    if(this->graphicTileTop!=NULL)
    {
        this->setPosGraphicTileTop(this->x,this->y);
        graphicItem.append(this->graphicTileTop);
    }else
        this->colorTileTop.clear();
    return graphicItem;
}
/*-----------------------------------------------PRIVATE---------------------------------------------------*/


QGraphicsRectItem *DiagramPillar::createItem(int width, int height)
{
    QGraphicsRectItem *item=new QGraphicsRectItem();
    item->setBrush(QBrush(Qt::white));
    item->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    item->setRect(0,0,width,height);
    return item;
}

void DiagramPillar::setRowColor(int indexRow, SettingColor::COLOR_BRICK *colorAngleBrick, SettingColor::COLOR_BRICK *colorAngleInsert)
{
    if(indexRow>this->row())
    {
        qDebug()<<QString::fromLocal8Bit("Указанный индекс ряда не входит в диапазон рядов столба");
        return;
    }
    if(colorAngleBrick==NULL)
        qDebug()<<QString::fromLocal8Bit("Не удалось найти указанный цвет, брик угловой");
    if(this->insert[(int)this->side]!=0)
    {
        if(colorAngleInsert==NULL)
            qDebug()<<QString::fromLocal8Bit("Не удалось найти указанный цвет, брик угловой вставка");
    }
    if(this->insert[(int)this->side]==0 ||
        (this->insert[(int)this->side]/this->settingItem->heightBrickAngle)<indexRow)
    {
        if(colorAngleBrick!=NULL)
        {
            this->graphicsTileBricks.at(indexRow*2-2)->setBrush(QBrush(colorAngleBrick->image1.scaled(this->tileBrickWidth,
                                                                                                      this->tileBrickHeight)));
            this->graphicsTileBricks.at(indexRow*2-1)->setBrush(QBrush(colorAngleBrick->image2.scaled(this->tileBrickWidth/2,
                                                                                                      this->tileBrickHeight)));
        }
        return;
    }
    if((this->insert[(int)this->side]/this->settingItem->heightBrickAngle)>=indexRow)
    {
        if(colorAngleBrick!=NULL)
            this->graphicsTileBricks.at(indexRow*2-1)->setBrush(QBrush(colorAngleBrick->image2.scaled(this->tileBrickWidth/2,
                                                                                                      this->tileBrickHeight)));
        if(colorAngleInsert!=NULL)
        {
            if((indexRow-1) % 2 == 0)
                this->graphicsTileBricks.at(indexRow*2-2)->setBrush(QBrush(colorAngleInsert->image1.scaled(this->tileBrickWidth,
                                                                                                           this->tileBrickHeight)));
            else this->graphicsTileBricks.at(indexRow*2-2)->setBrush(QBrush(colorAngleInsert->image2.scaled(this->tileBrickWidth,
                                                                                                            this->tileBrickHeight)));
        }
        return;
    }
}

void DiagramPillar::setPazzleColor(QString color1, QString color2)
{
    for(int i=1;i<this->row()+1;i++)
    {
        if(this->side==DiagramPillar::FRONT || this->side==DiagramPillar::BACK)
        {
            if(this->insert[(int)this->side]==0 ||
                    (this->insert[(int)this->side]/this->settingItem->heightBrickAngle)<i)
            {
                SettingItem::COLOR_BRICK *colorAngle=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG,
                                                                                    color1);
                if(colorAngle!=NULL)
                    this->graphicsTileBricks.at(i*2-2)->setBrush(QBrush(colorAngle->image1.scaled(this->tileBrickWidth,
                                                                                                  this->tileBrickHeight)));
                colorAngle=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG,color2);
                if(colorAngle!=NULL)
                    this->graphicsTileBricks.at(i*2-1)->setBrush(QBrush(colorAngle->image2.scaled(this->tileBrickWidth/2,
                                                                                                  this->tileBrickHeight)));
                continue;
            }
            if((this->insert[(int)this->side]/this->settingItem->heightBrickAngle)>=i)
            {
                SettingItem::COLOR_BRICK *colorAngle=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG,
                                                                                   color2);
                if(colorAngle!=NULL)
                    this->graphicsTileBricks.at(i*2-1)->setBrush(QBrush(colorAngle->image2.scaled(this->tileBrickWidth/2,
                                                                                                      this->tileBrickHeight)));
                SettingItem::COLOR_BRICK *colorAngleInsert=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_SMALL,
                                                                                         color1);
                if(colorAngleInsert!=NULL)
                {
                    if((i-1) % 2 == 0)
                        this->graphicsTileBricks.at(i*2-2)->setBrush(QBrush(colorAngleInsert->image1.scaled(this->tileBrickWidth,
                                                                                                            this->tileBrickHeight)));
                    else this->graphicsTileBricks.at(i*2-2)->setBrush(QBrush(colorAngleInsert->image2.scaled(this->tileBrickWidth,
                                                                                                             this->tileBrickHeight)));
                }
                continue;
            }
        }
        if(this->side==DiagramPillar::LEFT || this->side==DiagramPillar::RIGHT)
        {
            if(this->insert[(int)this->side]==0 ||
                    (this->insert[(int)this->side]/this->settingItem->heightBrickAngle)<i)
            {
                SettingItem::COLOR_BRICK *colorAngle=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG,
                                                                                    color2);
                if(colorAngle!=NULL)
                    this->graphicsTileBricks.at(i*2-2)->setBrush(QBrush(colorAngle->image1.scaled(this->tileBrickWidth,
                                                                                                  this->tileBrickHeight)));
                colorAngle=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG,color1);
                if(colorAngle!=NULL)
                    this->graphicsTileBricks.at(i*2-1)->setBrush(QBrush(colorAngle->image2.scaled(this->tileBrickWidth/2,
                                                                                                  this->tileBrickHeight)));
                continue;
            }
            if((this->insert[(int)this->side]/this->settingItem->heightBrickAngle)>=i)
            {
                SettingItem::COLOR_BRICK *colorAngle=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG,
                                                                                   color1);
                if(colorAngle!=NULL)
                    this->graphicsTileBricks.at(i*2-1)->setBrush(QBrush(colorAngle->image2.scaled(this->tileBrickWidth/2,
                                                                                                      this->tileBrickHeight)));
                SettingItem::COLOR_BRICK *colorAngleInsert=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_SMALL,
                                                                                         color2);
                if(colorAngleInsert!=NULL)
                {
                    if((i-1) % 2 == 0)
                        this->graphicsTileBricks.at(i*2-2)->setBrush(QBrush(colorAngleInsert->image1.scaled(this->tileBrickWidth,
                                                                                                            this->tileBrickHeight)));
                    else this->graphicsTileBricks.at(i*2-2)->setBrush(QBrush(colorAngleInsert->image2.scaled(this->tileBrickWidth,
                                                                                                             this->tileBrickHeight)));
                }
                continue;
            }
        }
    }
}

void DiagramPillar::updateColorsTileBricks()
{
    if(this->enablePazzle)
        this->setPazzleColor(this->namecolorPazzleAngle1,this->namecolorPazzleAngle2);
    else
    {
        qDebug()<<"updateColorsTileBricks() count colors:"<<this->colorTileBricks.count();
        for(int i=0;i<this->row();i++)
            this->setRowColor(i+1,
                              this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG,this->colorTileBricks.at(i)),
                              this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_SMALL,this->colorTileBricks.at(i)));
    }
}


void DiagramPillar::setPosGraphicTileTop(int x, int y)
{
    if(this->graphicTileTop==NULL)
        return;
    y=y-(this->tileBottomHeight+(this->tileBrickHeight*this->row())+this->tileTopHeight);
    x=x-(this->tileTopWidth-(this->tileBrickWidth+this->tileBrickWidth/2))/2;
    this->graphicTileTop->setPos(x,y);
}


void DiagramPillar::setPosGraphicTileBricks(int x, int y)
{
    y=y-this->tileBottomHeight;
    for(int i=1;i<=this->row();i++)
    {
        y=y-this->tileBrickHeight;
        if((i-1) % 2 == 0)
        {
            this->graphicsTileBricks.at((i-1)*2)->setPos(x,y);
            this->graphicsTileBricks.at((i-1)*2+1)->setPos(x+this->tileBrickWidth,y);
        }else{
            this->graphicsTileBricks.at((i-1)*2)->setPos(x+this->tileBrickWidth/2,y);
            this->graphicsTileBricks.at((i-1)*2+1)->setPos(x,y);
        }
    }
}

void DiagramPillar::updateColorBottom()
{
    QList<SettingItem::COLOR_BRICK*> bottomColor=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BOTTOM);
    if(bottomColor.isEmpty())
        return;
    if(this->insert[(int)this->side]>0)
        this->graphicTileBottom->setBrush(QBrush(bottomColor.at(0)->image1.scaled(this->tileBottomWidth,
                                                                                  this->tileBottomHeight)));
    else this->graphicTileBottom->setBrush(QBrush(bottomColor.at(0)->image2.scaled(this->tileBottomWidth,
                                                                                   this->tileBottomHeight)));
}

void DiagramPillar::setPosGraphicTileBottom(int x, int y)
{
    if(this->graphicTileBottom==NULL)
        return;
    y=y-this->tileBottomHeight;
    x=x-(this->tileBottomWidth-(this->tileBrickWidth+this->tileBrickWidth/2))/2;
    this->graphicTileBottom->setPos(x,y);
}


void DiagramPillar::clearGraphicsTileBricks()
{
    foreach(QGraphicsRectItem *item,this->graphicsTileBricks)
        delete item;
    this->graphicsTileBricks.clear();
}
