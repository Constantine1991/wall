#include "graphicspillaritem.h"
#include "QDebug"

GraphicsPillarItem::GraphicsPillarItem(QMenu *menuItem, QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsEllipseItem(parent, scene)
{
    this->isBackUp=false;
    this->mouseRelease=false;
    this->enabledBackUp=false;
    this->itemText=new QGraphicsTextItem();
    this->itemText->setPos(0,0);
    this->setBrush(QBrush(Qt::white));
    this->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->setText("0|0");
    this->setRect(0,0,16,16);
    this->itemText->setPos(8-this->itemText->boundingRect().width()/2,0-this->itemText->boundingRect().height());
    this->itemText->setParentItem(this);
    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    this->menuItem=menuItem;
    this->heightPillar=0;
    this->topPillar=false;
    this->heightSidePillar[0]=0;
    this->heightSidePillar[2]=0;
    this->heightSidePillar[3]=0;
    this->heightSidePillar[4]=0;
    this->bottomTypePillar=GraphicsPillarItem::BOTTOM_DEAF;
    this->pazzlePillar=false;
    this->bottomTypeEnablePillar=false;
}

GraphicsPillarItem::~GraphicsPillarItem()
{
    this->listWall.clear();
}

void GraphicsPillarItem::setText(QString caption)
{
    this->itemText->setPlainText(caption);
    this->textPillar=caption;
}

QString GraphicsPillarItem::text()
{
    return this->textPillar;
}

void GraphicsPillarItem::addWall(GraphicsWallItem *lineWall, bool point)
{
    this->listWall.insert(lineWall,point);
}

void GraphicsPillarItem::removeWall(GraphicsWallItem *item)
{
    this->listWall.remove(item);
}

QVariant GraphicsPillarItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change==QGraphicsItem::ItemPositionChange || change==QGraphicsItem::ItemRotationChange)
    {
        if(this->mouseRelease && this->enabledBackUp && !this->isBackUp)
        {
            this->lastPos.append(this->pos());
            this->mouseRelease=false;
        }
        foreach(GraphicsWallItem *changeline,this->listWall.keys())
        {
            if(this->listWall.value(changeline))
                changeline->setLinePoint(this->centre(),changeline->line().p2());
            else changeline->setLinePoint(changeline->line().p1(),this->centre());
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

void GraphicsPillarItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    this->setSelected(true);
    this->menuItem->actions().at(0)->setVisible(false);
    this->menuItem->actions().at(1)->setVisible(false);
    this->menuItem->actions().at(2)->setVisible(false);
    this->menuItem->actions().at(3)->setVisible(false);
    this->menuItem->exec(event->screenPos());
}

void GraphicsPillarItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    this->mouseRelease=true;
    QGraphicsItem::mouseReleaseEvent(event);
}

void GraphicsPillarItem::setHeight(int height)
{
    this->heightPillar=height;
}

int GraphicsPillarItem::height()
{
    return this->heightPillar;
}

QPointF GraphicsPillarItem::centre()
{
    int x=this->pos().x()+(this->boundingRect().width()/2*TableAngle[0][(int)this->rotation()/45]);
    int y=this->pos().y()+(this->boundingRect().height()/2*TableAngle[1][(int)this->rotation()/45]);
    return QPointF(x,y);
}

void GraphicsPillarItem::setHeightSide(SIDETYPE sideType, int height)
{
    this->heightSidePillar[(int)sideType]=height;
}

void GraphicsPillarItem::setHeightSide(int side, int height)
{
    this->heightSidePillar[side]=height;
}

void GraphicsPillarItem::setBottomTypeEnable(bool enable)
{
    this->bottomTypeEnablePillar=enable;
}

int GraphicsPillarItem::heightSide(SIDETYPE sideType)
{
    return this->heightSidePillar[(int)sideType];
}

int GraphicsPillarItem::heightSide(int side)
{
     return this->heightSidePillar[side];
}

int GraphicsPillarItem::isBottomType()
{
    int front=this->heightSide(GraphicsPillarItem::SIDE_FRONT)>0?1:0;
    int back=this->heightSide(GraphicsPillarItem::SIDE_BACK)>0?1:0;
    int left=this->heightSide(GraphicsPillarItem::SIDE_LIFT)>0?1:0;
    int right=this->heightSide(GraphicsPillarItem::SIDE_RIGHT)>0?1:0;
    int typeSide=front+back+left+right;
    switch(typeSide)
    {
        case 0:{
            this->bottomTypePillar=GraphicsPillarItem::BOTTOM_DEAF;
            break;
        }
        case 1:{
            this->bottomTypePillar=GraphicsPillarItem::BOTTOM_BEGINEND;
            break;
        }
        case 2:{
            if(((front+back)==2)||((left+right==2)))
            {
                this->bottomTypePillar=GraphicsPillarItem::BOTTOM_PASSAGE;
                break;
            }
            if(((front+left)==2)||((front+right)==2)||((back+left)==2)||((back+right)==2))
            {
                this->bottomTypePillar=GraphicsPillarItem::BOTTOM_ANGLETWO;
                break;
            }
        }
        case 3:{
            this->bottomTypePillar=GraphicsPillarItem::BOTTOM_ANGLETHREE;
            break;
        }
        default:{
            this->bottomTypePillar=GraphicsPillarItem::BOTTOM_DEAF;
            break;
        }
    }
    return (int)this->bottomTypePillar;
}

bool GraphicsPillarItem::isBottomTypeEnable()
{
    return this->bottomTypeEnablePillar;
}

void GraphicsPillarItem::clearColorRow()
{
    this->colorRowPillar.clear();
}

void GraphicsPillarItem::addColorRow(COLOR color)
{
    this->colorRowPillar.append(color);
}

void GraphicsPillarItem::setCountColorRow(int count)
{
    if(this->colorRowPillar.isEmpty())
        for(int i=0;i<count;i++)
            this->colorRowPillar.append(COLOR());
     else{
        if(this->colorRowPillar.count()<count)
            for(int i=this->colorRowPillar.count()-1;i<count;i++)
                this->colorRowPillar.append(COLOR());
        else
            if(this->colorRowPillar.count()>count)
                for(int i=this->colorRowPillar.count()-1;i<count-1;i--)
                    this->colorRowPillar.removeLast();
    }
}

void GraphicsPillarItem::setColorRow(int row, COLOR color)
{
    this->colorRowPillar.removeAt(row-1);
    this->colorRowPillar.insert(row-1,color);
}

void GraphicsPillarItem::setColorRow(QList<COLOR> color)
{
    this->colorRowPillar.clear();
    this->colorRowPillar.append(color);
}

int GraphicsPillarItem::countColorRow()
{
    return this->colorRowPillar.count();
}

COLOR GraphicsPillarItem::colorRow(int row)
{
    return this->colorRowPillar.at(row);
}

QList<COLOR> GraphicsPillarItem::colorListRow()
{
    return this->colorRowPillar;
}

void GraphicsPillarItem::setTop(bool top)
{
    this->topPillar=top;
}

void GraphicsPillarItem::setTopColor(COLOR color)
{
    if(this->topPillar)
        this->colorTopPillar=color;
}

bool GraphicsPillarItem::isTop()
{
    return this->topPillar;
}

COLOR GraphicsPillarItem::topColor()
{
    return this->colorTopPillar;
}

void GraphicsPillarItem::setPazzle(bool pazzle)
{
    this->pazzlePillar=pazzle;
}

void GraphicsPillarItem::setColorPazzle(int number, COLOR color)
{
    if(this->pazzlePillar)
        this->colorPazzlePillar[number]=color;
}

bool GraphicsPillarItem::isPazzle()
{
    return this->pazzlePillar;
}

COLOR GraphicsPillarItem::colorPazzle(int number)
{
    return this->colorPazzlePillar[number];
}

QMenu *GraphicsPillarItem::menuitem()
{
    return this->menuItem;
}

void GraphicsPillarItem::backUp()
{
    if(this->lastPos.isEmpty())
        return;
    this->isBackUp=true;
    this->setPos(this->lastPos.last());
    if(this->lastPos.count()>1)
        this->lastPos.removeLast();
    this->isBackUp=false;
    foreach(GraphicsWallItem *changeline,this->listWall.keys())
    {
        if(this->listWall.value(changeline))
            changeline->setLinePoint(this->centre(),changeline->line().p2());
        else changeline->setLinePoint(changeline->line().p1(),this->centre());
    }
}

void GraphicsPillarItem::setEnabledBackUp(bool value)
{
    this->enabledBackUp=value;
}

void GraphicsPillarItem::setPosition(QPointF pos)
{
    if(this->enabledBackUp)
    {
        this->lastPos.append(pos);
    }
    this->setPos(pos);
}

void GraphicsPillarItem::setGraphicsPillarItem(GraphicsPillarItem *graphicsItem)
{
    this->setHeight(graphicsItem->height());
    for(int i=0;i<4;i++)
        this->setHeightSide(i,graphicsItem->heightSide(i));
    this->setBottomTypeEnable(graphicsItem->isBottomTypeEnable());
    this->setText(graphicsItem->text());
    this->setTop(graphicsItem->isTop());
    this->setPazzle(graphicsItem->isPazzle());
    if(this->isTop())
        this->setTopColor(graphicsItem->topColor());
    if(this->isPazzle())
    {
        this->setColorPazzle(0,graphicsItem->colorPazzle(0));
        this->setColorPazzle(1,graphicsItem->colorPazzle(1));
    }
    else this->setColorRow(graphicsItem->colorListRow());
}
