#include "graphicsgate2item.h"

GraphicsGate2Item::GraphicsGate2Item(QMenu *menu, QGraphicsItem *parent, QGraphicsScene *scene)
    :QGraphicsLineItem(parent,scene)
{
    this->width=20;
    this->rotP1=0;
    this->rotP2=180;
    this->rotP3=270;
    this->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->setFlag(QGraphicsItem::ItemIsSelectable,true);
    this->mirrorLine=new QGraphicsLineItem(this);
    this->mirrorLine->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->mirrorLine->setFlag(QGraphicsItem::ItemIsSelectable,false);
    this->topLine=new QGraphicsLineItem(this);
    this->topLine->setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    this->topLine->setFlag(QGraphicsItem::ItemIsSelectable,false);
    this->text=new QGraphicsTextItem("5000",this);
    this->menu=menu;
}

GraphicsGate2Item::~GraphicsGate2Item()
{}

void GraphicsGate2Item::setText(QString text)
{
    this->text->setPlainText(text);
    this->updateText();
}

void GraphicsGate2Item::setPosition(QPointF p1, QPointF p2)
{
    QPointF point2=this->rotatePoint(p1,QPointF(p1.x()+this->width,p1.y()),this->rotP1);
    this->setLine(QLineF(p1,point2));
    this->updateText();
    point2=this->rotatePoint(p2,QPointF(p2.x()+this->width,p2.y()),this->rotP2);
    this->mirrorLine->setLine(QLineF(p2,point2));
    QPointF centreTopLine=this->rotatePoint(this->mirrorLine->line().p2(),
                                            QPointF(this->mirrorLine->line().p2().x()+10,
                                                    this->mirrorLine->line().p2().y()),this->rotP3);
    QPointF p1TopLine=this->rotatePoint(centreTopLine,QPointF(centreTopLine.x()+10,centreTopLine.y()),this->rotP1);
    QPointF p2TopLine=this->rotatePoint(centreTopLine,QPointF(centreTopLine.x()+10,centreTopLine.y()),this->rotP2);
    this->topLine->setLine(QLineF(p1TopLine,p2TopLine));
}

void GraphicsGate2Item::setRotate(int angle)
{
    this->rotP1=angle;
    this->rotP2=180+angle;
    this->rotP2=this->rotP2>360?this->rotP2-360:this->rotP2;
    this->rotP3=270+angle;
    this->rotP3=this->rotP3>360?this->rotP3-360:this->rotP3;
    this->setPosition(this->line().p1(),this->mirrorLine->line().p1());
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

QPointF GraphicsGate2Item::centre()
{
    return QPointF((this->line().p1().x()+this->line().p2().x())/2,(this->line().p1().y()+this->line().p2().y())/2);
}

void GraphicsGate2Item::updateText()
{
    QPointF p1=this->line().p1();
    QPointF p2=this->line().p2();
    float angle=::atan2(p2.y()-p1.y(),p2.x()-p1.x())/PI*180;
    angle=angle<0?angle+360:angle;
    this->text->setRotation(angle);
    this->text->setPos(this->line().p2());
}
