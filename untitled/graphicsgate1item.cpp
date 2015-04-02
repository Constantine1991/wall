#include "graphicsgate1item.h"

GraphicsGate1Item::GraphicsGate1Item(QMenu *menu, QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsTextItem(parent,scene)
{
    this->menu=menu;
    this->widthGate=0;
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->setPlainText(QString::fromLocal8Bit("Ворота\nраспашные\n\n\n0"));
    this->setPos(0,0);
}

GraphicsGate1Item::~GraphicsGate1Item()
{
}

void GraphicsGate1Item::setText(QString text)
{
    this->setPlainText(QString::fromLocal8Bit("Ворота\nраспашные\n\n\n")+text);
    this->widthGate=text.toInt();
}

int GraphicsGate1Item::value()
{
    return this->widthGate;
}

void GraphicsGate1Item::setPosition(QPointF p1, QPointF p2)
{
    QPointF centre;
    centre.setX((p1.x()+p2.x())/2);
    centre.setY((p1.y()+p2.y())/2);
    this->setPos(this->rotatePoint(centre,QPointF(centre.x()-30,centre.y()-60),this->rotation()));
}

QPointF GraphicsGate1Item::posP1()
{
    return this->pos();
}

QPointF GraphicsGate1Item::posP2()
{
    return this->pos();
}

void GraphicsGate1Item::setRotate(int angle)
{
    this->setRotation(angle);
}

int GraphicsGate1Item::rotationGate()
{
    return this->rotation();
}

void GraphicsGate1Item::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    this->setSelected(true);
    this->menu->actions().at(0)->setVisible(true);
    this->menu->actions().at(1)->setVisible(true);
    this->menu->actions().at(2)->setVisible(true);
    this->menu->actions().at(3)->setVisible(true);
    this->menu->exec(event->screenPos());
}

QPointF GraphicsGate1Item::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

