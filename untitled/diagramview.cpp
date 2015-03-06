#include "diagramview.h"
///////////////////////////////////
#include <QDebug>
//////////////////////////////////



DiagramView::DiagramView(QWidget *parent):QGraphicsView(parent)
{

    this->setMouseTracking(true);
    this->pDiagramScene=new QGraphicsScene(QRectF(0,0,8000,8000),parent);
    this->setScene(this->pDiagramScene);
    this->currentIdItem=1;
    this->lineWall=NULL;
    this->lineFilling=NULL;
    this->CreateMenuItem();
    this->pDiagramScene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
    this->pillarBottom=false;
    this->Fundament=false;
    this->Rigel=false;
    this->mousePrees=false;
    this->centerOn(0,0);
}

DiagramView::~DiagramView()
{
    //this->itemScene.RemoveAll();
}
/*-----------------------------------------private------------------------------------------*/

void DiagramView::CreateMenuItem()
{
    this->Rotate_45Action=new QAction(QString::fromLocal8Bit("Повернуть на 45 градусов"),this);
    connect(this->Rotate_45Action,SIGNAL(triggered()),this,SLOT(RotateItem_45()));
    this->Rotate_90Action=new QAction(QString::fromLocal8Bit("Повернуть на 90 градусов"),this);
    connect(this->Rotate_90Action,SIGNAL(triggered()),this,SLOT(RotateItem_90()));
    this->Rotate_180Action=new QAction(QString::fromLocal8Bit("Повернуть на 180 градусов"),this);
    connect(this->Rotate_180Action,SIGNAL(triggered()),this,SLOT(RotateItem_180()));
    this->DeleteItem=new QAction(QString::fromLocal8Bit("Удалить"),this);
    connect(this->DeleteItem,SIGNAL(triggered()),this,SLOT(Delete_Item()));
    this->MenuItem=new QMenu(this);
    this->MenuItem->addAction(this->Rotate_45Action);
    this->MenuItem->addAction(this->Rotate_90Action);
    this->MenuItem->addAction(this->Rotate_180Action);
    this->MenuItem->addSeparator();
    this->MenuItem->addAction(this->DeleteItem);
}

QGraphicsItem *DiagramView::itemToScene(TYPEITEM typeItem, QPointF point)
{
    QList<QGraphicsItem*> listItem=this->pDiagramScene->items(point);
    if(!listItem.isEmpty())
    {
        foreach(QGraphicsItem *item,listItem)
            switch(typeItem)
            {
                case ITEM_PILLAR:{
                    if(item->type()==GraphicsPillarItem::Type)
                        return item;
                }
                default:break;
            }
    }
    return NULL;
}

void DiagramView::AppendItem(TYPEITEM typeItem, QPointF point)
{
    switch(typeItem)
    {
        case ITEM_PILLAR:{
            GraphicsPillarItem *PillarItem=new GraphicsPillarItem(this->MenuItem,0,this->pDiagramScene);
            PillarItem->setPos(point);
            this->pDiagramScene->addItem(PillarItem);
            return;
        }
        case ITEM_WALL:{
            GraphicsWallItem *wall=new GraphicsWallItem(this->MenuItem);
            QGraphicsItem *item1=this->itemToScene(ITEM_PILLAR,this->lineWall->line().p1());
            QGraphicsItem *item2=this->itemToScene(ITEM_PILLAR,this->lineWall->line().p2());
            if(item1!=NULL && item2!=NULL)
            {
                GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(item1);
                GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(item2);
                wall->setLinePoint(pillar1->centre(),pillar2->centre());
                pillar1->addWall(wall,true);
                pillar2->addWall(wall,false);
                this->pDiagramScene->addItem(wall);
            }
            this->pDiagramScene->removeItem(this->lineWall);
            delete this->lineWall;
            this->lineWall=NULL;
            return;
        }
        case ITEM_GATE_A:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            group->createGroup(GroupItem::ITEM_GATE1,this->MenuItem,this->pDiagramScene);
            group->setPos(point);
            this->listGroup.append(group);
            return;
        }
        case ITEM_GATE_B:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            group->createGroup(GroupItem::ITEM_GATE2,this->MenuItem,this->pDiagramScene);
            group->setPos(point);
            this->listGroup.append(group);
            return;
        }
        case ITEM_WICKET:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            group->createGroup(GroupItem::ITEM_WICKET,this->MenuItem,this->pDiagramScene);
            group->setPos(point);
            this->listGroup.append(group);
            return;
        }
        default:return;
    }
}

float DiagramView::distancePointToPoint(QPointF point1, QPointF point2)
{
    return ::sqrtf(::powf(point1.x()-point2.x(),2)+::powf(point1.y()-point2.y(),2));
}

void DiagramView::RotateItem(int Angle)
{
    foreach(GroupItem* group,this->listGroup)
        if(group->isItem(this->pDiagramScene->selectedItems().at(0)))
        {
            group->setRotate(Angle);
            break;
        }
}

QPointF DiagramView::centerItem(QGraphicsItem *itemGraphics)
{
    int x=itemGraphics->pos().x()+(itemGraphics->boundingRect().width()/2*TableAngle[0][(int)itemGraphics->rotation()/45]);
    int y=itemGraphics->pos().y()+(itemGraphics->boundingRect().height()/2*TableAngle[1][(int)itemGraphics->rotation()/45]);
    return QPointF(x,y);
}

void DiagramView::changeLine(ITEM *parentItem,QGraphicsItem *itemGraphics)
{
    foreach(CHILD *child,parentItem->child)
        if(child->resize)
        {
            GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(child->itemChild);
            if(this->distancePointToPoint(itemGraphics->pos(),wall->line().p1())<this->distancePointToPoint(itemGraphics->pos(),wall->line().p2()))
                wall->setLine(QLineF(this->centerItem(itemGraphics), wall->line().p2()));
            else
                wall->setLine(QLineF(wall->line().p1(),this->centerItem(itemGraphics)));

        }
}

//-----------------------------------SLOTS---------------------------------------------------//

void DiagramView::RotateItem_45()
{
    if(!this->pDiagramScene->selectedItems().isEmpty())
        this->RotateItem(45);
}

void DiagramView::RotateItem_90()
{
    if(!this->pDiagramScene->selectedItems().isEmpty())
        this->RotateItem(90);
}

void DiagramView::RotateItem_180()
{
    if(!this->pDiagramScene->selectedItems().isEmpty())
        this->RotateItem(180);
}

void DiagramView::Delete_Item()
{
    if(!this->pDiagramScene->selectedItems().isEmpty())
    {
        foreach(QGraphicsItem *parentItem,this->pDiagramScene->selectedItems())
        {
            if(parentItem->type()==GraphicsWicketItem::Type || parentItem->type()==GraphicsGate1Item::Type ||
               parentItem->type()==GraphicsGate2Item::Type)
                foreach(GroupItem *group,this->listGroup)
                    if(group->isItem(parentItem))
                    {
                        this->listGroup.removeAt(this->listGroup.indexOf(group));
                        delete group;
                        break;
                    }
            foreach(QGraphicsItem *childItem,parentItem->childItems())
                this->pDiagramScene->removeItem(childItem);
            this->pDiagramScene->removeItem(parentItem);
        }
    }
}

void DiagramView::setInterval(float interval, bool empty)
{
   /* if(empty || interval<this->itemSetting->maxWidthBrickR*10+350)
    {
        this->deleteFilling();
        return;
    }
    QList<QGraphicsItem*> items=this->pDiagramScene->collidingItems(this->lineFilling);
    if(items.empty())
    {
        this->deleteFilling();
        return;
    }
    QGraphicsItem *ObjectA,*ObjectB;
    ObjectA=ObjectB=NULL;
    foreach(QGraphicsItem *graphicsItem,items)
    {
        if(graphicsItem->data(1).toInt()==0)
            continue;
        if(this->itemScene.getItem(graphicsItem->data(1).toInt())->type==ITEM_PILLAR &&
           this->coliding(graphicsItem,this->lineFilling->line().p1()))
            ObjectA=graphicsItem;
        if(this->itemScene.getItem(graphicsItem->data(1).toInt())->type==ITEM_PILLAR &&
           this->coliding(graphicsItem,this->lineFilling->line().p2()))
            ObjectB=graphicsItem;
        if(ObjectA!=NULL && ObjectB!=NULL)
            break;
    }
    this->deleteFilling();
    if(ObjectA!=NULL && ObjectB!=NULL)
        this->Filling(ObjectA,ObjectB,interval);*/
}

void DiagramView::deleteFilling()
{
    this->pDiagramScene->removeItem(this->lineFilling);
    this->lineFilling=NULL;
}

bool DiagramView::coliding(QGraphicsItem *Object, QPointF point)
{
    QPointF posObject=this->centerItem(Object);
    if(((posObject.x()+Object->boundingRect().width()/2)>=point.x())&&
       ((posObject.x()-Object->boundingRect().width()/2)<=point.x())&&
       ((posObject.y()+Object->boundingRect().height()/2)>=point.y())&&
       ((posObject.y()-Object->boundingRect().height()/2)<=point.y()))
        return true;
    return false;
}

QPointF DiagramView::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

GraphicsPillarItem *DiagramView::createPillar(QPoint pointScene)
{
    GraphicsPillarItem *PillarItem=new GraphicsPillarItem(this->MenuItem);
    PillarItem->setPos(pointScene.x(),pointScene.y());
    /*PillarItem->setData(1,QVariant(this->currentIdItem));
    this->itemScene.AppendItem(this->currentIdItem,ITEM_PILLAR);
    this->pDiagramScene->addItem(PillarItem);
    PillarItem->itemGraphicsText()->setPos(pointScene.x()-30,pointScene.y());
    this->pDiagramScene->addItem(PillarItem->itemGraphicsText());
    PillarItem->itemGraphicsLine()->setLine(QLineF(PillarItem->itemGraphicsText()->pos(),PillarItem->pos()));
    this->pDiagramScene->addItem(PillarItem->itemGraphicsLine());*/
    this->currentIdItem++;
    return PillarItem;
}

GraphicsWallItem *DiagramView::createWall(QPointF pointSceneA, QPointF pointSceneB)
{
    GraphicsWallItem *w=new GraphicsWallItem(this->MenuItem);
    /*w->setLine(QLineF(pointSceneA.x(),pointSceneA.y(),pointSceneB.x(),pointSceneB.y()));
    w->setData(1,QVariant(this->currentIdItem));
    this->itemScene.AppendItem(this->currentIdItem,ITEM_WALL);
    this->itemScene.getItem(this->currentIdItem)->wall->d=0;
    this->pDiagramScene->addItem(WallItem);
    this->currentIdItem++;
    WallItem->itemGraphicsText()->setPos(WallItem->centre().x()-30,WallItem->centre().y()-30);
    this->pDiagramScene->addItem(WallItem->itemGraphicsText());
    WallItem->itemGraphicsLine()->setLine(QLineF(WallItem->itemGraphicsText()->pos(),WallItem->centre()));
    this->pDiagramScene->addItem(WallItem->itemGraphicsLine());*/
    return w;
}

void DiagramView::appendChildObject(QGraphicsItem *a, QGraphicsItem *b, QGraphicsItem *l)
{
 /*   this->itemScene.AppendChild(a->data(1).toInt(),new CHILD(l->data(1).toInt(),true,l));
    this->itemScene.AppendChild(b->data(1).toInt(),new CHILD(l->data(1).toInt(),true,l));
    this->itemScene.AppendChild(l->data(1).toInt(),new CHILD(a->data(1).toInt(),false,NULL));
    this->itemScene.AppendChild(l->data(1).toInt(),new CHILD(b->data(1).toInt(),false,NULL));*/
}

void DiagramView::changeGroup(GroupItem *g1, GroupItem g2)
{
}

void DiagramView::Filling(QGraphicsItem *a, QGraphicsItem *b,float interval)
{/*
    QPointF posA,posB,point;
    bool gate=false;
    posA=this->centerItem(a);
    posB=this->centerItem(b);
    float angle=::atan2(posA.y()-posB.y(),posA.x()-posB.x())/PI*180;
    angle=angle<0?angle+360:angle;
    int countObject=qFloor(interval/(this->itemSetting->maxWidthGirth*10+350));
    int intervalRest=interval-(this->itemSetting->maxWidthGirth*10+350)*countObject;
    float distance=a->boundingRect().width()+50;
    GraphicsPillarItem *pillar;
    GraphicsWallItem *wall;
    for(int i=0;i<countObject-1;i++)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-(distance*(i+1)),posA.y()),angle);
        pillar=this->createPillar(QPoint(point.x()-a->boundingRect().width()/2,
                                                             point.y()-a->boundingRect().height()/2));
        wall=this->createWall(this->centerItem(a),point);
        this->itemScene.getItem(wall->data(1).toInt())->wall->width=this->itemSetting->maxWidthGirth;
        this->appendChildObject(a,pillar,wall);
        a=pillar;
    }
    if(intervalRest==0)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-distance*countObject,posA.y()),angle);
        ITEM *logicItem=this->itemScene.getItem(b->data(1).toInt());
        foreach(CHILD *child,logicItem->child)
        {
            if(this->itemScene.getItem(child->idChild)->type!=ITEM_PILLAR ||
               this->itemScene.getItem(child->idChild)->type!=ITEM_WALL)
            {
                this->changeGroup(child->itemChild,point);
                gate=true;
                break;
            }
        }
        if(!gate)
            b->setPos(point.x()-b->boundingRect().width()/2,point.y()-b->boundingRect().height()/2);
        wall=this->createWall(this->centerItem(a),point);
        this->itemScene.getItem(wall->data(1).toInt())->wall->width=this->itemSetting->maxWidthGirth;
        this->appendChildObject(a,b,wall);
        return;
    }
    if(countObject!=0)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-distance*countObject,posA.y()),angle);
        pillar=this->createPillar(QPoint(point.x()-a->boundingRect().width()/2,
                                                             point.y()-a->boundingRect().height()/2));
        wall=this->createWall(this->centerItem(a),point);
        this->itemScene.getItem(wall->data(1).toInt())->wall->width=this->itemSetting->maxWidthGirth;
        this->appendChildObject(a,pillar,wall);
        a=pillar;
    }
    int grith=0;
    if(intervalRest>this->itemSetting->minWidthBrickR*10+350)
    {
        for(int i=this->itemSetting->maxWidthBrickR*10+350;i<=this->itemSetting->maxWidthGirth*10+350;i+=150)
            if(i>=intervalRest)
            {
                grith=i;
                break;
            }
    }else{
        if(intervalRest>=qFloor(this->itemSetting->minWidthBrickR/2)*10)
            grith=this->itemSetting->minWidthBrickR*10+350;
    }
    if(grith>0)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-distance*(countObject+1),posA.y()),angle);
        ITEM *logicItem=this->itemScene.getItem(b->data(1).toInt());
        foreach(CHILD *child,logicItem->child)
        {
            if(this->itemScene.getItem(child->idChild)->type!=ITEM_PILLAR ||
               this->itemScene.getItem(child->idChild)->type!=ITEM_WALL)
            {
                this->changeGroup(child->itemChild,point);
                gate=true;
                break;
            }
        }
        if(!gate)
            b->setPos(point.x()-b->boundingRect().width()/2,point.y()-b->boundingRect().height()/2);
        wall=this->createWall(this->centerItem(a),point);
        this->itemScene.getItem(wall->data(1).toInt())->wall->width=(grith-350)/10;
        this->appendChildObject(a,b,wall);
    } else{
        this->pDiagramScene->clearSelection();
        b->setSelected(true);
        this->Delete_Item();
    }*/
}
/*-----------------------------------------public-------------------------------------------*/

void DiagramView::setTypeItem(TYPEITEM type)
{
    this->typeITEM=type;
}

void DiagramView::ClearScene()
{
   // this->itemScene.RemoveAll();
    foreach(QGraphicsItem *item,this->pDiagramScene->items())
            delete item;
    this->pDiagramScene->clear();
}

void DiagramView::SaveDiagramScene(QString nameFile)
{
    /*QFile saveFile(nameFile);
    if(!saveFile.open(QIODevice::WriteOnly))
        return;
    QDataStream outFile(&saveFile);
    outFile<<this->Rigel<<this->Fundament<<this->pillarBottom;
    outFile<<this->itemScene.CountItem();
    foreach(QGraphicsItem* graphicsItem,this->pDiagramScene->items())
    {
        if(graphicsItem->data(1).toInt()==0)
            continue;
        ITEM *item=this->itemScene.getItem(graphicsItem->data(1).toInt());
        outFile<<item->id<<item->type;
        switch (item->type)
        {
            case ITEM_PILLAR:{
                outFile<<graphicsItem->x()<<graphicsItem->y()<<graphicsItem->rotation()<<item->pillar->height
                      <<item->pillar->insert[0].insertTop<<item->pillar->insert[0].insertBottom
                      <<item->pillar->insert[0].insertTop<<item->pillar->insert[1].insertBottom
                      <<item->pillar->insert[0].insertTop<<item->pillar->insert[2].insertBottom
                      <<item->pillar->insert[0].insertTop<<item->pillar->insert[3].insertBottom
                      <<item->pillar->top<<item->pillar->colorTop.name()<<item->pillar->pazzle<<item->pillar->colorPazzle1.name()
                      <<item->pillar->colorPazzle2.name()<<item->pillar->colorBlocks.count();
                if(!item->pillar->colorBlocks.isEmpty())
                    foreach(QColor color,item->pillar->colorBlocks)
                        outFile<<color.name();
                break;
            }
            case ITEM_WALL:{
                GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(graphicsItem);
                outFile<<wall->line().p1().x()<<wall->line().p1().y()<<wall->line().p2().x()<<wall->line().p2().y()
                       <<item->wall->width<<item->wall->height<<item->wall->wallTop<<item->wall->colorTop.name()
                       <<item->wall->pazzle<<item->wall->colorPazzle1.name()<<item->wall->colorPazzle2.name()<<item->wall->colorBlocks.count();
                if(!item->wall->colorBlocks.isEmpty())
                    foreach(QColor color,item->wall->colorBlocks)
                        outFile<<color.name();
                outFile<<item->wall->d<<item->wall->colorDicoreit.name();
                break;
            }
            default:{
                outFile<<graphicsItem->x()<<graphicsItem->y()<<graphicsItem->rotation();
                break;
            }
        }
        outFile<<item->child.count();
        if(!item->child.isEmpty())
            foreach(CHILD *child,item->child)
                outFile<<child->idChild<<child->resize;
    }*/
}

bool DiagramView::LoadDiagramScene(QString nameFile)
{
   /* this->ClearScene();
    QFile loadFile(nameFile);
    if(!loadFile.open(QIODevice::ReadOnly))
        return false;
    Calculate calc(this->itemSetting);
    QDataStream inFile(&loadFile);
    int CountItem;
    inFile>>this->Rigel>>this->Fundament>>this->pillarBottom;
    inFile>>CountItem;
    for(int i=0;i<CountItem;i++)
    {
        int type;
        int id;
        inFile>>id>>type;
        ITEM *item;
        switch (type)
        {
            case ITEM_PILLAR:{
                GraphicsPillarItem *PillarItem=new GraphicsPillarItem(this->MenuItem);
                this->itemScene.AppendItem(id,ITEM_PILLAR);
                item=this->itemScene.getItem(id);
                float x,y,r;
                QString nameColorTop,nameColorPazzle1,nameColorPazzle2;
                int countColorBrick;
                inFile>>x>>y>>r>>item->pillar->height>>item->pillar->insert[0].insertTop>>item->pillar->insert[0].insertBottom
                     >>item->pillar->insert[1].insertTop>>item->pillar->insert[1].insertBottom
                     >>item->pillar->insert[2].insertTop>>item->pillar->insert[2].insertBottom
                     >>item->pillar->insert[3].insertTop>>item->pillar->insert[3].insertBottom
                     >>item->pillar->top>>nameColorTop>>item->pillar->pazzle>>nameColorPazzle1
                     >>nameColorPazzle2>>countColorBrick;
                item->pillar->colorTop.setNamedColor(nameColorTop);
                item->pillar->colorPazzle1.setNamedColor(nameColorPazzle1);
                item->pillar->colorPazzle2.setNamedColor(nameColorPazzle2);
                for(int i=0;i<countColorBrick;i++)
                {
                    QString nameColorBrick;
                    inFile>>nameColorBrick;
                    item->pillar->colorBlocks.append(QColor(nameColorBrick));
                }
                PillarItem->setPos(x,y);
                PillarItem->rotate(r);
                PillarItem->setData(1,QVariant(item->id));
                this->pDiagramScene->addItem(PillarItem);
                PillarItem->itemGraphicsText()->setPos(x-30,y);
                this->pDiagramScene->addItem(PillarItem->itemGraphicsText());
                PillarItem->itemGraphicsLine()->setLine(QLineF(PillarItem->itemGraphicsText()->pos(),PillarItem->pos()));
                this->pDiagramScene->addItem(PillarItem->itemGraphicsLine());
                int insert[]={item->pillar->insert[0].insertBottom,item->pillar->insert[0].insertTop,
                             item->pillar->insert[1].insertBottom,item->pillar->insert[1].insertTop,
                             item->pillar->insert[2].insertBottom,item->pillar->insert[2].insertTop,
                             item->pillar->insert[3].insertBottom,item->pillar->insert[3].insertTop};
                COLUMN p=calc.GetCountOnColumn(item->pillar->height,insert,4);
                PillarItem->setText(QString(QString::number(p.count_brick_angle)+" | "+
                                                QString::number(p.count_brick_angle_1+p.count_brick_angle_2+p.count_brick_angle_3+p.count_brick_angle_4)));
                break;
            }
            case ITEM_WALL:{
                GraphicsWallItem *WallItem=new GraphicsWallItem(this->MenuItem);
                this->itemScene.AppendItem(id,ITEM_WALL);
                item=this->itemScene.getItem(id);
                QString nameColorTop,nameColorPazzle1,nameColorPazzle2,nameColorDecoreit;
                int countColorBrick;
                float x1,y1,x2,y2;
                inFile>>x1>>y1>>x2>>y2>>item->wall->width>>item->wall->height>>item->wall->wallTop>>nameColorTop
                      >>item->wall->pazzle>>nameColorPazzle1>>nameColorPazzle2>>countColorBrick;
                item->wall->colorTop.setNamedColor(nameColorTop);
                item->wall->colorPazzle1.setNamedColor(nameColorPazzle1);
                item->wall->colorPazzle2.setNamedColor(nameColorPazzle2);
                for(int i=0;i<countColorBrick;i++)
                {
                    QString nameColorBrick;
                    inFile>>nameColorBrick;
                    item->wall->colorBlocks.append(QColor(nameColorBrick));
                }
                inFile>>item->wall->d>>nameColorDecoreit;
                item->wall->colorDicoreit.setNamedColor(nameColorDecoreit);
                WallItem->setLine(x1,y1,x2,y2);
                WallItem->setData(1,QVariant(item->id));
                this->pDiagramScene->addItem(WallItem);
                WallItem->itemGraphicsText()->setPos(WallItem->centre().x()-30,WallItem->centre().y()-30);
                this->pDiagramScene->addItem(WallItem->itemGraphicsText());
                WallItem->itemGraphicsLine()->setLine(QLineF(WallItem->itemGraphicsText()->pos(),WallItem->centre()));
                this->pDiagramScene->addItem(WallItem->itemGraphicsLine());
                FENCE f=calc.GetCountOnFence(item->wall->width,item->wall->height,false);
                WallItem->setText(QString(QString::number(f.count_brick)+" | "+QString::number(f.count_brick_dob)));
                break;
            }
            case ITEM_GATE_A:{

                break;
            }
            case ITEM_GATE_B:{

                break;
            }
            case ITEM_WICKET:{
                break;
            }
            default:break;
        }
        int countChild;
        inFile>>countChild;
        for(int i=0;i<countChild;i++)
        {
            int idChild;
            bool resize;
            inFile>>idChild>>resize;
            item->child.append(new CHILD(idChild,resize,NULL));
        }
    }
    QList<ITEM*> listItem=this->itemScene.items();
    foreach(QGraphicsItem *graphicsItem,this->pDiagramScene->items())
        foreach(ITEM *item,listItem)
            foreach(CHILD *childItem,item->child)
                if(childItem->idChild==graphicsItem->data(1).toInt())
                    childItem->itemChild=graphicsItem;
    this->currentIdItem=listItem.first()->id;
    this->currentIdItem++;*/
    return true;
}

void DiagramView::PrintDiagram()
{
    this->pDiagramScene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::NoBrush));
    this->pDiagramScene->clearSelection();
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                QString(), "*.pdf");
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setPaperSize(QSize(210,297),QPrinter::Millimeter);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QPainter p(&printer);
    bool newPage=false;
    for(int top=0;top<8001;top+=2000)
        for(int left=0;left<8001;left+=2000)
        {
            if(this->pDiagramScene->items(left,top,2000,2000).isEmpty())
                continue;
            if(newPage)
                printer.newPage();
            p.setWindow(left,top,2000,2000);
            this->scene()->render(&p,QRectF(left,top,2000,2000),QRectF(left,top,2000,2000));
            newPage=true;
        }
    this->pDiagramScene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
}

void DiagramView::AppendBrickColorPazzle(QList<COLORBRICK*> *colorBrick,int countColor,QString namedColor)
{
    if(!colorBrick->isEmpty())
    {
        bool appendColor=false;
        foreach(COLORBRICK *brick,*colorBrick)
        {
            if(brick->namedColor==namedColor)
            {
                appendColor=true;
                brick->countBrick+=countColor;
                break;
            }
        }
        if(!appendColor && countColor!=0)
            colorBrick->append(new COLORBRICK(countColor,namedColor));
    }else if(countColor!=0)
            colorBrick->append(new COLORBRICK(countColor,namedColor));
}

void DiagramView::PrintContract(bool girth,bool tray)
{/*
   Calculate calc(this->itemSetting);
   FENCE allFence;
   COLUMN allColumn;
   QList<COLORBRICK*> colorBrick[6];
   int countGirthRail[2];
   countGirthRail[0]=0;
   countGirthRail[1]=0;
   int countTop=0;
   int countBasePillar[5];
   countBasePillar[0]=0;
   countBasePillar[1]=0;
   countBasePillar[2]=0;
   countBasePillar[3]=0;
   countBasePillar[4]=0;
   foreach(QGraphicsItem *itemGraphics,this->pDiagramScene->items())
   {
       if(itemGraphics->data(1).toInt()==0)
           continue;
       ITEM *item=this->itemScene.getItem(itemGraphics->data(1).toInt());
       switch(item->type)
       {
            case ITEM_WALL:{
                FENCE tmpFence=calc.GetCountOnFence(item->wall->width,item->wall->height,true);
                allFence.count_brick+=tmpFence.count_brick;
                allFence.count_brick_dob+=tmpFence.count_brick_dob;
                if(item->wall->wallTop)
                    allFence.count_cover+=tmpFence.count_cover;
                if(tmpFence.count_brick==0)
                    break;
                foreach(COLOR *color,this->itemSetting->color)
                    if(color->color==item->wall->colorTop)
                    {
                        this->AppendBrickColorPazzle(&colorBrick[2],tmpFence.count_cover,
                                                     color->caption);
                        break;
                    }
                if(girth)
                {
                    countGirthRail[0]=item->wall->width<=this->itemSetting->minWidthGirth?countGirthRail[0]+1:
                                                                                          countGirthRail[0];
                    countGirthRail[1]=item->wall->width>this->itemSetting->minWidthGirth?countGirthRail[1]+1:
                                                                                        countGirthRail[1];
                }
                if(item->wall->pazzle)
                {
                    COLORBRICKWALL colorBrickW=calc.colorBrickWall(item->wall->width,item->wall->height);
                    foreach(COLOR *color,this->itemSetting->color)
                    {
                        if(color->color==item->wall->colorPazzle1)
                        {
                            this->AppendBrickColorPazzle(&colorBrick[0],colorBrickW.colorBrickBigWall.at(0),
                                                         color->caption);
                            this->AppendBrickColorPazzle(&colorBrick[1],colorBrickW.colorBrickSmallWall.at(0),
                                                         color->caption);
                        }
                        if(color->color==item->wall->colorPazzle2)
                        {
                            this->AppendBrickColorPazzle(&colorBrick[0],colorBrickW.colorBrickBigWall.at(1),
                                                         color->caption);
                            this->AppendBrickColorPazzle(&colorBrick[1],colorBrickW.colorBrickSmallWall.at(1),
                                                         color->caption);
                        }
                    }
                }else{
                    COLORBRICKWALL colorBrickW=calc.colorListBrickWall(item->wall->width,item->wall->height);
                    for(int i=0;i<item->wall->colorBlocks.count();i++)
                    {
                        foreach(COLOR * colorCaption,this->itemSetting->color)
                            if(item->wall->colorBlocks.at(i)==colorCaption->color)
                            {
                                this->AppendBrickColorPazzle(&colorBrick[0],colorBrickW.colorBrickBigWall.at(i),
                                                             colorCaption->caption);
                                this->AppendBrickColorPazzle(&colorBrick[1],colorBrickW.colorBrickSmallWall.at(i),
                                                             colorCaption->caption);
                                break;
                            }
                    }
                }
                break;
            }
            case ITEM_PILLAR:{
                int side[]={item->pillar->insert[0].insertBottom,
                            item->pillar->insert[1].insertBottom,
                            item->pillar->insert[2].insertBottom,
                            item->pillar->insert[3].insertBottom};
                int insert[]={item->pillar->insert[0].insertBottom,
                              item->pillar->insert[0].insertTop,
                              item->pillar->insert[1].insertBottom,
                              item->pillar->insert[1].insertTop,
                              item->pillar->insert[2].insertBottom,
                              item->pillar->insert[2].insertTop,
                              item->pillar->insert[3].insertBottom,
                              item->pillar->insert[3].insertTop};
                COLUMN tmpColumn=calc.GetCountOnColumn(item->pillar->height,insert,4);
                allColumn.count_brick_angle+=tmpColumn.count_brick_angle;
                allColumn.count_brick_angle_1+=tmpColumn.count_brick_angle_1;
                allColumn.count_brick_angle_2+=tmpColumn.count_brick_angle_2;
                allColumn.count_brick_angle_3+=tmpColumn.count_brick_angle_3;
                allColumn.count_brick_angle_4+=tmpColumn.count_brick_angle_4;
                if(tmpColumn.count_brick_angle+tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_2+
                   tmpColumn.count_brick_angle_3+tmpColumn.count_brick_angle_4==0)
                    break;
                if(tray)
                {
                    tmpColumn.count_brick_angle_1=item->pillar->insert[0].insertBottom>0?1:0;
                    tmpColumn.count_brick_angle_2=item->pillar->insert[1].insertBottom>0?1:0;
                    tmpColumn.count_brick_angle_3=item->pillar->insert[2].insertBottom>0?1:0;
                    tmpColumn.count_brick_angle_4=item->pillar->insert[3].insertBottom>0?1:0;
                    countBasePillar[0]=tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_2+
                                       tmpColumn.count_brick_angle_3+tmpColumn.count_brick_angle_4==0?
                                       countBasePillar[0]+1:countBasePillar[0];
                    countBasePillar[1]=tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_2+
                                       tmpColumn.count_brick_angle_3+tmpColumn.count_brick_angle_4==1?
                                       countBasePillar[1]+1:countBasePillar[1];
                    countBasePillar[4]=tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_2+
                                       tmpColumn.count_brick_angle_3+tmpColumn.count_brick_angle_4==3?
                                       countBasePillar[4]+1:countBasePillar[4];
                    if(tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_2==2 ||
                       tmpColumn.count_brick_angle_3+tmpColumn.count_brick_angle_4==2)
                        countBasePillar[2]+=1;
                    if(tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_3==2 ||
                       tmpColumn.count_brick_angle_2+tmpColumn.count_brick_angle_4==2 ||
                       tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_4==2 ||
                       tmpColumn.count_brick_angle_2+tmpColumn.count_brick_angle_3==2)
                        countBasePillar[3]+=1;
                }
                if(item->pillar->top)
                {
                    countTop+=1;
                    foreach(COLOR *colorCaptionTop,this->itemSetting->color)
                        if(colorCaptionTop->color==item->pillar->colorTop)
                        {
                            this->AppendBrickColorPazzle(&colorBrick[3],1,colorCaptionTop->caption);
                            break;
                        }
                }
                if(item->pillar->pazzle)
                {
                    COLORBRICKPILLAR colorBrickPillar=calc.colorBrickPillar(item->pillar->height,side);
                    foreach(COLOR *colorCaption,this->itemSetting->color)
                    {
                        if(colorCaption->color==item->pillar->colorPazzle1)
                        {
                            this->AppendBrickColorPazzle(&colorBrick[4],colorBrickPillar.colorBrickBigWall.at(0),
                                                         colorCaption->caption);
                            this->AppendBrickColorPazzle(&colorBrick[5],colorBrickPillar.colorBrickSmallWall.at(0),
                                                         colorCaption->caption);
                        }
                        if(colorCaption->color==item->pillar->colorPazzle2)
                        {
                            this->AppendBrickColorPazzle(&colorBrick[4],colorBrickPillar.colorBrickBigWall.at(1),
                                                         colorCaption->caption);
                            this->AppendBrickColorPazzle(&colorBrick[5],colorBrickPillar.colorBrickSmallWall.at(1),
                                                         colorCaption->caption);
                        }
                    }
                }else{
                    COLORBRICKPILLAR colorBrickPillar=calc.colorListBrickPillar(item->pillar->height,side);
                    for(int i=0;i<item->pillar->colorBlocks.count();i++)
                    {
                        foreach(COLOR *colorCaption,this->itemSetting->color)
                            if(colorCaption->color==item->pillar->colorBlocks.at(i))
                            {
                                this->AppendBrickColorPazzle(&colorBrick[4],colorBrickPillar.colorBrickBigWall.at(i),
                                                             colorCaption->caption);
                                this->AppendBrickColorPazzle(&colorBrick[5],colorBrickPillar.colorBrickSmallWall.at(i),
                                                             colorCaption->caption);
                                break;
                            }
                    }
                }
                break;
            }
            default:break;
       }
   }
    QString expColorBrick[6];
    for(int i=0;i<6;i++)
        if(!colorBrick[i].isEmpty())
            foreach(COLORBRICK *countColor,colorBrick[i])
            {
                if(!expColorBrick[i].isEmpty())
                    expColorBrick[i].insert(expColorBrick[i].count(),
                                            QString(" "+QString::number(countColor->countBrick)+" - "+countColor->namedColor));
                else expColorBrick[i].append(QString(QString::number(countColor->countBrick)+" - "+countColor->namedColor));
            }
    ExcelExport contract;
    contract.Open(QDir::currentPath()+"\\Dogovor.xls",this);
    contract.SetBlokRad(QString::number(allFence.count_brick));
    contract.SetBlokRadDob(QString::number(allFence.count_brick_dob));
    contract.SetKrishka500(QString::number(allFence.count_cover));
    contract.SetColorBlokRad(expColorBrick[0]);
    contract.SetColorBlokRadDob(expColorBrick[1]);
    contract.SetColorKrishka500(expColorBrick[2]);
    contract.SetRigel2850(QString::number(countGirthRail[0]));
    contract.SetRigel4050(QString::number(countGirthRail[1]));

    contract.SetBlokUg(QString::number(allColumn.count_brick_angle));
    contract.SetBlokUgPrim(QString::number(allColumn.count_brick_angle_1+allColumn.count_brick_angle_2+
                                           allColumn.count_brick_angle_3+allColumn.count_brick_angle_4));
    contract.SetColorBlockUg(expColorBrick[4]);
    contract.SetColorBlokUgPrim(expColorBrick[5]);
    contract.SetKrishka450(QString::number(countTop));
    contract.SetColorKrishka450(expColorBrick[3]);
    contract.setPillarBase1(QString::number(countBasePillar[0]));
    contract.setPillarBase2(QString::number(countBasePillar[1]));
    contract.setPillarBase3(QString::number(countBasePillar[2]));
    contract.setPillarBase4(QString::number(countBasePillar[3]));
    contract.setPillarBase5(QString::number(countBasePillar[4]));

    contract.setTray(QString::number(calc.GetCountBrickAngleOnPallet(allColumn.count_brick_angle)+
                                     calc.GetCountBrickAnglePrimOnPallet(allColumn.count_brick_angle_1+
                                                                         allColumn.count_brick_angle_2+
                                                                         allColumn.count_brick_angle_3+
                                                                         allColumn.count_brick_angle_4)+
                                     calc.GetCountCoverColumnOnPallet(countTop)+
                                     calc.GetCountBrickOnPallet(allFence.count_brick)+
                                     calc.GetCountBrickDobOnPallet(allFence.count_brick_dob)+
                                     calc.GetCountCoverOnPallet(allFence.count_cover)+
                                     calc.GetCountBaseOnPallet(countBasePillar[0]+countBasePillar[1]+
                                                               countBasePillar[2]+countBasePillar[3]+
                                                               countBasePillar[4])));*/
}

void DiagramView::setSettingItem(SETTINGS *itemSetting)
{
    this->itemSetting=itemSetting;
}

void DiagramView::closeProperties(TYPEITEM itemType,bool all)
{
    Calculate calc(this->itemSetting);
    if(itemType==ITEM_PILLAR)
    {
        GraphicsPillarItem *changePillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->itemGraphicsChange);
        int insert[]={changePillar->heightSide(GraphicsPillarItem::SIDE_FRONT),0,
                     changePillar->heightSide(GraphicsPillarItem::SIDE_BACK),0,
                     changePillar->heightSide(GraphicsPillarItem::SIDE_LIFT),0,
                     changePillar->heightSide(GraphicsPillarItem::SIDE_RIGHT),0};
        COLUMN p=calc.GetCountOnColumn(changePillar->height(),insert,4);
        changePillar->setText(QString(QString::number(p.count_brick_angle)+" | "+
                                        QString::number(p.count_brick_angle_1+p.count_brick_angle_2+p.count_brick_angle_3+p.count_brick_angle_4)));
        if(all)
        {
            foreach(QGraphicsItem *graphicsItem,this->pDiagramScene->items())
            {
                if(graphicsItem->type()!=GraphicsPillarItem::Type)
                    continue;
                if(this->itemGraphicsChange==graphicsItem)
                    continue;
                GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(graphicsItem);
                pillar->setGraphicsPillarItem(changePillar);
                pillar->setText(QString(QString::number(p.count_brick_angle)+" | "+
                                        QString::number(p.count_brick_angle_1+p.count_brick_angle_2+
                                                        p.count_brick_angle_3+p.count_brick_angle_4)));
            }
        }
    }
    if(itemType==ITEM_WALL)
    {
        GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->itemGraphicsChange);
        FENCE f=calc.GetCountOnFence(wall->width(),wall->height(),false);
        wall->setText(QString(QString::number(f.count_brick)+" | "+QString::number(f.count_brick_dob)));
        if(all)
        {
            foreach(QGraphicsItem *graphicsItem,this->pDiagramScene->items())
            {
                if(graphicsItem->type()!=GraphicsWallItem::Type)
                    continue;
                if(graphicsItem==this->itemGraphicsChange)
                    continue;
                GraphicsWallItem *changeWall=qgraphicsitem_cast<GraphicsWallItem*>(graphicsItem);
                changeWall->setText(QString(QString::number(f.count_brick)+" | "+QString::number(f.count_brick_dob)));
                changeWall->setGraphicsWallItem(wall);
            }
        }
    }
}

void DiagramView::component(TYPEITEM typeItem, int width)
{
}

void DiagramView::collidingGroup(QPointF point)
{
    if(this->pDiagramScene->selectedItems().isEmpty())
        return;
    GroupItem *moveGroup=new GroupItem();
    QGraphicsItem *item=this->pDiagramScene->selectedItems().at(0);
    foreach(GroupItem *group,this->listGroup)
        if(group->isItem(item))
        {
            moveGroup=group;
            break;
        }
    if(moveGroup->isType()==GroupItem::ITEM_NONE)
        return;
    QList<QGraphicsItem*> colidingItemList=this->pDiagramScene->collidingItems(moveGroup->items().at(0));
    colidingItemList.append(this->pDiagramScene->collidingItems(moveGroup->items().at(1)));
    GroupItem *coliding=new GroupItem();
    foreach(GroupItem *group,this->listGroup)
    {
        if(moveGroup==group)
            continue;
        foreach(QGraphicsItem *colidingItem,colidingItemList)
        {
            if(colidingItem->type()!=GraphicsPillarItem::Type)
                continue;
            if(group->isItem(colidingItem))
                coliding=group;
        }
        if(coliding->isType()!=GroupItem::ITEM_NONE)
            break;
    }
    if(coliding->isType()==GroupItem::ITEM_NONE)
        return;
    group=new GroupItem();
    connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
    group->createGroup(coliding,moveGroup,this->MenuItem,this->pDiagramScene);
    group->setPos(point);
    this->listGroup.append(group);
    foreach(QGraphicsItem *item,moveGroup->items())
        this->pDiagramScene->removeItem(item);
    foreach(QGraphicsItem *item,coliding->items())
        this->pDiagramScene->removeItem(item);
    this->listGroup.removeAt(this->listGroup.indexOf(moveGroup));
    delete moveGroup;
    this->listGroup.removeAt(this->listGroup.indexOf(coliding));
    delete coliding;
}
/*----------------------------------------protected--------------------------------------------------------*/

void DiagramView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    this->mousePrees=true;
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
    if(this->typeITEM==ITEM_PILLAR)
        this->AppendItem(this->typeITEM,this->mapToScene(event->pos()));
    if(this->typeITEM==ITEM_WALL)
    {
        this->lineWall=new QGraphicsLineItem(QLineF(this->mapToScene(event->pos()),this->mapToScene(event->pos())));
        this->lineWall->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        this->lineWall->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->pDiagramScene->addItem(this->lineWall);
        this->pDiagramScene->clearSelection();
    }
    if(this->typeITEM==ITEM_WICKET)
        this->AppendItem(ITEM_WICKET,this->mapToScene(event->pos()));
    if(this->typeITEM==ITEM_GATE_A)
        this->AppendItem(ITEM_GATE_A,this->mapToScene(event->pos()));
    if(this->typeITEM==ITEM_GATE_B)
        this->AppendItem(ITEM_GATE_B,this->mapToScene(event->pos()));
    if(this->typeITEM==ITEM_FILLING)
    {
        this->lineFilling=new QGraphicsLineItem(QLineF(this->mapToScene(event->pos()),this->mapToScene(event->pos())));
        this->lineFilling->setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        this->lineFilling->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->pDiagramScene->addItem(this->lineFilling);
        this->pDiagramScene->clearSelection();
    }/*
    if(this->typeITEM==ITEM_UNIVER)
    {
        TypeComponent *typeComponent=new TypeComponent(this);
        connect(typeComponent,SIGNAL(component(TYPEITEM,int)),this,SLOT(component(TYPEITEM,int)));
        typeComponent->show();
    }*/
    QGraphicsView::mousePressEvent(event);
}

void DiagramView::mouseMoveEvent(QMouseEvent *event)
{
    if(this->mousePrees)
    {
        this->itemMoveScene(this->mapToScene(event->pos()));
        this->collidingGroup(this->mapToScene(event->pos()));
    }
    if(this->typeITEM==ITEM_WALL)
        if(this->lineWall!=NULL)
            this->lineWall->setLine(QLineF(this->lineWall->line().p1(),this->mapToScene(event->pos())));
    if(this->typeITEM==ITEM_FILLING)
        if(this->lineFilling!=NULL)
            this->lineFilling->setLine(QLineF(this->lineFilling->line().p1(),this->mapToScene(event->pos())));
    QGraphicsView::mouseMoveEvent(event);
}

void DiagramView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    this->mousePrees=false;
    if(this->typeITEM==ITEM_WALL)
    {
        this->lineWall->setLine(QLineF(this->lineWall->line().p1(),this->mapToScene(event->pos())));
        this->AppendItem(ITEM_WALL,QPointF(0,0));
    }
   /* if(this->typeITEM==ITEM_FILLING)
    {
        this->lineFilling->setLine(QLineF(this->lineFilling->line().p1(),this->mapToScene(event->pos())));
        Interval *setIntervalWindow=new Interval(this);
        connect(setIntervalWindow,SIGNAL(closeDialog(float,bool)),this,SLOT(setInterval(float,bool)));
        setIntervalWindow->show();
    }*/
    this->typeITEM=ITEM_NONE;
    QApplication::restoreOverrideCursor();
    QGraphicsView::mouseReleaseEvent(event);
}

void DiagramView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    QList<QGraphicsItem*>itemGraphics=this->pDiagramScene->selectedItems();//items(this->mapToScene(event->pos()));
    if(!itemGraphics.isEmpty())
    {
        if(itemGraphics.at(0)->type()==GraphicsPillarItem::Type)
        {
            PropertiesPillarWindow *PillarWindow=new PropertiesPillarWindow(this);
            PillarWindow->heightBrick=this->itemSetting->heightBrickAngle;
            connect(PillarWindow,SIGNAL(closeProperties(TYPEITEM,bool)),this,SLOT(closeProperties(TYPEITEM,bool)));
            this->itemGraphicsChange=itemGraphics.at(0);
            PillarWindow->SetPropertiesPillar(qgraphicsitem_cast<GraphicsPillarItem*>(this->itemGraphicsChange),this->itemSetting->color);
            PillarWindow->show();
        }
        if(itemGraphics.at(0)->type()==GraphicsWallItem::Type)
        {
            this->itemGraphicsChange=itemGraphics.at(0);
            GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->itemGraphicsChange);
            QGraphicsItem *wallPillar=this->itemToScene(ITEM_PILLAR,wall->line().p1());
            if(wallPillar!=NULL)
            {

                GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(wallPillar);
                if(pillar->height()>=this->itemSetting->heightBrickAngle)
                {
                    PropertiesWallWindow *wallWindow=new PropertiesWallWindow(this);
                    connect(wallWindow,SIGNAL(closeProperties(TYPEITEM,bool)),this,SLOT(closeProperties(TYPEITEM,bool)));
                    wallWindow->SetPropertiesWall(wall,this->itemSetting,pillar);
                    wallWindow->show();
                }
            }
        }
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void DiagramView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete)
        this->Delete_Item();
    if(event->key()==Qt::Key_A)
        if(event->modifiers()==Qt::ControlModifier)
            foreach(QGraphicsItem* graphicsItem,this->pDiagramScene->items())
                    graphicsItem->setSelected(true);
    QGraphicsView::keyPressEvent(event);
}

