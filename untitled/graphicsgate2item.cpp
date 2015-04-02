#include "graphicsgate2item.h"

GraphicsGate2Item::GraphicsGate2Item(QMenu *menu, QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsTextItem(parent,scene)
{
    this->widthGate=0;
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->setPlainText(QString::fromLocal8Bit("Ворота\nоткатные\n\n\n0"));
    this->setPos(0,0);
    this->menu=menu;
}

GraphicsGate2Item::~GraphicsGate2Item()
{}

void GraphicsGate2Item::setText(QString text)
{
    this->setPlainText(QString::fromLocal8Bit("Ворота\nоткатные\n\n\n")+text);
    this->widthGate=text.toInt();
}

int GraphicsGate2Item::value()
{
    return this->widthGate;
}

void GraphicsGate2Item::setPosition(QPointF p1, QPointF p2)
{
    QPointF centre;
    centre.setX((p1.x()+p2.x())/2);
    centre.setY((p1.y()+p2.y())/2);
    this->setPos(this->rotatePoint(centre,QPointF(centre.x()-25,centre.y()-60),this->rotation()));
}

QPointF GraphicsGate2Item::posP1()
{
    return this->pos();
}

QPointF GraphicsGate2Item::posP2()
{
    return this->pos();
}

void GraphicsGate2Item::setRotate(int angle)
{
    this->setRotation(angle);
}

int GraphicsGate2Item::rotationGate()
{
    return this->rotation();
}

void GraphicsGate2Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    this->setSelected(true);
    this->menu->actions().at(0)->setVisible(true);
    this->menu->actions().at(1)->setVisible(true);
    this->menu->actions().at(2)->setVisible(true);
    this->menu->actions().at(3)->setVisible(true);
    this->menu->exec(event->screenPos());
}

QPointF GraphicsGate2Item::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

