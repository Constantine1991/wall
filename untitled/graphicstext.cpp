#include "graphicstext.h"
/*
GraphicsText::GraphicsText(QGraphicsItem *parent, QGraphicsScene *scene):QGraphicsTextItem(parent,scene)
{
    this->setFlag(QGraphicsItem::ItemIsMovable,true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges,true);
    this->setPlainText("0/0");
}

void GraphicsText::setLine(QGraphicsLineItem *line)
{
    this->line=line;
}

QVariant GraphicsText::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change==QGraphicsItem::ItemPositionChange)
        this->line->setLine(QLineF(this->pos(),this->line->line().p2()));
    return QGraphicsItem::itemChange(change, value);
}
*/
