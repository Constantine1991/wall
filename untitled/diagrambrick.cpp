#include "diagramBrick.h"

DiagramBrick::DiagramBrick()
{
    this->Brick=new QGraphicsRectItem();
    this->Brick->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
}

DiagramBrick::~DiagramBrick()
{
    delete this->Brick;
}

void DiagramBrick::setSize(int width, int height)
{
    this->Brick->setRect(0,0,width,height);
}

void DiagramBrick::setPos(float x, float y)
{
    this->Brick->setPos(x,y);
}

void DiagramBrick::setPos(QPointF pos)
{
    this->Brick->setPos(pos);
}

void DiagramBrick::setBrush(QBrush brush)
{
    this->Brick->setBrush(brush);
}

QGraphicsRectItem *DiagramBrick::brick() const
{
    return this->Brick;
}
