#include "diagramview.h"
///////////////////////////////////
#include <QDebug>
//////////////////////////////////



DiagramView::DiagramView(QWidget *parent):QGraphicsView(parent)
{
    this->widthGroup=0;
    this->setMouseTracking(true);
    this->pDiagramScene=new QGraphicsScene(QRectF(0,0,8000,8000),parent);
    this->setScene(this->pDiagramScene);
    this->currentIdItem=1;
    this->lineWall=NULL;
    this->lineFilling=NULL;
    this->linePoint1=NULL;
    this->linePoint2=NULL;
    this->CreateMenuItem();
    this->pDiagramScene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::CrossPattern));
    this->pillarBottom=false;
    this->Fundament=false;
    this->Rigel=false;
    this->mousePrees=false;
    this->centerOn(0,0);
    this->typeITEM=SettingItem::ITEM_NONE;
    this->keyPressA=false;
    this->RectA=NULL;
    this->alignment.setScene(this->pDiagramScene);
    this->lock=false;
    this->title.setDiagramScene(this->pDiagramScene);
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

QGraphicsItem *DiagramView::itemToScene(SettingItem::TYPEITEM typeItem, QPointF point)
{
    QList<QGraphicsItem*> listItem=this->pDiagramScene->items(point);
    if(!listItem.isEmpty())
    {
        foreach(QGraphicsItem *item,listItem)
            switch(typeItem)
            {
                case SettingItem::ITEM_PILLAR:{
                    if(item->type()==GraphicsPillarItem::Type)
                        return item;
                }
                default:break;
            }
    }
    return NULL;
}

QGraphicsItem* DiagramView::AppendItem(SettingItem::TYPEITEM typeItem, QPointF point)
{
    switch(typeItem)
    {
        case SettingItem::ITEM_PILLAR:{
            GraphicsPillarItem *PillarItem=new GraphicsPillarItem(this->MenuItem);
            PillarItem->setEnabledBackUp(true);
            PillarItem->setPosition(point);
            this->objectBackUp.append(PillarItem);
            this->pDiagramScene->addItem(PillarItem);
            return PillarItem;
        }
        case SettingItem::ITEM_WALL:{
            GraphicsWallItem *wall=new GraphicsWallItem(this->MenuItem);
            QGraphicsItem *item1=this->itemToScene(SettingItem::ITEM_PILLAR,this->lineWall->line().p1());
            QGraphicsItem *item2=this->itemToScene(SettingItem::ITEM_PILLAR,this->lineWall->line().p2());
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
        case SettingItem::ITEM_GATE_A:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            connect(this,SIGNAL(mouseRelease()),group,SLOT(mouseRelease()));
            group->createGroup(GroupItem::ITEM_GATE1,this->MenuItem,this->pDiagramScene);
            group->setPos(point);
            this->objectBackUp.append(group->items().at(0));
            GraphicsGate1Item *g=qgraphicsitem_cast<GraphicsGate1Item*>(group->items().at(1));
            g->setText(QString::number(this->widthGroup));
            this->listGroup.append(group);
            return NULL;
        }
        case SettingItem::ITEM_GATE_B:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            connect(this,SIGNAL(mouseRelease()),group,SLOT(mouseRelease()));
            group->createGroup(GroupItem::ITEM_GATE2,this->MenuItem,this->pDiagramScene);
            GraphicsGate2Item *g=qgraphicsitem_cast<GraphicsGate2Item*>(group->items().at(1));
            g->setText(QString::number(this->widthGroup));
            group->setPos(point);
            this->objectBackUp.append(group->items().at(0));
            this->listGroup.append(group);
            return NULL;
        }
        case SettingItem::ITEM_WICKET:{
            group=new GroupItem();
            connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
            connect(this,SIGNAL(mouseRelease()),group,SLOT(mouseRelease()));
            group->createGroup(GroupItem::ITEM_WICKET,this->MenuItem,this->pDiagramScene);
            GraphicsWicketItem *w=qgraphicsitem_cast<GraphicsWicketItem*>(group->items().at(1));
            w->setText(QString::number(this->widthGroup));
            group->setPos(point);
            this->objectBackUp.append(group->items().at(0));
            this->listGroup.append(group);
            return NULL;
        }
        case SettingItem::ITEM_LINE:{
            GraphicsLineItem *line=new GraphicsLineItem();
            line->setPoints(this->linePoint1->pos(),this->linePoint2->pos(),this->pDiagramScene);
            this->pDiagramScene->removeItem(this->linePoint1);
            this->pDiagramScene->removeItem(this->linePoint2);
            delete this->linePoint1;
            delete this->linePoint2;
            this->linePoint1=NULL;
            this->linePoint2=NULL;
            break;
        }
        default:return NULL;
    }
    return NULL;
}
/*
void DiagramView::AppendItem(GroupItem::TYPEGROUP typeGroup,QPointF point)
{
    group=new GroupItem();
    connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
    connect(this,SIGNAL(mouseRelease()),group,SLOT(mouseRelease()));
    group->createGroup(typeGroup,this->MenuItem,this->pDiagramScene);
    group->setPos(point);
    this->listGroup.append(group);
}*/

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
            return;
        }
    if(this->pDiagramScene->selectedItems().at(0)->type()==GraphicsPillarItem::Type)
        this->pDiagramScene->selectedItems().at(0)->setRotation(this->pDiagramScene->selectedItems().at(0)->rotation()+
                                                                Angle);
}

QPointF DiagramView::centerItem(QGraphicsItem *itemGraphics)
{
    int x=itemGraphics->pos().x()+(itemGraphics->boundingRect().width()/2*TableAngle[0][(int)itemGraphics->rotation()/45]);
    int y=itemGraphics->pos().y()+(itemGraphics->boundingRect().height()/2*TableAngle[1][(int)itemGraphics->rotation()/45]);
    return QPointF(x,y);
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
                    QList<QGraphicsItem *> items=group->items();
                    foreach(QGraphicsItem *item,items)
                    {
                        if(parentItem==item)
                            continue;
                        foreach(QGraphicsItem *childItem,item->childItems())
                        {
                            this->pDiagramScene->removeItem(childItem);
                            delete childItem;
                        }
                        this->pDiagramScene->removeItem(item);
                        delete item;
                    }
                    this->listGroup.removeAt(this->listGroup.indexOf(group));
                    delete group;
                    break;
                }
            if(parentItem->type()==GraphicsPillarItem::Type)
            {
                while(true)
                {
                    int index=this->objectBackUp.indexOf(parentItem);
                    if(index==-1)
                        break;
                    this->objectBackUp.removeAt(index);
                }
            }
            if(parentItem->type()==GraphicsWallItem::Type)
            {
                GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(parentItem);
                GraphicsPillarItem *pillar1=qgraphicsitem_cast<GraphicsPillarItem*>(this->itemToScene(SettingItem::ITEM_PILLAR,wall->line().p1()));
                GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(this->itemToScene(SettingItem::ITEM_PILLAR,wall->line().p2()));
                if(pillar1!=NULL)
                    pillar1->removeWall(wall);
                if(pillar2!=NULL)
                    pillar2->removeWall(wall);
            }
            foreach(QGraphicsItem *childItem,parentItem->childItems())
            {
                this->pDiagramScene->removeItem(childItem);
                delete childItem;
            }
            this->pDiagramScene->removeItem(parentItem);
            delete parentItem;
        }
    }
}

void DiagramView::setInterval(float interval, bool empty)
{
    if(empty || interval<this->itemSetting->maxWidthBrickR+35)
    {
        this->deleteFilling();
        return;
    }
    QGraphicsItem *ObjectA,*ObjectB;
    ObjectA=this->itemToScene(SettingItem::ITEM_PILLAR,this->lineFilling->line().p1());
    ObjectB=this->itemToScene(SettingItem::ITEM_PILLAR,this->lineFilling->line().p2());
    this->deleteFilling();
    if(ObjectA!=NULL && ObjectB!=NULL)
        this->Filling(qgraphicsitem_cast<GraphicsPillarItem*>(ObjectA),
                      qgraphicsitem_cast<GraphicsPillarItem*>(ObjectB),interval);
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

void DiagramView::Filling(GraphicsPillarItem *a, GraphicsPillarItem *b,float interval)
{
    QPointF posA,posB,point;
    posA=a->centre();
    posB=b->centre();
    GroupItem *groupItem=new GroupItem();
    foreach(GroupItem *group,this->listGroup)
        if(group->isItem(b))
        {
            groupItem=group;
            break;
        }
    float angle=::atan2(posA.y()-posB.y(),posA.x()-posB.x())/PI*180;
    angle=angle<0?angle+360:angle;
    int countObject=qFloor(interval/(this->itemSetting->maxWidthGirth+35));
    int residue=interval-(this->itemSetting->maxWidthGirth+35)*countObject;
    float distance=a->boundingRect().width()+50;
    for(int i=0;i<countObject-1;i++)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-(distance*(i+1)),posA.y()),angle);
        point.setX(point.x()-b->boundingRect().width()/2);
        point.setY(point.y()-b->boundingRect().height()/2);
        GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->AppendItem(SettingItem::ITEM_PILLAR,point));
        this->lineWall=new QGraphicsLineItem(QLineF(a->centre(),pillar->centre()));
        GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->AppendItem(SettingItem::ITEM_WALL,QPointF(0,0)));
        wall->setGirthRail(true);
        wall->setWidth(this->itemSetting->maxWidthGirth);
        a=pillar;
    }
    if(residue==0)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-distance*countObject,posA.y()),angle);
        point.setX(point.x()-b->boundingRect().width()/2);
        point.setY(point.y()-b->boundingRect().height()/2);
        b->setPosition(point);
        if(!groupItem->types().isEmpty())
            groupItem->setOffsetPos(b->centre(),distance);
        this->lineWall=new QGraphicsLineItem(QLineF(a->centre(),b->centre()));
        GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->AppendItem(SettingItem::ITEM_WALL,QPointF(0,0)));
        wall->setGirthRail(true);
        wall->setWidth(this->itemSetting->maxWidthGirth);
        return;
    }
    if(countObject!=0)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-distance*countObject,posA.y()),angle);
        point.setX(point.x()-b->boundingRect().width()/2);
        point.setY(point.y()-b->boundingRect().height()/2);
        GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->AppendItem(SettingItem::ITEM_PILLAR,point));
        this->lineWall=new QGraphicsLineItem(QLineF(a->centre(),pillar->centre()));
        GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->AppendItem(SettingItem::ITEM_WALL,QPointF(0,0)));
        wall->setGirthRail(true);
        wall->setWidth(this->itemSetting->maxWidthGirth);
        a=pillar;
    }
    int grith=0;
    if(residue>this->itemSetting->minWidthBrickR+35)
    {
        for(int i=this->itemSetting->maxWidthBrickR+35;i<=this->itemSetting->maxWidthGirth+35;i+=15)
            if(i>=residue)
            {
                grith=i;
                break;
            }
    }else{
        if(residue>=qFloor(this->itemSetting->minWidthBrickR/2))
            grith=this->itemSetting->minWidthBrickR+35;
    }
    if(grith>0)
    {
        point=this->rotatePoint(posA,QPointF(posA.x()-distance*(countObject+1),posA.y()),angle);
        point.setX(point.x()-b->boundingRect().width()/2);
        point.setY(point.y()-b->boundingRect().height()/2);
        b->setPosition(point);
        if(!groupItem->types().isEmpty())
            groupItem->setOffsetPos(b->centre(),distance);
        this->lineWall=new QGraphicsLineItem(QLineF(a->centre(),b->centre()));
        GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->AppendItem(SettingItem::ITEM_WALL,QPointF(0,0)));
        wall->setGirthRail(true);
        wall->setWidth(grith-35);
    }
}
/*-----------------------------------------public-------------------------------------------*/

void DiagramView::setTypeItem(SettingItem::TYPEITEM type)
{
    this->typeITEM=type;
    if(this->linePoint1!=NULL)
    {
        this->pDiagramScene->removeItem(this->linePoint1);
        delete this->linePoint1;
        this->linePoint1=NULL;
    }
    if(this->linePoint2!=NULL)
    {
        this->pDiagramScene->removeItem(this->linePoint2);
        delete this->linePoint2;
        this->linePoint2=NULL;
    }
}

void DiagramView::setTypeItem(SettingItem::TYPEITEM type, int interval)
{
    this->setTypeItem(type);
    this->widthGroup=interval;
}

void DiagramView::ClearScene()
{
    foreach(GroupItem *group,this->listGroup)
        delete group;
    this->listGroup.clear();
   /* foreach(QGraphicsItem *item,this->objectBackUp)
        delete item;*/
    if(!this->objectBackUp.isEmpty())
        this->objectBackUp.clear();
    foreach(QGraphicsItem *item,this->pDiagramScene->items())
    {
        foreach(QGraphicsItem *child,item->childItems())
            delete child;
        delete item;
    }
    this->pDiagramScene->clear();
}

void DiagramView::savePillar(QDomDocument *document,QDomElement *parent, GraphicsPillarItem *pillar)
{
    /*QDomElement object=document->createElement("Object");
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
    bottomType.setAttribute("type",pillar->isBottomTypeEnable());
    object.appendChild(bottomType);
    parent->appendChild(object);*/
}

void DiagramView::SaveDiagramScene(QString nameFile)
{
   /* QDomDocument document;
    QDomElement root=document.createElement("data");
    document.appendChild(root);
    QDomElement f=document.createElement("Fundament");
    f.setAttribute("value",this->Fundament);
    root.appendChild(f);
    foreach(QGraphicsItem* graphicsItem,this->pDiagramScene->items())
    {
        bool saveItem=true;
        foreach(GroupItem *group,this->listGroup)
            if(group->isItem(graphicsItem))
            {
                saveItem=false;
                break;
            }
        if(saveItem && graphicsItem->type()==GraphicsPillarItem::Type)
        {
            GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(graphicsItem);
            this->savePillar(&document,&root,pillar);
        }
    }
    foreach(GroupItem *group,this->listGroup)
    {
        QDomElement groupObject=document.createElement("GroupObject");
        groupObject.setAttribute("x",group->pos().x());
        groupObject.setAttribute("y",group->pos().y());
        groupObject.setAttribute("rotation",group->rot());
        foreach(QGraphicsItem *item,group->items())
        {
            switch(item->type())
            {
                case GraphicsPillarItem::Type:{
                    GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
                    this->savePillar(&document,&groupObject,pillar);
                    break;
                }
                case GraphicsWicketItem::Type:{
                    GraphicsWicketItem *graphicObject=qgraphicsitem_cast<GraphicsWicketItem*>(item);
                    QDomElement object=document.createElement("Object");
                    object.setAttribute("type",graphicObject->type());;
                    QDomElement width=document.createElement("Width");
                    width.setAttribute("value",graphicObject->value());
                    object.appendChild(width);
                    groupObject.appendChild(object);
                    break;
                }
                case GraphicsGate1Item::Type:{
                    GraphicsGate1Item *graphicObject=qgraphicsitem_cast<GraphicsGate1Item*>(item);
                    QDomElement object=document.createElement("Object");
                    object.setAttribute("type",graphicObject->type());
                    QDomElement width=document.createElement("Width");
                    width.setAttribute("value",graphicObject->value());
                    object.appendChild(width);
                    groupObject.appendChild(object);
                    break;
                }
                case GraphicsGate2Item::Type:{
                    GraphicsGate2Item *graphicObject=qgraphicsitem_cast<GraphicsGate2Item*>(item);
                    QDomElement object=document.createElement("Object");
                    object.setAttribute("type",graphicObject->type());
                    QDomElement width=document.createElement("Width");
                    width.setAttribute("value",graphicObject->value());
                    object.appendChild(width);
                    groupObject.appendChild(object);
                    break;
                }
                default:break;
            }
        }
        root.appendChild(groupObject);
    }
    foreach(QGraphicsItem *graphicsItem,this->pDiagramScene->items())
    {
        bool saveItem=true;
        foreach(GroupItem *group,this->listGroup)
            if(group->isItem(graphicsItem))
            {
                saveItem=false;
                break;
            }
        if(saveItem && graphicsItem->type()==GraphicsWallItem::Type)
        {
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
        }
    }
    QFile saveFile(nameFile);
    if(!saveFile.open(QIODevice::WriteOnly|QIODevice::Text))
        return;
    QTextStream outFile(&saveFile);
    outFile<<document.toString();
    saveFile.close();*/
}

void DiagramView::loadPillar(QXmlStreamReader *xml, GraphicsPillarItem *pillar)
{
   /* while(!(xml->isEndElement()&&xml->name()=="Object"))
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
                pillar->setBottomTypeEnable((bool)xml->attributes().value("type").toString().toInt());
        }
        xml->readNext();
    }
    int insert[]={pillar->heightSide(0),0,pillar->heightSide(1),0,pillar->heightSide(2),0,
                  pillar->heightSide(3),0};
    Calculate calc(this->itemSetting);
    COLUMN p=calc.GetCountOnColumn(pillar->height(),insert,4);
    pillar->setText(QString(QString::number(p.count_brick_angle)+" | "+
                            QString::number(p.count_brick_angle_1+p.count_brick_angle_2+
                                            p.count_brick_angle_3+p.count_brick_angle_4)));*/
}

bool DiagramView::LoadDiagramScene(QString nameFile)
{
   /* this->ClearScene();
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
            if(xml.name()=="Fundament")
                this->Fundament=(bool)xml.attributes().value("value").toString().toInt();
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
            if(xml.name()=="GroupObject")
            {
                this->group=new GroupItem();
                connect(this,SIGNAL(itemMoveScene(QPointF)),group,SLOT(itemMoveScene(QPointF)));
                float x=xml.attributes().value("x").toString().toFloat();
                float y=xml.attributes().value("y").toString().toFloat();
                int angle=xml.attributes().value("rot").toString().toInt();
                int i=0;
                QList<GraphicsPillarItem*> listPillar;
                while(!(xml.isEndElement()&&xml.name()=="GroupObject"))
                {
                    if(xml.isStartElement()&&xml.name()=="Object")
                    {
                        switch(xml.attributes().value("type").toString().toInt())
                        {
                            case GraphicsPillarItem::Type:{
                                GraphicsPillarItem *pillar=new GraphicsPillarItem(this->MenuItem);
                                this->loadPillar(&xml,pillar);
                                listPillar.append(pillar);
                                break;
                            }
                            case GraphicsWicketItem::Type:{
                                while(!(xml.isEndElement()&&xml.name()=="Object"))
                                {
                                    if(xml.isStartElement()&&xml.name()=="Width")
                                        this->widthGroup=xml.attributes().value("value").toString().toInt();
                                    xml.readNext();
                                }
                                if(this->group->types().isEmpty())
                                    this->AppendItem(ITEM_WICKET,QPointF(0,0));
                                else this->group->addGroup(GroupItem::ITEM_WICKET,QString::number(this->widthGroup),
                                                           this->MenuItem,this->pDiagramScene);
                                break;
                            }
                            case GraphicsGate1Item::Type:{
                                while(!(xml.isEndElement()&&xml.name()=="Object"))
                                {
                                    if(xml.isStartElement()&&xml.name()=="Width")
                                        this->widthGroup=xml.attributes().value("value").toString().toInt();
                                    xml.readNext();
                                }
                                if(this->group->types().isEmpty())
                                    this->AppendItem(ITEM_GATE_A,QPointF(0,0));
                                else this->group->addGroup(GroupItem::ITEM_GATE1,QString::number(this->widthGroup),
                                                           this->MenuItem,this->pDiagramScene);
                                break;
                            }
                            case GraphicsGate2Item::Type:{
                                while(!(xml.isEndElement()&&xml.name()=="Object"))
                                {
                                    if(xml.isStartElement()&&xml.name()=="Width")
                                        this->widthGroup=xml.attributes().value("value").toString().toInt();
                                    xml.readNext();
                                }
                                if(this->group->types().isEmpty())
                                    this->AppendItem(ITEM_GATE_B,QPointF(0,0));
                                else this->group->addGroup(GroupItem::ITEM_GATE2,QString::number(this->widthGroup),
                                                           this->MenuItem,this->pDiagramScene);
                                break;
                            }
                            default:break;
                        }
                        i++;
                    }
                    xml.readNext();
                }
                this->group->setPos(QPointF(x,y));
                this->group->setRotate(angle);
                for(int i=0,j=0;i<this->group->items().count();i+=2,j++)
                {
                    GraphicsPillarItem *p1=qgraphicsitem_cast<GraphicsPillarItem*>(listPillar.at(j));
                    GraphicsPillarItem *p2=qgraphicsitem_cast<GraphicsPillarItem*>(this->group->items().at(i));
                    p2->setGraphicsPillarItem(p1);
                }
               // this->listGroup.append(group);
            }
        }
        xml.readNext();
    }
    foreach(QGraphicsItem *item,this->objectBackUp)
    {
        bool isGroup=false;
        foreach(GroupItem *group,this->listGroup)
            if(group->isItem(item))
            {
                QPointF pos=group->pos();
                group->clearBackUp();
                group->setPos(pos);
                isGroup=true;
                break;
            }
        if(isGroup)
            continue;
        GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
        QPointF pos=pillar->pos();
        pillar->clearBackUp();
        pillar->setPosition(pos);
    }
    return true;*/
}

void DiagramView::PrintDiagram()
{
    if(this->pDiagramScene->items().isEmpty())
    {
        QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),
                           QString::fromLocal8Bit("Необходимо построить чертеж, чтобы расспечатать!"));
        return;
    }
    this->pDiagramScene->setBackgroundBrush(QBrush(Qt::lightGray, Qt::NoBrush));
    this->title.show();
    this->pDiagramScene->clearSelection();
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                QString(), "*.pdf");
    if(!fileName.isEmpty())
    {
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
    }
    this->title.hide();
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

void DiagramView::PrintContract()
{
   /*Calculate calc(this->itemSetting);
   FENCE allFence;
   COLUMN allColumn;
   QList<COLORBRICK*> colorBrick[6];
   QHash<QString,int> residueTopWall;
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
       switch(itemGraphics->type())
       {
            case GraphicsWallItem::Type:{
                GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(itemGraphics);
                FENCE tmpFence=calc.GetCountOnFence(wall->width(),wall->height(),true);
                allFence.count_brick+=tmpFence.count_brick;
                allFence.count_brick_dob+=tmpFence.count_brick_dob;
                if(wall->isTop())
                {
                    allFence.count_cover+=tmpFence.count_cover;
                    this->AppendBrickColorPazzle(&colorBrick[2],tmpFence.count_cover,
                                                 wall->colorTop().caption);
                    int residue=wall->width()-tmpFence.count_cover*this->itemSetting->widthWallTop;
                    if(residue>(this->itemSetting->minWidthBrickR/2))
                        residueTopWall.insertMulti(wall->colorTop().caption,residue);

                }
                if(tmpFence.count_brick==0)
                    break;
                if(wall->isGirthRail())
                {
                    countGirthRail[0]=wall->width()<=this->itemSetting->minWidthGirth?countGirthRail[0]+1:
                                                                                          countGirthRail[0];
                    countGirthRail[1]=wall->width()>this->itemSetting->minWidthGirth?countGirthRail[1]+1:
                                                                                        countGirthRail[1];
                }
                if(wall->isPazzle())
                {
                    COLORBRICKWALL colorBrickW=calc.colorBrickWall(wall->width(),wall->height());
                    this->AppendBrickColorPazzle(&colorBrick[0],colorBrickW.colorBrickBigWall.at(0),
                                                 wall->colorPazzle(0).caption);
                    this->AppendBrickColorPazzle(&colorBrick[1],colorBrickW.colorBrickSmallWall.at(0),
                                                 wall->colorPazzle(0).caption);
                    this->AppendBrickColorPazzle(&colorBrick[0],colorBrickW.colorBrickBigWall.at(1),
                                                 wall->colorPazzle(1).caption);
                    this->AppendBrickColorPazzle(&colorBrick[1],colorBrickW.colorBrickSmallWall.at(1),
                                                 wall->colorPazzle(1).caption);
                }else{
                    COLORBRICKWALL colorBrickW=calc.colorListBrickWall(wall->width(),wall->height());
                    for(int i=0;i<wall->colorListRow().count();i++)
                    {
                        this->AppendBrickColorPazzle(&colorBrick[0],colorBrickW.colorBrickBigWall.at(i),
                                                     wall->colorRow(i).caption);
                        this->AppendBrickColorPazzle(&colorBrick[1],colorBrickW.colorBrickSmallWall.at(i),
                                                     wall->colorRow(i).caption);
                    }
                }
                break;
            }
            case GraphicsPillarItem::Type:{
                GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(itemGraphics);
                int side[]={pillar->heightSide(0),pillar->heightSide(1),pillar->heightSide(2),
                            pillar->heightSide(3)};
                int insert[]={pillar->heightSide(0),0,pillar->heightSide(1),0,pillar->heightSide(2),0,
                              pillar->heightSide(3),0};
                COLUMN tmpColumn=calc.GetCountOnColumn(pillar->height(),insert,4);
                allColumn.count_brick_angle+=tmpColumn.count_brick_angle;
                allColumn.count_brick_angle_1+=tmpColumn.count_brick_angle_1;
                allColumn.count_brick_angle_2+=tmpColumn.count_brick_angle_2;
                allColumn.count_brick_angle_3+=tmpColumn.count_brick_angle_3;
                allColumn.count_brick_angle_4+=tmpColumn.count_brick_angle_4;
                if(tmpColumn.count_brick_angle+tmpColumn.count_brick_angle_1+tmpColumn.count_brick_angle_2+
                   tmpColumn.count_brick_angle_3+tmpColumn.count_brick_angle_4==0)
                    break;
                if(pillar->isBottomTypeEnable())
                    countBasePillar[pillar->isBottomType()]+=1;
                if(pillar->isTop())
                {
                    countTop+=1;
                    this->AppendBrickColorPazzle(&colorBrick[3],1,pillar->topColor().caption);
                }
                if(pillar->isPazzle())
                {
                    COLORBRICKPILLAR colorBrickPillar=calc.colorBrickPillar(pillar->height(),side);
                    this->AppendBrickColorPazzle(&colorBrick[4],colorBrickPillar.colorBrickBigWall.at(0),
                                                 pillar->colorPazzle(0).caption);
                    this->AppendBrickColorPazzle(&colorBrick[5],colorBrickPillar.colorBrickSmallWall.at(0),
                                                 pillar->colorPazzle(0).caption);
                    this->AppendBrickColorPazzle(&colorBrick[4],colorBrickPillar.colorBrickBigWall.at(1),
                                                 pillar->colorPazzle(1).caption);
                    this->AppendBrickColorPazzle(&colorBrick[5],colorBrickPillar.colorBrickSmallWall.at(1),
                                                 pillar->colorPazzle(1).caption);
                }else{
                    COLORBRICKPILLAR colorBrickPillar=calc.colorListBrickPillar(pillar->height(),side);
                    for(int i=0;i<pillar->colorListRow().count();i++)
                    {
                        this->AppendBrickColorPazzle(&colorBrick[4],colorBrickPillar.colorBrickBigWall.at(i),
                                                     pillar->colorRow(i).caption);
                        this->AppendBrickColorPazzle(&colorBrick[5],colorBrickPillar.colorBrickSmallWall.at(i),
                                                     pillar->colorRow(i).caption);
                    }
                }
                break;
            }
            default:break;
       }
   }
    QString expColorBrick[6];
    foreach(COLORBRICK *color,colorBrick[2])
    {
        int widthTopWall=0;
        foreach(int i,residueTopWall.values(color->namedColor))
            widthTopWall+=i;
        allFence.count_cover+=calc.coverWall(widthTopWall);
        this->AppendBrickColorPazzle(&colorBrick[2],calc.coverWall(widthTopWall),color->namedColor);
    }
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


void DiagramView::setSettingItem(SettingItem *itemSetting)
{
    this->itemSetting=itemSetting;
}

void DiagramView::closeProperties(SettingItem::TYPEITEM itemType,bool all)
{
    Calculate calc(this->itemSetting);
    if(itemType==SettingItem::ITEM_PILLAR)
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
    }/*
    if(itemType==SettingItem::ITEM_WALL)
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
                changeWall->setGraphicsWallItem(wall);
                f=calc.GetCountOnFence(changeWall->width(),changeWall->height(),false);
                changeWall->setText(QString(QString::number(f.count_brick)+" | "+QString::number(f.count_brick_dob)));
            }
        }
    }*/
}

void DiagramView::collidingGroup(QPointF point)
{
    if(this->pDiagramScene->selectedItems().isEmpty())
        return;
    GroupItem *moveGroup=new GroupItem();
    QGraphicsItem *item=this->pDiagramScene->selectedItems().at(0);
    this->pDiagramScene->clearSelection();
    foreach(GroupItem *group,this->listGroup)
        if(group->isItem(item))
        {
            moveGroup=group;
            break;
        }
    if(moveGroup->types().isEmpty())
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
        if(!coliding->types().isEmpty())
            break;
    }
    if(coliding->types().isEmpty())
        return;
    if(coliding->types().count()>4 || moveGroup->types().count()>1)
        return;
    coliding->addGroup(moveGroup,this->MenuItem,this->pDiagramScene);
    coliding->setPos(point);
    foreach(QGraphicsItem *item,moveGroup->items())
        this->pDiagramScene->removeItem(item);
    this->listGroup.removeAt(this->listGroup.indexOf(moveGroup));
    while(true)
    {
        int indexA=this->objectBackUp.indexOf(moveGroup->items().at(0));
        if(indexA!=-1)
            this->objectBackUp.removeAt(indexA);
        if(indexA==-1)
            break;

    }
    delete moveGroup;
}
/*----------------------------------------protected--------------------------------------------------------*/

void DiagramView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    this->keyPressA=false;
    this->mousePrees=true;
    QApplication::setOverrideCursor(Qt::PointingHandCursor);
    if(this->typeITEM==SettingItem::ITEM_PILLAR)
        this->AppendItem(SettingItem::ITEM_PILLAR,this->mapToScene(event->pos()));
    if(this->typeITEM==SettingItem::ITEM_WALL)
    {
        this->lineWall=new QGraphicsLineItem(QLineF(this->mapToScene(event->pos()),this->mapToScene(event->pos())));
        this->lineWall->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        this->lineWall->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->pDiagramScene->addItem(this->lineWall);
        this->pDiagramScene->clearSelection();
    }
    if(this->typeITEM==SettingItem::ITEM_WICKET)
        this->AppendItem(SettingItem::ITEM_WICKET,this->mapToScene(event->pos()));
    if(this->typeITEM==SettingItem::ITEM_GATE_A)
        this->AppendItem(SettingItem::ITEM_GATE_A,this->mapToScene(event->pos()));
    if(this->typeITEM==SettingItem::ITEM_GATE_B)
        this->AppendItem(SettingItem::ITEM_GATE_B,this->mapToScene(event->pos()));
    if(this->typeITEM==SettingItem::ITEM_FILLING)
    {
        this->lineFilling=new QGraphicsLineItem(QLineF(this->mapToScene(event->pos()),this->mapToScene(event->pos())));
        this->lineFilling->setPen(QPen(Qt::green, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        this->lineFilling->setFlag(QGraphicsItem::ItemIsSelectable,true);
        this->pDiagramScene->addItem(this->lineFilling);
        this->pDiagramScene->clearSelection();
    }
    if(this->typeITEM==SettingItem::ITEM_LINE)
    {
        QGraphicsEllipseItem *ellipse=new QGraphicsEllipseItem();
        ellipse->setBrush(QBrush(Qt::blue));
        ellipse->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        ellipse->setRect(0,0,5,5);
        ellipse->setPos(this->mapToScene(event->pos()));
        if(this->linePoint1==NULL)
            this->linePoint1=ellipse;
        else this->linePoint2=ellipse;
        this->pDiagramScene->addItem(ellipse);
    }
    QGraphicsPolygonItem *p=new QGraphicsPolygonItem();
    QPolygonF a;
    a<<this->mapToScene(event->pos());
    p->setPolygon(a);
    if(this->typeITEM==SettingItem::ITEM_NONE && this->pDiagramScene->collidingItems(p).isEmpty())
    {
        this->RectA=new RectAllocation();
        this->RectA->setPosArea(this->mapToScene(event->pos()));
        this->pDiagramScene->addItem(this->RectA);
    }
    QGraphicsView::mousePressEvent(event);
}

void DiagramView::mouseMoveEvent(QMouseEvent *event)
{
    if(this->mousePrees && !this->lock)
    {
        emit this->itemMoveScene(this->mapToScene(event->pos()));
        this->collidingGroup(this->mapToScene(event->pos()));
    }
    if(this->typeITEM==SettingItem::ITEM_WALL)
        if(this->lineWall!=NULL)
            this->lineWall->setLine(QLineF(this->lineWall->line().p1(),this->mapToScene(event->pos())));
    if(this->typeITEM==SettingItem::ITEM_FILLING)
        if(this->lineFilling!=NULL)
            this->lineFilling->setLine(QLineF(this->lineFilling->line().p1(),this->mapToScene(event->pos())));
    if(this->RectA!=NULL)
        this->RectA->setArea(this->RectA->posArea(),this->mapToScene(event->pos()));
    QGraphicsView::mouseMoveEvent(event);
}

void DiagramView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    if(!this->pDiagramScene->selectedItems().isEmpty())
        if(this->pDiagramScene->selectedItems().at(0)->type()==GraphicsPillarItem::Type)
        {
            this->objectBackUp.append(this->pDiagramScene->selectedItems().at(0));
        }
    emit this->mouseRelease();
    this->mousePrees=false;
    if(this->typeITEM==SettingItem::ITEM_WALL)
    {
        this->lineWall->setLine(QLineF(this->lineWall->line().p1(),this->mapToScene(event->pos())));
        this->AppendItem(SettingItem::ITEM_WALL,QPointF(0,0));
    }
    if(this->typeITEM==SettingItem::ITEM_FILLING)
    {
        this->lineFilling->setLine(QLineF(this->lineFilling->line().p1(),this->mapToScene(event->pos())));
        Interval *setIntervalWindow=new Interval(this);
        connect(setIntervalWindow,SIGNAL(setInterval(float,bool)),this,SLOT(setInterval(float,bool)));
        setIntervalWindow->show();
    }
    if(this->typeITEM==SettingItem::ITEM_LINE)
    {
        if(this->linePoint1!=NULL && this->linePoint2!=NULL)
        {
            this->AppendItem(SettingItem::ITEM_LINE,QPointF(0,0));
            this->typeITEM=SettingItem::ITEM_NONE;
        }
    }else
        if(this->typeITEM!=SettingItem::ITEM_PILLAR && this->typeITEM!=SettingItem::ITEM_WALL)
            this->typeITEM=SettingItem::ITEM_NONE;
    if(this->RectA!=NULL)
    {
        QList<QGraphicsItem*> list=this->pDiagramScene->collidingItems(this->RectA);
        foreach(QGraphicsItem *item,list)
            item->setSelected(true);
        this->pDiagramScene->removeItem(this->RectA);
        delete this->RectA;
        this->RectA=NULL;
    }
    QApplication::restoreOverrideCursor();
    QGraphicsView::mouseReleaseEvent(event);
}

void DiagramView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    QList<QGraphicsItem*>itemGraphics=this->pDiagramScene->items(this->mapToScene(event->pos()));
    if(!itemGraphics.isEmpty())
    {
        if(itemGraphics.at(0)->type()==GraphicsPillarItem::Type)
        {
            PropertiesPillarWindow *PillarWindow=new PropertiesPillarWindow(this);
            connect(PillarWindow,SIGNAL(closeProperties(SettingItem::TYPEITEM,bool)),
                    this,SLOT(closeProperties(SettingItem::TYPEITEM,bool)));
            this->itemGraphicsChange=itemGraphics.at(0);
            GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->itemGraphicsChange);
            PillarWindow->SetPropertiesPillar(pillar,this->itemSetting,this->Fundament);
            PillarWindow->show();
        }
        if(itemGraphics.at(0)->type()==GraphicsWallItem::Type)
        {
            this->itemGraphicsChange=itemGraphics.at(0);
            GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->itemGraphicsChange);
            QGraphicsItem *wallPillar=this->itemToScene(SettingItem::ITEM_PILLAR,wall->line().p1());
            QGraphicsItem *wallPillar2=this->itemToScene(SettingItem::ITEM_PILLAR,wall->line().p2());
            if(wallPillar!=NULL && wallPillar2!=NULL)
            {
                GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(wallPillar);
                GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(wallPillar2);
                if((pillar->height()>=this->itemSetting->heightBrickAngle)&&
                   (pillar2->height()>=this->itemSetting->heightBrickAngle))
                {
                    PropertiesWallWindow *wallWindow=new PropertiesWallWindow(this);
                    connect(wallWindow,SIGNAL(closeProperties(SettingItem::TYPEITEM,bool)),this,SLOT(closeProperties(SettingItem::TYPEITEM,bool)));
                    wallWindow->SetPropertiesWall(wall,this->itemSetting,pillar,this->Fundament);
                    wallWindow->show();
                }
            }
        }
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void DiagramView::isValidateObject()
{
    /*QList<QGraphicsItem*>itemGraphics=this->pDiagramScene->items();
    foreach(QGraphicsItem* item,itemGraphics)
    {
        if(item->type()==GraphicsWallItem::Type)
        {
            GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(item);
            QGraphicsItem *wallPillar=this->itemToScene(ITEM_PILLAR,wall->line().p1());
            QGraphicsItem *wallPillar2=this->itemToScene(ITEM_PILLAR,wall->line().p2());
            if(wallPillar!=NULL && wallPillar2!=NULL)
            {
                qDebug()<<"-----------------------------------";
                GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(wallPillar);
                GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(wallPillar2);
                if((pillar->height()>=this->itemSetting->heightBrickAngle)&&
                   (pillar2->height()>=this->itemSetting->heightBrickAngle))
                {
                    qDebug()<<"PILLAR 2: height="<<pillar2->height();
                    qDebug()<<"PILLAR 1: height="<<pillar->height();
                    for(int i=0;i<4;i++)
                        qDebug()<<"Side("<<i<<"):"<<pillar->heightSide(i);
                    if(pillar->isTop())
                        qDebug()<<"Top color:"<<pillar->topColor().caption;
                    if(pillar->isPazzle())
                        qDebug()<<"Pazzle color(1):"<<pillar->colorPazzle(0).caption<<" color(2):"<<
                                  pillar->colorPazzle(0).caption;
                    if(!pillar->colorListRow().isEmpty())
                    {
                        qDebug()<<"Count color list row:"<<pillar->countColorRow();
                        foreach(COLOR color,pillar->colorListRow())
                            qDebug()<<"Color row:"<<color.caption;
                    }
                    if(pillar->isBottomTypeEnable())
                        qDebug()<<"Bottom type:"<<pillar->isBottomType();
                    ////////////////////////////////////////////////////////////
                    qDebug()<<"WALL width:"<<wall->width()<<" height:"<<wall->height();
                    if(wall->isTop())
                        qDebug()<<"Top color:"<<wall->colorTop().caption;
                    if(wall->isPazzle())
                        qDebug()<<"Pazzle color(1):"<<wall->colorPazzle(0).caption<<" color(2):"<<
                                  wall->colorPazzle(1).caption;
                    if(!wall->colorListRow().isEmpty())
                    {
                        qDebug()<<"Count color list row:"<<wall->countColorRow();
                        foreach(COLOR color,wall->colorListRow())
                            qDebug()<<"Color row:"<<color.caption;
                    }
                    qDebug()<<wall->isDecoreid();
                }
            }
        }
    }*//////
   /*if(!itemGraphics.isEmpty())
    {
        if(itemGraphics.at(0)->type()==GraphicsPillarItem::Type)
        {
            PropertiesPillarWindow *PillarWindow=new PropertiesPillarWindow(this);
            PillarWindow->heightBrick=this->itemSetting->heightBrickAngle;
            connect(PillarWindow,SIGNAL(closeProperties(TYPEITEM,bool)),this,SLOT(closeProperties(TYPEITEM,bool)));
            this->itemGraphicsChange=itemGraphics.at(0);
            GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->itemGraphicsChange);
            PillarWindow->SetPropertiesPillar(pillar,this->itemSetting->color);
            PillarWindow->show();
        }
        if(itemGraphics.at(0)->type()==GraphicsWallItem::Type)
        {
            this->itemGraphicsChange=itemGraphics.at(0);
            GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(this->itemGraphicsChange);
            QGraphicsItem *wallPillar=this->itemToScene(ITEM_PILLAR,wall->line().p1());
            QGraphicsItem *wallPillar2=this->itemToScene(ITEM_PILLAR,wall->line().p2());
            if(wallPillar!=NULL && wallPillar2!=NULL)
            {
                GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(wallPillar);
                GraphicsPillarItem *pillar2=qgraphicsitem_cast<GraphicsPillarItem*>(wallPillar2);
                if((pillar->height()>=this->itemSetting->heightBrickAngle)&&
                   (pillar2->height()>=this->itemSetting->heightBrickAngle))
                {
                    PropertiesWallWindow *wallWindow=new PropertiesWallWindow(this);
                    connect(wallWindow,SIGNAL(closeProperties(TYPEITEM,bool)),this,SLOT(closeProperties(TYPEITEM,bool)));
                    wallWindow->SetPropertiesWall(wall,this->itemSetting,pillar);
                    wallWindow->show();
                }
            }
        }
    }*/
}

void DiagramView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete)
    {
        if(this->keyPressA)
             this->ClearScene();
        else this->Delete_Item();
        this->keyPressA=false;
    }
    if(event->key()==Qt::Key_A)
        if(event->modifiers()==Qt::ControlModifier)
        {
            foreach(QGraphicsItem* graphicsItem,this->pDiagramScene->items())
                    graphicsItem->setSelected(true);
            this->keyPressA=true;
        }
    if(event->key()==Qt::Key_Z)
        if(event->modifiers()==Qt::ControlModifier)
            this->setLastPosObject();
    /*if(event->key()==Qt::Key_1)
    {
        this->isValidateObject();
    }*/
    QGraphicsView::keyPressEvent(event);
}


void DiagramView::setLastPosObject()
{
    if(this->objectBackUp.isEmpty())
        return;
    bool itemGroup=false;
    foreach(GroupItem *group,this->listGroup)
        if(group->isItem(this->objectBackUp.last()))
        {
            group->backUp();
            itemGroup=true;
            break;
        }
    if(!itemGroup)
    {
        GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(this->objectBackUp.last());
        pillar->backUp();
    }
    this->objectBackUp.removeLast();
}


void DiagramView::setFundament(bool Fundament)
{
    this->Fundament=Fundament;
    foreach(QGraphicsItem *item,this->pDiagramScene->items())
    {
        if(item->type()==GraphicsPillarItem::Type)
        {
            GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
            if(pillar->isBottomTypeEnable())
                pillar->setBottomTypeEnable(!this->Fundament);
            continue;
        }
        if(item->type()==GraphicsWallItem::Type)
        {
            GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(item);
            if(wall->isGirthRail())
                wall->setGirthRail(!this->Fundament);
            continue;
        }
    }
}


float DiagramView::normalVector2D(QPointF vector2d)
{
    return qSqrt((vector2d.x()*vector2d.x())+(vector2d.y()*vector2d.y()));
}

/*
void DiagramView::alignmentWall(int width, GraphicsPillarItem *pillar1, GraphicsPillarItem *pillar2)
{
    float angle=::atan2(pillar1->pos().y()-pillar2->pos().y(),pillar1->pos().x()-pillar2->pos().x())/PI*180;
    angle=angle<0?angle+360:angle;
    QPointF point=this->rotatePoint(pillar1->pos(),QPointF(pillar1->pos().x()-width,pillar1->pos().y()),angle);
    pillar2->setPosition(point);
}*/

void DiagramView::alignmentSelectedWall(int width)
{
    if(this->pDiagramScene->selectedItems().isEmpty())
        return;
    foreach(GroupItem *group,this->listGroup)
        foreach(QGraphicsItem *item,this->pDiagramScene->selectedItems())
            if(group->isItem(item))
                return;
    this->alignment.alignmentAnglePillar(width,this->pDiagramScene->selectedItems());
    //this->alignment.alignmentLengthPillar(width,this->pDiagramScene->selectedItems());
}

void DiagramView::setLockingScene(bool lock)
{
    this->lock=lock;
    foreach(QGraphicsItem *itemGraphic,this->pDiagramScene->items())
        if(itemGraphic->type()==GraphicsPillarItem::Type)
            itemGraphic->setFlag(QGraphicsItem::ItemIsMovable,!this->lock);
}

bool DiagramView::locking()
{
    return this->lock;
}
