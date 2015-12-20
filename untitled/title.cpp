#include "title.h"
#include "QDebug"

Title::Title()
{
    this->labelRight=NULL;
    this->lableTop=NULL;
    this->pillar=NULL;
    this->labelPillar1=NULL;
    this->labelPillar2=NULL;
    this->wall=NULL;
    this->labelWall1=NULL;
    this->labelWall2=NULL;
}

void Title::setDiagramScene(QGraphicsScene *scene)
{
    this->scene=scene;
}

void Title::show()
{
    this->lableTop=new QGraphicsTextItem(QString::fromLocal8Bit("Схема укладки блоков"));
    this->lableTop->setFont(QFont("Times", 18, QFont::Bold));
    this->labelRight=new QGraphicsTextItem(QString::fromLocal8Bit("Условные обозначения:"));
    this->labelRight->setFont(QFont("Times", 16, QFont::Bold));
    this->labelPillar1=new QGraphicsTextItem(QString::fromLocal8Bit("1. Брик угловой"));
    this->labelPillar1->setFont(QFont("Times", 12));
    this->labelPillar2=new QGraphicsTextItem(QString::fromLocal8Bit("2. Брик угловой примыкание"));
    this->labelPillar2->setFont(this->labelPillar1->font());
    this->labelWall1=new QGraphicsTextItem(QString::fromLocal8Bit("3. Брик рядовой"));
    this->labelWall1->setFont(this->labelPillar1->font());
    this->labelWall2=new QGraphicsTextItem(QString::fromLocal8Bit("4. Брик доборный"));
    this->labelWall2->setFont(this->labelPillar1->font());
    this->pillar=new GraphicsPillarItem();
    this->pillar->setEnabledBackUp(false);
    this->pillar->setText("1|2");
    this->wall=new GraphicsWallItem();
    this->wall->setText("3|4");
    QRectF boundingRectScene=this->scene->itemsBoundingRect();
    this->lableTop->setPos(boundingRectScene.x()+boundingRectScene.width()/2-this->lableTop->boundingRect().width()/2,
                           10);
    this->labelRight->setPos(boundingRectScene.x()+boundingRectScene.width()+50,boundingRectScene.y());
    this->pillar->setPos(this->labelRight->pos().x()+5,
                         this->labelRight->y()+this->labelRight->boundingRect().height()+30);
    this->labelPillar1->setPos(this->labelRight->pos().x(),
                               this->pillar->y()+this->pillar->boundingRect().height());
    this->labelPillar2->setPos(this->labelRight->pos().x(),
                               this->labelPillar1->y()+this->labelPillar1->boundingRect().height());
    this->wall->setLinePoint(QPointF(this->labelRight->pos().x()+5,
                        this->labelPillar2->y()+this->labelPillar2->boundingRect().height()+30),
                        QPointF(this->labelRight->pos().x()+this->labelPillar2->boundingRect().width(),
                        this->labelPillar2->y()+this->labelPillar2->boundingRect().height()+30));
    this->labelWall1->setPos(this->labelRight->pos().x(),
                             this->wall->line().y1()+this->wall->boundingRect().height()+20);
    this->labelWall2->setPos(this->labelRight->pos().x(),
                             this->labelWall1->pos().y()+this->labelWall1->boundingRect().height());

    this->scene->addItem(this->lableTop);
    this->scene->addItem(this->labelRight);
    this->scene->addItem(this->pillar);
    this->scene->addItem(this->labelPillar1);
    this->scene->addItem(this->labelPillar2);
    this->scene->addItem(this->wall);
    this->scene->addItem(this->labelWall1);
    this->scene->addItem(this->labelWall2);
}

void Title::hide()
{
    qDebug()<<"-------------START TITLE:HIDE-------------------";
    if(this->lableTop!=NULL)
    {
        this->scene->removeItem(this->lableTop);
        //delete this->lableTop;
        this->lableTop=NULL;
    }
    if(this->labelRight!=NULL)
    {
        this->scene->removeItem(this->labelRight);
        //delete this->labelRight;
        this->labelRight=NULL;
    }
    if(this->pillar!=NULL)
    {
        this->scene->removeItem(this->pillar);
        //delete this->pillar;
        this->pillar=NULL;
    }
    if(this->labelPillar1!=NULL)
    {
        this->scene->removeItem(this->labelPillar1);
       // delete this->labelPillar1;
        this->labelPillar1=NULL;
    }
    if(this->labelPillar2!=NULL)
    {
        this->scene->removeItem(this->labelPillar2);
        //delete this->labelPillar2;
        this->labelPillar2=NULL;
    }
    if(this->wall!=NULL)
    {
        this->scene->removeItem(this->wall);
        //delete this->wall;
        this->wall=NULL;
    }
    if(this->labelWall1!=NULL)
    {
        this->scene->removeItem(this->labelWall1);
       // delete this->labelWall1;
        this->labelWall1=NULL;
    }
    if(this->labelWall2!=NULL)
    {
        this->scene->removeItem(this->labelWall2);
        //delete this->labelWall2;
        this->labelWall2=NULL;
    }
    qDebug()<<"-------------FINISH TITLE:HIDE-------------------";
}
