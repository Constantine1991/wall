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
    this->typeITEM=ITEM_NONE;
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

QGraphicsItem* DiagramView::AppendItem(TYPEITEM typeItem, QPointF point)
{
    switch(typeItem)
    {
        case ITEM_PILLAR:{
            GraphicsPillarItem *PillarItem=new GraphicsPillarItem(this->MenuItem);
            PillarItem->setPos(point);
            this->pDiagramScene->addItem(PillarItem);
            return PillarItem;
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
            return wall;
        }
        case ITEM_GATE_A:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            group->createGroup(GroupItem::ITEM_GATE1,this->MenuItem,this->pDiagramScene);
            group->setPos(point);
            this->listGroup.append(group);
            return NULL;
        }
        case ITEM_GATE_B:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            group->createGroup(GroupItem::ITEM_GATE2,this->MenuItem,this->pDiagramScene);
            group->setPos(point);
            this->listGroup.append(group);
            return NULL;
        }
        case ITEM_WICKET:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            group->createGroup(GroupItem::ITEM_WICKET,this->MenuItem,this->pDiagramScene);
            group->setPos(point);
            this->listGroup.append(group);
            return NULL;
        }
        default:return NULL;
    }
}

void DiagramView::AppendItem(GroupItem::TYPEGROUP typeGroup, QPointF point)
{
    group=new GroupItem();
    connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
    group->createGroup(typeGroup,this->MenuItem,this->pDiagramScene);
    group->setPos(point);
    this->listGroup.append(group);
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
                foreach(GroupItem *group,this->listGroup)
                    if(group->isItem(parentItem))
                    {
                        if(parentItem->type()==GraphicsPillarItem::Type)
                        {
                            QList<QGraphicsItem*> item=group->items();
                            if(item.count()==3)
                                this->pDiagramScene->removeItem(item.at(2));
                            if(item.count()==5)
                            {
                                this->pDiagramScene->removeItem(item.at(4));
                                this->pDiagramScene->removeItem(item.at(3));
                            }
                        }
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
    this->listGroup.clear();
    foreach(QGraphicsItem *item,this->pDiagramScene->items())
            delete item;
    this->pDiagramScene->clear();
}

void DiagramView::savePillar(QDomDocument *document,QDomElement *parent, GraphicsPillarItem *pillar)
{
    QDomElement object=document->createElement("Object");
    object.setAttribute("type",pillar->type());
    QDomElement point=document->createElement("Point");
    point.setAttribute("x",pillar->pos().x());
    point.setAttribute("y",pillar->pos().y());
    object.appendChild(point);
    QDomElement rotation=document->createElement("rotation");
    rotation.setAttribute("value",pillar->rotation());
    object.appendChild(rotation);
    QDomElement height=document->createElement("HeightPillar");
    height.setAttribute("value",pillar->height());
    object.appendChild(height);
    QDomElement heightSide=document->createElement("HeightSide");
    for(int i=0;i<4;i++)
    {
        QDomElement side=document->createElement("side");
        side.setAttribute("id",i);
        side.setAttribute("value",pillar->heightSide(i));
        heightSide.appendChild(side);
    }
    object.appendChild(heightSide);
    QDomElement top=document->createElement("Top");
    top.setAttribute("enable",pillar->isTop());
    QDomElement color=document->createElement("color");
    color.setAttribute("caption",pillar->topColor().caption);
    color.setAttribute("name",pillar->topColor().color.name());
    top.appendChild(color);
    object.appendChild(top);
    QDomElement pazzle=document->createElement("Pazzle");
    pazzle.setAttribute("enable",pillar->isPazzle());
    color=document->createElement("color");
    color.setAttribute("id",0);
    color.setAttribute("caption",pillar->colorPazzle(0).caption);
    color.setAttribute("name",pillar->colorPazzle(0).color.name());
    pazzle.appendChild(color);
    color=document->createElement("color");
    color.setAttribute("id",1);
    color.setAttribute("caption",pillar->colorPazzle(1).caption);
    color.setAttribute("name",pillar->colorPazzle(1).color.name());
    pazzle.appendChild(color);
    object.appendChild(pazzle);
    QDomElement colorRow=document->createElement("ColorRow");
    colorRow.setAttribute("empty",pillar->colorListRow().isEmpty());
    foreach(COLOR c,pillar->colorListRow())
    {
        color=document->createElement("color");
        color.setAttribute("caption",c.caption);
        color.setAttribute("name",c.color.name());
        colorRow.appendChild(color);
    }
    object.appendChild(colorRow);
    QDomElement bottomType=document->createElement("Bottom");
    bottomType.setAttribute("type",pillar->isBottomType());
    object.appendChild(bottomType);
    parent->appendChild(object);
}

void DiagramView::SaveDiagramScene(QString nameFile)
{
    QDomDocument document;
    QDomElement root=document.createElement("data");
    document.appendChild(root);
    for(int i=this->pDiagramScene->items().count()-1;i>-1;i--)
    {
        QGraphicsItem* graphicsItem=this->pDiagramScene->items().at(i);
        bool saveItem=true;
        foreach(GroupItem *group,this->listGroup)
            if(group->isItem(graphicsItem))
            {
                saveItem=false;
                break;
            }
        if(saveItem)
            switch (graphicsItem->type())
            {
                case GraphicsPillarItem::Type:{
                    GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(graphicsItem);
                    this->savePillar(&document,&root,pillar);
                    break;
                }
                case GraphicsWallItem::Type:{
                    GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(graphicsItem);
                    QDomElement object=document.createElement("Object");
                    object.setAttribute("type",wall->type());
                    QDomElement point=document.createElement("Point");
                    point.setAttribute("x1",wall->posP1().x());
                    point.setAttribute("y1",wall->posP1().y());
                    point.setAttribute("x2",wall->posP2().x());
                    point.setAttribute("y2",wall->posP2().y());
                    object.appendChild(point);
                    QDomElement height=document.createElement("Height");
                    height.setAttribute("value",wall->height());
                    object.appendChild(height);
                    QDomElement width=document.createElement("Width");
                    width.setAttribute("value",wall->width());
                    object.appendChild(width);
                    QDomElement top=document.createElement("Top");
                    top.setAttribute("enable",wall->isTop());
                    QDomElement color=document.createElement("color");
                    color.setAttribute("caption",wall->colorTop().caption);
                    color.setAttribute("name",wall->colorTop().color.name());
                    top.appendChild(color);
                    object.appendChild(top);
                    QDomElement pazzle=document.createElement("Pazzle");
                    pazzle.setAttribute("enable",wall->isPazzle());
                    color=document.createElement("color");
                    color.setAttribute("caption",wall->colorPazzle(0).caption);
                    color.setAttribute("name",wall->colorPazzle(0).color.name());
                    color.setAttribute("id",0);
                    pazzle.appendChild(color);
                    color=document.createElement("color");
                    color.setAttribute("caption",wall->colorPazzle(1).caption);
                    color.setAttribute("name",wall->colorPazzle(1).color.name());
                    color.setAttribute("id",1);
                    pazzle.appendChild(color);
                    object.appendChild(pazzle);
                    QDomElement colorRow=document.createElement("ColorRow");
                    colorRow.setAttribute("empty",wall->colorListRow().isEmpty());
                    foreach(COLOR c,wall->colorListRow())
                    {
                        color=document.createElement("color");
                        color.setAttribute("caption",c.caption);
                        color.setAttribute("name",c.color.name());
                        colorRow.appendChild(color);
                    }
                    object.appendChild(colorRow);
                    QDomElement decoreit=document.createElement("Decoreit");
                    decoreit.setAttribute("enable",wall->isDecoreid());
                    color=document.createElement("color");
                    color.setAttribute("caption",wall->colorDecoreid().caption);
                    color.setAttribute("name",wall->colorDecoreid().color.name());
                    decoreit.appendChild(color);
                    object.appendChild(decoreit);
                    QDomElement girthRail=document.createElement("GirthRail");
                    girthRail.setAttribute("enable",wall->isGirthRail());
                    object.appendChild(girthRail);
                    root.appendChild(object);
                    break;
                }
                default:break;
            }
    }

    QFile saveFile(nameFile);
    if(!saveFile.open(QIODevice::WriteOnly|QIODevice::Text))
        return;
    QTextStream outFile(&saveFile);
    outFile<<document.toString();
    saveFile.close();
}

void DiagramView::loadPillar(QXmlStreamReader *xml, GraphicsPillarItem *pillar)
{
    while(!(xml->isEndElement()&&xml->name()=="Object"))
    {
        if(xml->isStartElement())
        {
            if(xml->name()=="Point")
                pillar->setPos(xml->attributes().value("x").toString().toFloat(),
                               xml->attributes().value("y").toString().toFloat());
            if(xml->name()=="rotation")
                pillar->setRotation(xml->attributes().value("value").toString().toFloat());
            if(xml->name()=="HeightPillar")
                pillar->setHeight(xml->attributes().value("value").toString().toInt());
            if(xml->name()=="HeightSide")
                while(!(xml->isEndElement()&&xml->name()=="HeightSide"))
                {
                    if(xml->isStartElement()&&xml->name()=="side")
                        pillar->setHeightSide(xml->attributes().value("id").toString().toInt(),
                                              xml->attributes().value("value").toString().toInt());
                    xml->readNext();
                }
            if(xml->name()=="Top")
            {
                pillar->setTop((bool)xml->attributes().value("enable").toString().toInt());
                while(!(xml->isEndElement()&&xml->name()=="Top"))
                {
                    if(xml->isStartElement()&&xml->name()=="color")
                        pillar->setTopColor(COLOR(QColor(xml->attributes().value("name").toString()),
                                                         xml->attributes().value("caption").toString()));
                    xml->readNext();
                }
            }
            if(xml->name()=="Pazzle")
            {
                pillar->setPazzle((bool)xml->attributes().value("enable").toString().toInt());
                while(!(xml->isEndElement()&&xml->name()=="Pazzle"))
                {
                    if(xml->isStartElement()&&xml->name()=="color")
                        pillar->setColorPazzle(xml->attributes().value("id").toString().toInt(),
                                              COLOR(QColor(xml->attributes().value("name").toString()),
                                                           xml->attributes().value("caption").toString()));
                    xml->readNext();
                }
            }
            if(xml->name()=="ColorRow")
            {
                bool empty=(bool)xml->attributes().value("empty").toString().toInt();
                if(!empty)
                    while(!(xml->isEndElement()&&xml->name()=="ColorRow"))
                    {
                        if(xml->isStartElement()&&xml->name()=="color")
                            pillar->addColorRow(COLOR(QColor(xml->attributes().value("name").toString()),
                                                      xml->attributes().value("caption").toString()));
                        xml->readNext();
                    }
            }
            if(xml->name()=="Bottom")
                pillar->setBottomType(xml->attributes().value("type").toString().toInt());
        }
        xml->readNext();
    }
    int insert[]={pillar->heightSide(0),0,pillar->heightSide(1),0,pillar->heightSide(2),0,
                  pillar->heightSide(3),0};
    Calculate calc(this->itemSetting);
    COLUMN p=calc.GetCountOnColumn(pillar->height(),insert,4);
    pillar->setText(QString(QString::number(p.count_brick_angle)+" | "+
                            QString::number(p.count_brick_angle_1+p.count_brick_angle_2+
                                            p.count_brick_angle_3+p.count_brick_angle_4)));
}

bool DiagramView::LoadDiagramScene(QString nameFile)
{
    this->ClearScene();
    QFile loadFile(nameFile);
    if(!loadFile.open(QIODevice::ReadOnly|QIODevice::Text))
        return false;
    Calculate calc(this->itemSetting);
    QTextStream inFile(&loadFile);
    QString dataFile=inFile.readAll();
    QXmlStreamReader xml(dataFile);
    while(!xml.atEnd())
    {
        if(xml.isStartElement())
        {
            if(xml.name()=="Object")
            {
                switch (xml.attributes().value("type").toString().toInt())
                {
                    case GraphicsPillarItem::Type:{
                        GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->AppendItem(ITEM_PILLAR,QPointF(0,0)));
                        this->loadPillar(&xml,pillar);
                        break;
                    }
                    case GraphicsWallItem::Type:{
                        GraphicsWallItem *wall;
                        while(!(xml.isEndElement()&&xml.name()=="Object"))
                        {
                            if(xml.isStartElement())
                            {
                                if(xml.name()=="Point")
                                {
                                    this->lineWall=new QGraphicsLineItem(xml.attributes().value("x1").toString().toFloat(),
                                                                         xml.attributes().value("y1").toString().toFloat(),
                                                                         xml.attributes().value("x2").toString().toFloat(),
                                                                         xml.attributes().value("y2").toString().toFloat());
                                    wall=qgraphicsitem_cast<GraphicsWallItem*>(this->AppendItem(ITEM_WALL,QPointF(0,0)));
                                }
                                if(xml.name()=="Height")
                                    wall->setHeight(xml.attributes().value("value").toString().toInt());
                                if(xml.name()=="Width")
                                    wall->setWidth(xml.attributes().value("value").toString().toInt());
                                if(xml.name()=="Top")
                                {
                                    wall->setTop((bool)xml.attributes().value("enable").toString().toInt());
                                    while(!(xml.isEndElement()&&xml.name()=="Top"))
                                    {
                                        if(xml.isStartElement()&&xml.name()=="color")
                                            wall->setColorTop(COLOR(QColor(xml.attributes().value("name").toString()),
                                                                    xml.attributes().value("caption").toString()));
                                        xml.readNext();
                                    }
                                }
                                if(xml.name()=="Pazzle")
                                {
                                    wall->setPazzle((bool)xml.attributes().value("enable").toString().toInt());
                                    while(!(xml.isEndElement()&&xml.name()=="Pazzle"))
                                    {
                                        if(xml.isStartElement()&&xml.name()=="color")
                                            wall->setColorPazzle(xml.attributes().value("id").toString().toInt(),
                                                                 COLOR(QColor(xml.attributes().value("name").toString()),
                                                                       xml.attributes().value("caption").toString()));
                                        xml.readNext();
                                    }
                                }
                                if(xml.name()=="ColorRow")
                                {
                                    bool empty=(bool)xml.attributes().value("empty").toString().toInt();
                                    if(!empty)
                                        while(!(xml.isEndElement()&&xml.name()=="ColorRow"))
                                        {
                                            if(xml.isStartElement()&&xml.name()=="color")
                                                wall->addColorRow(COLOR(QColor(xml.attributes().value("name").toString()),
                                                                        xml.attributes().value("caption").toString()));
                                            xml.readNext();
                                        }
                                }
                                if(xml.name()=="Decoreit")
                                {
                                    wall->setDecoreid(xml.attributes().value("enable").toString().toInt());
                                    while(!(xml.isEndElement()&&xml.name()=="Decoreit"))
                                    {
                                        if(xml.isStartElement()&&xml.name()=="color")
                                            wall->setColorDecoreid(COLOR(QColor(xml.attributes().value("name").toString()),
                                                                         xml.attributes().value("caption").toString()));
                                        xml.readNext();
                                    }
                                }
                                if(xml.name()=="GirthRail")
                                    wall->setGirthRail((bool)xml.attributes().value("enable").toString().toInt());
                            }
                            xml.readNext();
                        }
                        FENCE f=calc.GetCountOnFence(wall->width(),wall->height(),false);
                        wall->setText(QString(QString::number(f.count_brick)+" | "+QString::number(f.count_brick_dob)));
                        break;
                    }
                default:break;
                }
            }
        }
        xml.readNext();
    }
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
    if((int)coliding->isType()<3 && (int)moveGroup->isType()<3)
    {
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
}
/*----------------------------------------protected--------------------------------------------------------*/

void DiagramView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    this->mousePrees=true;
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
    if(this->typeITEM==ITEM_PILLAR)
        this->AppendItem(ITEM_PILLAR,this->mapToScene(event->pos()));
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

