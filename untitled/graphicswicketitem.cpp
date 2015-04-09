#include "graphicswicketitem.h"
#include "QDebug"
GraphicsWicketItem::GraphicsWicketItem(QMenu *menuItem, QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsTextItem(parent,scene)
{
    this->widthWicket=0;
    this->rot=0;
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->setPos(0,0);
    this->setPlainText(QString::fromLocal8Bit("Калитка\n\n\n0"));
    this->menu=menuItem;
}

GraphicsWicketItem::~GraphicsWicketItem()
{
}

void GraphicsWicketItem::setText(QString text)
{
    this->setPlainText(QString::fromLocal8Bit("Калитка\n\n\n")+text);
    this->widthWicket=text.toInt();
}

int GraphicsWicketItem::value()
{
    return this->widthWicket;
}

void GraphicsWicketItem::setPosition(QPointF pos)
{
   // point=pos;
    this->setPos(this->rotatePoint(pos,QPointF(pos.x()-15,pos.y()-40),this->rotation()));
}

QPointF GraphicsWicketItem::position()
{
    return this->pos();
}

int GraphicsWicketItem::rotationWicket()
{
    return this->rotation();
}

void GraphicsWicketItem::setRotate(int angle)
{
    this->setRotation(angle);
    this->setPos(this->rotatePoint(this->centre(),this->pos(),angle));
}

void GraphicsWicketItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    this->setSelected(true);
    this->menu->actions().at(0)->setVisible(true);
    this->menu->actions().at(1)->setVisible(true);
    this->menu->actions().at(2)->setVisible(true);
    this->menu->actions().at(3)->setVisible(true);
    this->menu->exec(event->screenPos());
}

QPointF GraphicsWicketItem::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

QPointF GraphicsWicketItem::centre()
{
    int x=this->pos().x()+(this->boundingRect().width()/2*TableAngle[0][(int)this->rotation()/45]);
    int y=this->pos().y()+(this->boundingRect().height()/2*TableAngle[1][(int)this->rotation()/45]);
    return QPointF(x,y);
}
