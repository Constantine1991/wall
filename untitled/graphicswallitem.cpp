#include "graphicswallitem.h"
#include "QDebug"
GraphicsWallItem::GraphicsWallItem(QMenu *menuItem, QGraphicsItem *parent, QGraphicsScene *scene):QGraphicsLineItem(parent,scene)
{
    this->setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    this->itemText=new QGraphicsTextItem("0|0",this);
    this->menuItem=menuItem;
    this->wallWidth=0;
    this->wallHeight=0;
    this->wallPazzle=false;
    this->wallDecoreid=0;
    this->wallGirthRail=false;
    this->wallTop=false;
}

void GraphicsWallItem::setText(QString caption)
{
    this->itemText->setPlainText(caption);
    this->updatePosText();
}

void GraphicsWallItem::setLinePoint(QPointF p1, QPointF p2)
{
    this->setLine(QLineF(p1,p2));
    this->updatePosText();
}

QPointF GraphicsWallItem::posP1()
{
    return this->line().p1();
}

QPointF GraphicsWallItem::posP2()
{
    return this->line().p2();
}

void GraphicsWallItem::updatePosText()
{
    QPointF p1=this->line().p1();
    QPointF p2=this->line().p2();
    float angle=::atan2(p1.y()-p2.y(),p1.x()-p2.x())/PI*180;
    angle=angle<0?angle+360:angle;
    QPointF centreLine=this->centre();
    this->itemText->setRotation(angle+180);
    this->itemText->setPos(centreLine);
}

QPointF GraphicsWallItem::centre()
{
    return QPointF((this->line().p1().x()+this->line().p2().x())/2,(this->line().p1().y()+this->line().p2().y())/2);
}

void GraphicsWallItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    this->setSelected(true);
    this->menuItem->actions().at(0)->setVisible(false);
    this->menuItem->actions().at(1)->setVisible(false);
    this->menuItem->actions().at(2)->setVisible(false);
    this->menuItem->actions().at(3)->setVisible(false);
    this->menuItem->exec(event->screenPos());
}

void GraphicsWallItem::setWidth(int width)
{
    this->wallWidth=width;
}

int GraphicsWallItem::width()
{
    return this->wallWidth;
}

void GraphicsWallItem::setHeight(int height)
{
    this->wallHeight=height;
}

int GraphicsWallItem::height()
{
    return this->wallHeight;
}

void GraphicsWallItem::setTop(bool top)
{
    this->wallTop=top;
}

bool GraphicsWallItem::isTop()
{
    return this->wallTop;
}

void GraphicsWallItem::setColorTop(QString color)
{
    this->wallColorTop=color;
}

QString GraphicsWallItem::colorTop()
{
    return this->wallColorTop;
}

void GraphicsWallItem::setPazzle(bool pazzle)
{
    this->wallPazzle=pazzle;
}

bool GraphicsWallItem::isPazzle()
{
    return this->wallPazzle;
}

void GraphicsWallItem::setColorPazzle(int pazzle, QString color)
{
    this->wallColorPazzle[pazzle]=color;
}

QString GraphicsWallItem::colorPazzle(int pazzle)
{
    return this->wallColorPazzle[pazzle];
}

void GraphicsWallItem::addColorRow(QString color)
{
    this->wallColorRow.append(color);
}

void GraphicsWallItem::clearColorRow()
{
    this->wallColorRow.clear();
}

void GraphicsWallItem::setColorRow(int row, QString color)
{
    this->wallColorRow.removeAt(row-1);
    this->wallColorRow.insert(row-1,color);
}

void GraphicsWallItem::setColorRowList(QList<QString> colorList)
{
    this->clearColorRow();
    this->wallColorRow=colorList;
}

QString GraphicsWallItem::colorRow(int row)
{
    return this->wallColorRow.at(row);
}

QList<QString> GraphicsWallItem::colorListRow()
{
    return this->wallColorRow;
}

bool GraphicsWallItem::isEmptyColorRow()
{
    return this->wallColorRow.isEmpty();
}

int GraphicsWallItem::countColorRow()
{
    return this->wallColorRow.count();
}

void GraphicsWallItem::setDecoreid(int decoreid)
{
    this->wallDecoreid=decoreid;
}

int GraphicsWallItem::isDecoreid()
{
    return this->wallDecoreid;
}

void GraphicsWallItem::setColorDecoreid(QString color)
{
   this->wallColorDecoreid=color;
}

QString GraphicsWallItem::colorDecoreid()
{
    return this->wallColorDecoreid;
}

void GraphicsWallItem::setGirthRail(bool girth)
{
    this->wallGirthRail=girth;
}

bool GraphicsWallItem::isGirthRail()
{
    return this->wallGirthRail;
}

void GraphicsWallItem::setGraphicsWallItem(GraphicsWallItem *wall)
{
    this->setHeight(wall->height());
    //this->setWidth(wall->width());
    this->setTop(wall->isTop());
    if(this->isTop())
        this->setColorTop(wall->colorTop());
    this->setPazzle(wall->isPazzle());
    if(this->isPazzle())
    {
        this->setColorPazzle(0,wall->colorPazzle(0));
        this->setColorPazzle(1,wall->colorPazzle(1));
    }
    this->setColorRowList(wall->colorListRow());
    this->setDecoreid(wall->isDecoreid());
    if(this->isDecoreid()!=0)
        this->setColorDecoreid(wall->colorDecoreid());
    this->setGirthRail(wall->isGirthRail());
}
