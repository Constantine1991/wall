#include "diagramwall.h"
#include "QDebug"

DiagramWall::DiagramWall()
{
    this->height=0;
    this->width=0;
    this->graphicsTops=NULL;
    this->graphicsBottom=NULL;
    this->settingItem=NULL;
}

DiagramWall::~DiagramWall()
{
    this->clearTileBricks();
}

void DiagramWall::setSettingItem(SettingItem *settingItem)
{
    this->settingItem=settingItem;
    qDebug()<<this->settingItem->maxWidthBrickR;
    qDebug()<<this->settingItem->minWidthBrickR;
}


void DiagramWall::setHeight(int height)
{
    Calculate calc(this->settingItem);
    this->height=height;

    qDebug()<<this->colorsBricks.count()<<calc.rowBrickBigWall(this->height);
    if(this->colorsBricks.count()<calc.rowBrickBigWall(this->height))
        for(int i=this->colorsBricks.count();i<calc.rowBrickBigWall(this->height);i++)
            this->colorsBricks.append(QString(""));
    else
        for(int i=this->colorsBricks.count();i>calc.rowBrickBigWall(this->height);i--)
        {
            qDebug()<<i;
            this->colorsBricks.removeLast();
        }
}

void DiagramWall::setWidth(int width)
{
    this->width=width;
}

void DiagramWall::setPos(int x, int y)
{
    this->pos_x=x;
    this->pos_y=y;
}

void DiagramWall::setSizeTileBrick(int width, int height)
{
    this->sizeTileBrick.setHeight(height);
    this->sizeTileBrick.setWidth(width);
}

void DiagramWall::setSizeTileBottom(int width, int height)
{
    this->sizeTileBottom.setHeight(height);
    this->sizeTileBottom.setWidth(width);
}

void DiagramWall::setSizeTileTop(int width, int height)
{
    this->sizeTileTop.setWidth(width);
    this->sizeTileTop.setHeight(height);
}

void DiagramWall::setTop(bool enable)
{
    if(enable)
    {
        Calculate calc(this->settingItem);
        int width=calc.colBrickBigWall(this->width)*this->sizeTileBrick.width();
        if(calc.isBrickRD(this->width))
            width+=this->sizeTileBrick.width()/2;
        this->graphicsTops=this->createItem(width,this->sizeTileTop.height());
    }else{
        if(this->graphicsTops!=NULL)
            delete this->graphicsTops;
        this->graphicsTops=NULL;
    }
}

void DiagramWall::setColorTop(QString nameColor)
{
    if(this->graphicsTops==NULL)
        return;
    SettingItem::COLOR_BRICK *color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_TOP,
                                                                  nameColor);
    if(color!=NULL)
        this->graphicsTops->setBrush(QBrush(color->image1.scaled(this->graphicsTops->boundingRect().width(),
                                                                 this->sizeTileTop.height())));
}

void DiagramWall::setBootom(bool enable)
{
    if(enable)
    {
        Calculate calc(this->settingItem);
        int width=calc.colBrickBigWall(this->width)*this->sizeTileBrick.width();
        if(calc.isBrickRD(this->width))
            width+=this->sizeTileBrick.width()/2;
        this->graphicsBottom=this->createItem(width,this->sizeTileBottom.height());
    }else{
        if(this->graphicsBottom!=NULL)
            delete this->graphicsBottom;
        this->graphicsBottom=NULL;
    }
}

int DiagramWall::boundingRectWidth()
{
    if(this->settingItem!=NULL)
    {
        Calculate calc(this->settingItem);
        return calc.colBrickBigWall(this->width)*this->sizeTileBrick.width()+this->pos_x+50;
    }
    return 0;
}

int DiagramWall::row()
{
    Calculate calc(this->settingItem);
    return calc.rowBrickBigWall(this->height);
}

QString DiagramWall::colorRow(int indexRow)
{
    if(this->colorsBricks.isEmpty())
        return QString("");
    return this->colorsBricks.at(indexRow-1);
}

void DiagramWall::setColorRow(int indexRow, QString nameColor)
{
    if(this->colorsBricks.isEmpty())
        return;

    if(this->colorsBricks.count()>=indexRow)
    {
        if(this->colorsBricks.at(indexRow-1)==nameColor)
            return;
        this->colorsBricks.removeAt(indexRow-1);
        this->colorsBricks.insert(indexRow-1,nameColor);
    }
}

void DiagramWall::setColorRowAll(QString nameColor)
{
    this->colorsBricks.clear();
    for(int i=0;i<this->row();i++)
        this->colorsBricks.append(nameColor);
}

void DiagramWall::setColorRow(QList<QString> colors)
{
    this->colorsBricks.clear();
    this->colorsBricks.append(colors);
}

void DiagramWall::setPazzle(bool enable)
{
    this->pazzle=enable;
}

void DiagramWall::setColorPazzle(QString nameColor1, QString nameColor2)
{
    this->nameColorPazzle1=nameColor1;
    this->nameColorPazzle2=nameColor2;
}

QList<QGraphicsRectItem *> DiagramWall::update()
{
    QList<QGraphicsRectItem *> tiles;
    this->updateBricks();
    if(!this->graphicBricks.isEmpty())
        tiles.append(this->graphicBricks);
    else return tiles;
    if(this->graphicsTops!=NULL)
    {
        this->updateTops();
        tiles.append(this->graphicsTops);
    }
    if(this->graphicsBottom!=NULL)
    {
        this->updateBottom();
        tiles.append(this->graphicsBottom);
    }
    return tiles;
}

/*------------------PRIVATE-------------------*/

SettingItem::COLOR_BRICK *DiagramWall::indexColor(int indexRow, int indexCol, SettingColor::COLOR_BRICK_TYPE type)
{
    if(indexRow % 2 == 0)
    {
        if(indexCol % 2 ==0)
             return this->settingItem->colorBrick(type,this->nameColorPazzle1);
        else return this->settingItem->colorBrick(type,this->nameColorPazzle2);
    }
    else
    {
        if(indexCol % 2 ==0)
            return this->settingItem->colorBrick(type,this->nameColorPazzle2);
        else return this->settingItem->colorBrick(type,this->nameColorPazzle1);
    }
    return NULL;
}

void DiagramWall::clearTileBricks()
{
    if(this->graphicBricks.isEmpty())
        return;
    foreach(QGraphicsRectItem *item,this->graphicBricks)
        if(item!=NULL)
            delete item;
    this->graphicBricks.clear();
}

QGraphicsRectItem * DiagramWall::createItem(int width,int height)
{
    QGraphicsRectItem *item=new QGraphicsRectItem();
    item->setBrush(QBrush(Qt::white));
    item->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    item->setRect(0,0,width,height);
    return item;
}

void DiagramWall::updateBricks()
{
    this->clearTileBricks();
    Calculate calc(this->settingItem);
    if(calc.rowBrickBigWall(this->height)==0 || calc.colBrickBigWall(this->width)==0)
        return;
    int offsetX=this->pos_x;
    int offsetY=this->pos_y-this->sizeTileBottom.height()-this->sizeTileBrick.height();
    SettingItem::COLOR_BRICK *color=NULL;
    if(calc.isBrickRD(this->width))
    {
        qDebug()<<"row:"<<calc.rowBrickBigWall(this->height)<<" col:"<<calc.colBrickBigWall(this->width);
        for(int i=0;i<calc.rowBrickBigWall(this->height);i++)
        {
            for(int j=0;j<calc.colBrickBigWall(this->width);j++)
            {
                this->graphicBricks.append(this->createItem(this->sizeTileBrick.width(),this->sizeTileBrick.height()));
                if(this->pazzle)
                {
                    if(calc.colBrickBigWall(this->width)%2==0)
                         color=this->indexColor(i,j,SettingItem::COLOR_BRICK_WALL_BIG);
                    else color=this->indexColor(0,j,SettingItem::COLOR_BRICK_WALL_BIG);
                }
                else color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_BIG,
                                                         this->colorsBricks.at(i));
                if(color!=NULL)
                    this->graphicBricks.last()->setBrush(QBrush(color->image1.scaled(this->sizeTileBrick.width(),
                                                                                    this->sizeTileBrick.height())));
                this->graphicBricks.last()->setPos(offsetX,offsetY);
                offsetX=(i+1)%2==0?offsetX-this->sizeTileBrick.width():offsetX+this->sizeTileBrick.width();
            }
            this->graphicBricks.append(this->createItem(this->sizeTileBrick.width()/2,this->sizeTileBrick.height()));
            if(this->pazzle)
            {
                if(calc.colBrickBigWall(this->width)%2 ==0)
                     color=this->indexColor(i,0,SettingItem::COLOR_BRICK_WALL_SMALL);
                else color=this->indexColor(0,1,SettingItem::COLOR_BRICK_WALL_SMALL);
            }
            else color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_SMALL,
                                                     this->colorsBricks.at(i));
            if(color!=NULL)
                this->graphicBricks.last()->setBrush(QBrush(color->image1.scaled(this->sizeTileBrick.width()/2,
                                                                                this->sizeTileBrick.height())));
            offsetX=(i+1)%2==0?offsetX+this->sizeTileBrick.width()/2:offsetX;
            this->graphicBricks.last()->setPos(offsetX,offsetY);
            offsetX=(i+1)%2>0?offsetX-this->sizeTileBrick.width()/2:offsetX;
            offsetY-=this->sizeTileBrick.height();
        }
    }else{
        for(int i=0;i<calc.rowBrickBigWall(this->height);i++)
        {
            if(i % 2 ==0)
            {
                for(int j=0;j<calc.colBrickBigWall(this->width);j++)
                {
                    this->graphicBricks.append(this->createItem(this->sizeTileBrick.width(),
                                                                this->sizeTileBrick.height()));

                    this->graphicBricks.last()->setPos(offsetX,offsetY);
                    if(this->pazzle)
                         color=this->indexColor(i,j,SettingItem::COLOR_BRICK_WALL_BIG);
                    else color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_BIG,
                                                             this->colorsBricks.at(i));
                    if(color!=NULL)
                        this->graphicBricks.last()->setBrush(QBrush(color->image1.scaled(this->sizeTileBrick.width(),
                                                                                        this->sizeTileBrick.height())));
                    offsetX+=this->sizeTileBrick.width();
                }
            }else{
                offsetX-=this->sizeTileBrick.width()/2;
                this->graphicBricks.append(this->createItem(this->sizeTileBrick.width()/2,
                                                            this->sizeTileBrick.height()));
                this->graphicBricks.last()->setPos(offsetX,offsetY);
                if(this->pazzle)
                     color=this->indexColor(i,calc.colBrickBigWall(this->width),SettingItem::COLOR_BRICK_WALL_SMALL);
                else color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_SMALL,
                                                         this->colorsBricks.at(i));
                if(color!=NULL)
                    this->graphicBricks.last()->setBrush(QBrush(color->image1.scaled(this->sizeTileBrick.width()/2,
                                                                                    this->sizeTileBrick.height())));
                offsetX-=this->sizeTileBrick.width();
                for(int j=0;j<calc.colBrickBigWall(this->width)-1;j++)
                {
                    this->graphicBricks.append(this->createItem(this->sizeTileBrick.width(),
                                                                this->sizeTileBrick.height()));

                    this->graphicBricks.last()->setPos(offsetX,offsetY);
                    if(this->pazzle)
                         color=this->indexColor(i,j,SettingItem::COLOR_BRICK_WALL_BIG);
                    else color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_BIG,
                                                             this->colorsBricks.at(i));
                    if(color!=NULL)
                        this->graphicBricks.last()->setBrush(QBrush(color->image1.scaled(this->sizeTileBrick.width(),
                                                                                        this->sizeTileBrick.height())));
                    offsetX-=this->sizeTileBrick.width();
                }
                offsetX+=this->sizeTileBrick.width()/2;
                this->graphicBricks.append(this->createItem(this->sizeTileBrick.width()/2,
                                                            this->sizeTileBrick.height()));
                this->graphicBricks.last()->setPos(offsetX,offsetY);
                if(this->pazzle)
                     color=this->indexColor(i-1,calc.colBrickBigWall(this->width),SettingItem::COLOR_BRICK_WALL_SMALL);
                else color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_SMALL,
                                                         this->colorsBricks.at(i));
                if(color!=NULL)
                    this->graphicBricks.last()->setBrush(QBrush(color->image1.scaled(this->sizeTileBrick.width()/2,
                                                                                    this->sizeTileBrick.height())));
            }
            offsetY-=this->sizeTileBrick.height();
        }
    }
}

void DiagramWall::updateTops()
{
    Calculate calc(this->settingItem);
    int offsetX=this->pos_x;
    int offsetY=this->pos_y-(this->sizeTileBottom.height()+calc.rowBrickBigWall(this->height)*
                             this->sizeTileBrick.height()+this->sizeTileTop.height());
    this->graphicsTops->setPos(offsetX,offsetY);
    int width=calc.colBrickBigWall(this->width)*this->sizeTileBrick.width();
    if(calc.isBrickRD(this->width))
        width+=this->sizeTileBrick.width()/2;
    this->graphicsTops->setRect(0,0,width,this->sizeTileTop.height());
}

void DiagramWall::updateBottom()
{
    Calculate calc(this->settingItem);
    int offsetX=this->pos_x;
    int offsetY=this->pos_y-this->sizeTileBottom.height();
    this->graphicsBottom->setPos(offsetX,offsetY);
    int width=calc.colBrickBigWall(this->width)*this->sizeTileBrick.width();
    if(calc.isBrickRD(this->width))
        width+=this->sizeTileBrick.width()/2;
    this->graphicsBottom->setRect(0,0,width,this->sizeTileBottom.height());
    QList<SettingItem::COLOR_BRICK*> color=this->settingItem->colorBrick(SettingItem::COLOR_BRICK_WALL_BOTTOM);
    if(!color.isEmpty())
        this->graphicsBottom->setBrush(QBrush(color.first()->image1.scaled(width,
                                                                           this->sizeTileBottom.height())));
}
