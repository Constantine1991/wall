#include "graphicswicketitem.h"

GraphicsWicketItem::GraphicsWicketItem(QMenu *menuItem, QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsLineItem(parent,scene)
{
    this->widthWicket=0;
    this->width=30;
    this->rot=130;
    this->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    QPointF p2=this->rotatePoint(QPointF(0,0),QPointF(0,this->width),this->rot);
    this->setLine(QLineF(QPointF(0,0),p2));
    this->text=new QGraphicsTextItem("0",this);
    this->text->setPos(50,0);
    this->menu=menuItem;
}

GraphicsWicketItem::~GraphicsWicketItem()
{
}

void GraphicsWicketItem::setText(QString text)
{
    this->text->setPlainText(text);
    this->widthWicket=text.toInt();
    this->updateText();
}

int GraphicsWicketItem::value()
{
    return this->widthWicket;
}

void GraphicsWicketItem::setPosition(QPointF pos)
{
    QPointF p2=this->rotatePoint(pos,QPointF(pos.x()+this->width,pos.y()),this->rot);
    this->setLine(QLineF(pos,p2));
    this->updateText();
}

QPointF GraphicsWicketItem::position()
{
    return this->line().p1();
}

int GraphicsWicketItem::rotationWicket()
{
    return this->rot-130;
}

void GraphicsWicketItem::setRotate(int angle)
{
    this->rot=130+angle;
    this->setPosition(this->line().p1());
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
    return QPointF((this->line().p1().x()+this->line().p2().x())/2,(this->line().p1().y()+this->line().p2().y())/2);
}

void GraphicsWicketItem::updateText()
{
    QPointF p1=this->line().p1();
    QPointF p2=this->line().p2();
    float angle=::atan2(p1.y()-p2.y(),p1.x()-p2.x())/PI*180;
    angle=angle<0?angle+360:angle;
    this->text->setRotation(angle);
    this->text->setPos(this->line().p2());
}
