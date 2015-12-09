#include "diagrampillar.h"
#include "QDebug"

DiagramPillar::DiagramPillar()
{
    this->graphicTileTop=NULL;
    this->graphicTileBottom=NULL;
    this->settingItem=NULL;
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
//        qDebug()<<"count object list:"<<this->graphicsTileBricks.count();
//        qDebug()<<"count row:"<<this->row();
        for(int i=this->graphicsTileBricks.count()-1;i>=(this->row()*2);i--)
        {
//            qDebug()<<"delete object i:"<<i;
            delete this->graphicsTileBricks.last();
            this->graphicsTileBricks.removeLast();
        }
        return;
    }
    for(int i=(this->graphicsTileBricks.count()/2);i<this->row();i++)
    {
        this->graphicsTileBricks.append(this->createItem(this->tileBrickWidth,this->tileBrickHeight));
        this->graphicsTileBricks.append(this->createItem(this->tileBrickWidth/2,this->tileBrickHeight));
    }
}

void DiagramPillar::setInsert(SIDE side, int insert)
{
    this->insert[(int)side]=insert;
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

void DiagramPillar::showSide(SIDE side)
{
    this->side=side;
}

QList<QGraphicsRectItem*> DiagramPillar::graphics()
{
    QList<QGraphicsRectItem*> graphicItem;
    if(this->graphicTileBottom!=NULL)
    {
        this->setPosGraphicTileBottom(this->x,this->y);
        graphicItem.append(this->graphicTileBottom);
    }
    if(!this->graphicsTileBricks.isEmpty())
    {
        this->setPosGraphicTileBricks(this->x,this->y);
        graphicItem.append(this->graphicsTileBricks);
    }
    if(this->graphicTileTop!=NULL)
    {
        this->setPosGraphicTileTop(this->x,this->y);
        graphicItem.append(this->graphicTileTop);
    }
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
    for(int i=0;i<this->row()*2;i+=2)
    {
        y=y-this->tileBrickHeight;
        if(i % 2 == 0)
        {
            this->graphicsTileBricks.at(i)->setPos(x,y);
            this->graphicsTileBricks.at(i+1)->setPos(x+this->tileBrickWidth,y);
        }else{
            this->graphicsTileBricks.at(i)->setPos(x+this->tileBrickWidth/2,y);
            this->graphicsTileBricks.at(i+1)->setPos(x,y);
        }
    }
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
