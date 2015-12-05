#include "diagramviewwall.h"
#include "QDebug"
DiagramViewWall::DiagramViewWall(QWidget *parent):QGraphicsView(parent)
{
    this->GraphicsSceneWall=new QGraphicsScene(QRectF(0,0,600,400),parent);
    this->setScene(this->GraphicsSceneWall);
    this->row=0;
    this->widthWall=10;
    this->heightWall=0;
    this->topWall=0;
    this->color1=QColor(Qt::white);
    this->color2=QColor(Qt::white);
    this->pazzle=false;
    this->d1=false;
    this->d2=false;
    this->d3=false;
}

void DiagramViewWall::setGraphicsWall(int width, int height, bool topWall)
{
    this->widthWall=width;
    this->heightWall=height;
    this->topWall=topWall;
    this->rendering();
}

void DiagramViewWall::setWidthWall(int width)
{
    this->widthWall=width;
    this->rendering();
}

void DiagramViewWall::setHeightWall(int height)
{
    this->heightWall=height;
    this->rendering();
}

void DiagramViewWall::setSetting(SettingItem *itemSetting)
{
    this->calc=new Calculate(itemSetting);
    this->heightBrick=itemSetting->heightBrickAngle;
    this->widthBrickR=itemSetting->maxWidthBrickR;
    this->widthBrickRD=itemSetting->minWidthBrickR;
}

void DiagramViewWall::setEnableTopWall(bool enable, QColor color)
{
    this->topWall=enable;
    this->colorTop=color;
    this->rendering();
}

void DiagramViewWall::setColorRowWall(int number, QColor color)
{
    this->colorRow.removeAt(number-1);
    this->colorRow.insert(number-1,color);
    this->rendering();
}

void DiagramViewWall::setColorAllRawWall(QColor colorAllRow)
{
    this->colorRow.clear();
    for(int i=0;i<this->row;i++)
        this->colorRow.append(colorAllRow);
    this->rendering();
}

void DiagramViewWall::setEnableColorPazzle(bool enable, QColor color1, QColor color2)
{
    this->pazzle=enable;
    this->color1=color1;
    this->color2=color2;
    this->rendering();
}

QColor DiagramViewWall::getColorRow(int numberRow)
{
    return this->colorRow.at(numberRow);
}

QList<QColor> DiagramViewWall::getColorAllRow()
{
    return this->colorRow;
}

int DiagramViewWall::countRow()
{
    return this->row;
}

int DiagramViewWall::countColorRow()
{
    return this->colorRow.count();
}

void DiagramViewWall::setEnableDecoreit(bool d1, QColor colorD1, bool d2, QColor colorD2, bool d3, QColor colorD3)
{
    this->d1=d1;
    this->colorD1=colorD1;
    this->d2=d2;
    this->colorD2=colorD2;
    this->d3=d3;
    this->colorD3=colorD3;
    this->rendering();
}

void DiagramViewWall::clearScene()
{
    foreach(QGraphicsItem *itemGraphics,this->GraphicsSceneWall->items())
        delete itemGraphics;
    this->GraphicsSceneWall->clear();
}

void DiagramViewWall::createWall()
{
    int y=this->GraphicsSceneWall->height()-50;
    int x=90;
    if(this->calc->isBrickRD(this->widthWall))
    {
        for(int i=0;i<this->calc->rowBrickBigWall(this->heightWall);i++)
        {
            for(int j=0;j<this->calc->colBrickBigWall(this->widthWall);j++)
            {
                QGraphicsRectItem *itemBrickBig = new QGraphicsRectItem();
                itemBrickBig->setBrush(QBrush(this->colorRow.at(i)));
                itemBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                itemBrickBig->setRect(x,y,30,10);
                this->GraphicsSceneWall->addItem(itemBrickBig);
                x=(i+1)%2==0?x-30:x+30;
            }
            x=(i+1)%2==0?x+15:x;
            QGraphicsRectItem *itemBrickSmall=new QGraphicsRectItem();
            itemBrickSmall->setBrush(QBrush(this->colorRow.at(i)));
            itemBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            itemBrickSmall->setRect(x,y,15,10);
            this->GraphicsSceneWall->addItem(itemBrickSmall);
            x=(i+1)%2>0?x-15:x;
            QGraphicsTextItem *itemText=new QGraphicsTextItem(QString::number(i+1));
            itemText->setPos(30,y-5);
            this->GraphicsSceneWall->addItem(itemText);
            y-=10;
        }
    }else{
        for(int i=0;i<this->calc->rowBrickBigWall(this->heightWall);i++)
        {
            if((i+1)%2>0)
            {
                for(int j=0;j<this->calc->colBrickBigWall(this->widthWall);j++)
                {
                    QGraphicsRectItem *itemBrickBig = new QGraphicsRectItem();
                    itemBrickBig->setBrush(QBrush(this->colorRow.at(i)));
                    itemBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                    itemBrickBig->setRect(x,y,30,10);
                    this->GraphicsSceneWall->addItem(itemBrickBig);
                    x+=30;
                }
            }else{
                x-=15;
                QGraphicsRectItem *itemBrickSmall=new QGraphicsRectItem();
                itemBrickSmall->setBrush(QBrush(this->colorRow.at(i)));
                itemBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                itemBrickSmall->setRect(x,y,15,10);
                this->GraphicsSceneWall->addItem(itemBrickSmall);
                x-=30;
                for(int j=0;j<this->calc->colBrickBigWall(this->widthWall)-1;j++)
                {
                    QGraphicsRectItem *itemBrickBig = new QGraphicsRectItem();
                    itemBrickBig->setBrush(QBrush(this->colorRow.at(i)));
                    itemBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                    itemBrickBig->setRect(x,y,30,10);
                    this->GraphicsSceneWall->addItem(itemBrickBig);
                    x-=30;
                }
                x+=15;
                itemBrickSmall=new QGraphicsRectItem();
                itemBrickSmall->setBrush(QBrush(this->colorRow.at(i)));
                itemBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                itemBrickSmall->setRect(x,y,15,10);
                this->GraphicsSceneWall->addItem(itemBrickSmall);
            }
            QGraphicsTextItem *itemText=new QGraphicsTextItem(QString::number(i+1));
            itemText->setPos(30,y-5);
            this->GraphicsSceneWall->addItem(itemText);
            y-=10;
        }
    }
    if(this->topWall)
    {
        y+=5;
        int widthTopWall=this->calc->isBrickRD(this->widthWall)==true?(this->calc->colBrickBigWall(this->widthWall)*30)+15:
                                                                      this->calc->colBrickBigWall(this->widthWall)*30;
        QGraphicsRectItem *topGraphicsWall=new QGraphicsRectItem();
        topGraphicsWall->setBrush(QBrush(this->colorTop));
        topGraphicsWall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        topGraphicsWall->setRect(90,y,widthTopWall,5);
        this->GraphicsSceneWall->addItem(topGraphicsWall);
    }
}

void DiagramViewWall::createPazzleWall()
{
    int y=this->GraphicsSceneWall->height()-50;
    int x=90;
    if(this->calc->isBrickRD(this->widthWall))
    {
        for(int i=0;i<this->calc->rowBrickBigWall(this->heightWall);i++)
        {
            for(int j=0;j<this->calc->colBrickBigWall(this->widthWall);j++)
            {
                QGraphicsRectItem *itemBrickBig = new QGraphicsRectItem();
                if(this->calc->colBrickBigWall(this->widthWall)%2==0)
                    itemBrickBig->setBrush(QBrush((j+1)%2==0?this->color1:this->color2));
                else
                    itemBrickBig->setBrush(QBrush((j+1)%2==0?this->color2:this->color1));
                itemBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                itemBrickBig->setRect(x,y,30,10);
                this->GraphicsSceneWall->addItem(itemBrickBig);
                x=(i+1)%2==0?x-30:x+30;
            }
            x=(i+1)%2==0?x+15:x;
            QGraphicsRectItem *itemBrickSmall=new QGraphicsRectItem();
            itemBrickSmall->setBrush(QBrush(this->color2));
            if(this->calc->colBrickBigWall(this->widthWall)%2==0 &&(i+1)%2>0)
                itemBrickSmall->setBrush(QBrush(this->color1));
            itemBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            itemBrickSmall->setRect(x,y,15,10);
            this->GraphicsSceneWall->addItem(itemBrickSmall);
            x=(i+1)%2>0?x-15:x;
            QGraphicsTextItem *itemText=new QGraphicsTextItem(QString::number(i+1));
            itemText->setPos(30,y-5);
            this->GraphicsSceneWall->addItem(itemText);
            y-=10;
        }
    }else{
        for(int i=0;i<this->calc->rowBrickBigWall(this->heightWall);i++)
        {
            if((i+1)%2>0)
            {
                for(int j=0;j<this->calc->colBrickBigWall(this->widthWall);j++)
                {
                    QGraphicsRectItem *itemBrickBig = new QGraphicsRectItem();
                    itemBrickBig->setBrush(QBrush((j+1)%2>0?this->color1:this->color2));
                    itemBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                    itemBrickBig->setRect(x,y,30,10);
                    this->GraphicsSceneWall->addItem(itemBrickBig);
                    x+=30;
                }
            }else{
                x-=15;
                QGraphicsRectItem *itemBrickSmall=new QGraphicsRectItem();
                itemBrickSmall->setBrush(QBrush(this->calc->colBrickBigWall(this->widthWall)%2==0?
                                                    this->color2:this->color1));
                itemBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                itemBrickSmall->setRect(x,y,15,10);
                this->GraphicsSceneWall->addItem(itemBrickSmall);
                x-=30;
                for(int j=0;j<this->calc->colBrickBigWall(this->widthWall)-1;j++)
                {
                    QGraphicsRectItem *itemBrickBig = new QGraphicsRectItem();
                    if(this->calc->colBrickBigWall(this->widthWall)%2==0)
                        itemBrickBig->setBrush(QBrush((j+1)%2==0?this->color2:this->color1));
                    else
                        itemBrickBig->setBrush(QBrush((j+1)%2==0?this->color1:this->color2));
                    itemBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                    itemBrickBig->setRect(x,y,30,10);
                    this->GraphicsSceneWall->addItem(itemBrickBig);
                    x-=30;
                }
                x+=15;
                itemBrickSmall=new QGraphicsRectItem();
                itemBrickSmall->setBrush(QBrush(this->color2));
                itemBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                itemBrickSmall->setRect(x,y,15,10);
                this->GraphicsSceneWall->addItem(itemBrickSmall);
            }
            QGraphicsTextItem *itemText=new QGraphicsTextItem(QString::number(i+1));
            itemText->setPos(30,y-5);
            this->GraphicsSceneWall->addItem(itemText);
            y-=10;
        }
    }
    if(this->topWall)
    {
        y+=5;
        int widthTopWall=this->calc->isBrickRD(this->widthWall)==true?(this->calc->colBrickBigWall(this->widthWall)*30)+15:
                                                                      this->calc->colBrickBigWall(this->widthWall)*30;
        QGraphicsRectItem *topGraphicsWall=new QGraphicsRectItem();
        topGraphicsWall->setBrush(QBrush(this->colorTop));
        topGraphicsWall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        topGraphicsWall->setRect(90,y,widthTopWall,5);
        this->GraphicsSceneWall->addItem(topGraphicsWall);
    }
}

void DiagramViewWall::setHeightPillar(int height)
{
    this->heightPillar=height;
}

void DiagramViewWall::setTopPillar(bool top, QString color)
{
    this->topPillar=top;
    if(this->topPillar)
        this->colorTopPillar=color;
    else this->colorTopPillar=QString();
}

void DiagramViewWall::setPazzlePillar(bool pazzle, QString color1, QString color2)
{
    this->pazzlePillar=pazzle;
    if(this->pazzlePillar)
    {
        this->colorPazzle1Pillar=color1;
        this->colorPazzle2Pillar=color2;
    }else{
        this->colorPazzle1Pillar=QString();
        this->colorPazzle2Pillar=QString();
    }
}

void DiagramViewWall::setColorListPillar(QList<QString> colorList)
{
    if(!colorList.isEmpty())
        this->colorList=colorList;
}

void DiagramViewWall::createPillar()
{
    /*int y=this->GraphicsSceneWall->height()-50;
    int heightop=10;
    if(this->topWall)
        heightop=5;
    int heightD=this->heightPillar-this->heightWall;
    int dy=y-this->heightWall+heightop-heightD;
    int x=90;
    int countD=qRound(this->widthWall/10);
    if(d1 && heightD!=0)
    {
        QPolygonF polygon;
        polygon<<QPointF(5,0)<<QPointF(0,5)<<QPointF(0,heightD)<<QPointF(10,heightD)<<QPointF(10,5);
        for(int i=0;i<countD;i++)
        {
            QGraphicsPolygonItem *itemGraphics=new QGraphicsPolygonItem(polygon);
            itemGraphics->setBrush(QBrush(this->colorD1));
            itemGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            itemGraphics->setPos(x,dy);
            this->GraphicsSceneWall->addItem(itemGraphics);
            x+=10;
        }
    }
    if(d2 && heightD!=0)
    {
        QGraphicsRectItem *left=new QGraphicsRectItem();
        left->setBrush(QBrush(this->colorD2));
        left->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        left->setRect(x,dy,10,heightD);
        this->GraphicsSceneWall->addItem(left);
        x+=10;
        QGraphicsLineItem *topLine=new QGraphicsLineItem();
        topLine->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        topLine->setLine(x,dy+70,x+this->widthWall,dy+70);
        this->GraphicsSceneWall->addItem(topLine);
        QGraphicsLineItem *centreLine=new QGraphicsLineItem();
        centreLine->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        centreLine->setLine(x,dy+40,x+this->widthWall,dy+40);
        this->GraphicsSceneWall->addItem(centreLine);
        QGraphicsLineItem *bottomLine=new QGraphicsLineItem();
        bottomLine->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        bottomLine->setLine(x,dy+10,x+this->widthWall,dy+10);
        this->GraphicsSceneWall->addItem(bottomLine);
        QPolygonF polygon;
        polygon<<QPointF(5,0)<<QPointF(0,5)<<QPointF(2.5,5)<<QPointF(2.5,heightD)<<QPointF(7.5,heightD)<<QPointF(7.5,5)
               <<QPointF(10,5);
        for(int i=0;i<countD;i++)
        {
            QGraphicsPolygonItem *itemGraphics=new QGraphicsPolygonItem(polygon);
            itemGraphics->setBrush(QBrush(this->colorD2));
            itemGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            itemGraphics->setPos(x,dy);
            this->GraphicsSceneWall->addItem(itemGraphics);
            x+=10;
        }
    }
    if(d3 && heightD!=0)
    {
        for(int i=0;i<countD;i++)
        {
            QGraphicsRectItem *itemGraphics=new QGraphicsRectItem();
            itemGraphics->setBrush(QBrush(this->colorD3));
            itemGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            itemGraphics->setRect(x,dy,10,heightD);
            this->GraphicsSceneWall->addItem(itemGraphics);
            x+=10;
        }
    }
    int Row=this->calc->getCountBrickAngle(this->heightPillar);
    for(int i=0;i<Row;i++)
    {
        QGraphicsRectItem *itemGraphicsBrickSmall=new QGraphicsRectItem();
        QGraphicsRectItem *itemGraphicsBrickBig=new QGraphicsRectItem();
        itemGraphicsBrickSmall->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        itemGraphicsBrickBig->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        if(i % 2 ==0)
        {
            itemGraphicsBrickSmall->setRect(50,y,15,10);
            itemGraphicsBrickBig->setRect(65,y,25,10);
        }else{
            itemGraphicsBrickBig->setRect(50,y,25,10);
            itemGraphicsBrickSmall->setRect(75,y,15,10);
        }
        if(!this->pazzlePillar)
        {
            if(this->colorList.isEmpty())
            {
                itemGraphicsBrickBig->setBrush(QBrush(Qt::white));
                itemGraphicsBrickSmall->setBrush(QBrush(Qt::white));
            }
            else
            {
                itemGraphicsBrickBig->setBrush(QBrush(this->colorList.at(i).color));
                itemGraphicsBrickSmall->setBrush(QBrush(this->colorList.at(i).color));
            }
        }else{
            if(i % 2 == 0)
            {
                itemGraphicsBrickSmall->setBrush(QBrush(this->colorPazzle1Pillar.color));
                itemGraphicsBrickBig->setBrush(QBrush(this->colorPazzle2Pillar.color));
            }
            else{
                itemGraphicsBrickSmall->setBrush(QBrush(this->colorPazzle2Pillar.color));
                itemGraphicsBrickBig->setBrush(QBrush(this->colorPazzle1Pillar.color));
            }
        }
        this->GraphicsSceneWall->addItem(itemGraphicsBrickSmall);
        this->GraphicsSceneWall->addItem(itemGraphicsBrickBig);
        y-=10;
    }
    if(this->topPillar)
    {
        y-=15;
        QPolygonF polygon;
        polygon<<QPointF(20.0f,0.0f)<<QPointF(0,20)<<QPointF(40,20);
        QGraphicsPolygonItem *itemTopGraphics=new QGraphicsPolygonItem(polygon);
        itemTopGraphics->setBrush(QBrush(this->colorTopPillar.color));
        itemTopGraphics->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        itemTopGraphics->setPos(50,y+5);
        this->GraphicsSceneWall->addItem(itemTopGraphics);
    }**/
}

void DiagramViewWall::rendering()
{
    this->clearScene();
    if(this->widthWall==0 ||this->heightWall<this->heightBrick || this->heightWall==0)
    {
        this->colorRow.clear();
        return;
    }
    this->row=this->calc->rowBrickBigWall(this->heightWall);
    if(!this->colorRow.isEmpty())
        for(int i=0;i<this->row;i++)
            this->colorRow.append(QColor(Qt::white));
    if(this->colorRow.count()-1<this->row)
    {
        for(int i=this->colorRow.count()-1;i<this->row;i++)
            this->colorRow.append(QColor(Qt::white));
    }
    else for(int i=this->colorRow.count()-1;i>this->row;i--)
            this->colorRow.removeAt(i);
    if(this->widthWall<550)
        this->GraphicsSceneWall->setSceneRect(0,0,600,400);
    else this->GraphicsSceneWall->setSceneRect(0,0,this->widthWall+100,400);
    if(this->heightWall<400)
        this->GraphicsSceneWall->setSceneRect(0,0,this->GraphicsSceneWall->width(),400);
    else this->GraphicsSceneWall->setSceneRect(0,0,this->GraphicsSceneWall->width(),this->heightWall+50);
    this->createPillar();
    if(this->pazzle)
        this->createPazzleWall();
    else this->createWall();
}
