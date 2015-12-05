#include "alignment.h"
#include "QDebug"

float Alignment::normalVector2D(QPointF vector2d)
{
    return qSqrt((vector2d.x()*vector2d.x())+(vector2d.y()*vector2d.y()));
}

QPointF Alignment::rotatePoint(QPointF center, QPointF point,float angle)
{
    return QPoint(center.x()+(point.x()-center.x())*::cos(angle*PI/180)-(point.y()-center.y())*::sin(angle*PI/180),
                  center.y()+(point.y()-center.y())*::cos(angle*PI/180)+(point.x()-center.x())*::sin(angle*PI/180));
}

/////////////////////////

void Alignment::setScene(QGraphicsScene *scene)
{
    this->scene=scene;
}

void Alignment::alignmentAnglePillar(int angle,QList<QGraphicsItem *> listItem)
{
    if(listItem.isEmpty())
        return;
    angle+=180;
    QList<GraphicsPillarItem *> listPillar;
//    foreach(QGraphicsItem *item,listItem)
//        if(item->type()==GraphicsWallItem::Type)
//            listItem.removeAt(listItem.indexOf(item));
//    for(int i=0;i<listItem.count()-1;i++)
//        for(int j=i+1;j<listItem.count();j++)
//            if(this->normalVector2D(listItem.at(i)->pos())>this->normalVector2D(listItem.at(j)->pos()))
//                listItem.move(j,i);
    int step=0;
    ///Нахождение начального и конечного столба
    foreach(QGraphicsItem *item,listItem)
    {
        if(item->type()==GraphicsPillarItem::Type)
        {
            step++;
            GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
            if(pillar->itemsWall().count()==1)
                listPillar.append(pillar);
            if(pillar->itemsWall().count()==2)
                foreach(GraphicsWallItem *wall,pillar->itemsWall())
                {
                    int selectedItem=0;
                    foreach(QGraphicsItem *selected,wall->collidingItems())
                        if(selected->isSelected() && selected->type()==GraphicsPillarItem::Type)
                            selectedItem++;
                    if(selectedItem==1)
                        listPillar.append(pillar);
                }
        }
    }
    //// Какой столб ближе к ночалу координат
    if(this->normalVector2D(listPillar.first()->centre())>this->normalVector2D(listPillar.last()->centre()))
    {
        listPillar.insert(0,listPillar.last());
        listPillar.removeLast();
    }
    QList<float> distance;
    //// Вычеление порядка слолбов(какой за каким расположен) и просчет дистанции между столбами
    for(int i=0;i<step;i++)
    {
        QList<GraphicsWallItem*> listWall=listPillar.at(i)->itemsWall();
        foreach(GraphicsWallItem *wall,listWall)
            foreach(QGraphicsItem *item,wall->collidingItems())
                if(item->isSelected() && item->type()==GraphicsPillarItem::Type)
                {
                    GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
                    bool newPillar=true;
                    foreach(GraphicsPillarItem *itemPillar,listPillar)
                        if(itemPillar->centre()==pillar->centre())
                        {
                            newPillar=false;
                            break;
                        }
                    if(newPillar)
                    {
                        distance.append(this->normalVector2D(QPointF(pillar->pos().x()-listPillar.at(i)->pos().x(),
                                                                     pillar->pos().y()-listPillar.at(i)->pos().y())));
                        listPillar.insert(i+1,pillar);
                    }
                }
    }
   /* float angle=::atan2(listPillar.first()->centre().y()-listPillar.last()->centre().y(),
                        listPillar.first()->centre().x()-listPillar.last()->centre().x())/PI*180;
    angle=angle<0?angle+360:angle;
    qDebug()<<angle;*/
    distance.append(this->normalVector2D(QPointF(listPillar.last()->pos().x()-listPillar.at(listPillar.count()-2)->pos().x(),
                                                 listPillar.last()->pos().y()-listPillar.at(listPillar.count()-2)->pos().y())));
    float a=0;
    QPointF center=listPillar.at(0)->pos();
    //// Выравнивание столбов в одну линию
    for(int i=0;i<step-1;i++)
    {
        listPillar.at(i+1)->setPosition(this->rotatePoint(center,QPointF(center.x()-(distance.at(i)+a),center.y()),angle));
        a+=distance.at(i);
    }
}

void Alignment::appendVertex(GraphicsPillarItem *parentPillar)
{
  /*  Alignment::firstVertex parent;
    parent.first=parentPillar;
    this->changePosPillar.append(parent);
    QList<GraphicsWallItem*> wallPillar=parentPillar->itemsWall();
    foreach(Alignment::firstVertex firstPillar,this->changePosPillar)
    {
        foreach(GraphicsWallItem *wall,wallPillar)
            if(firstPillar.first->collidesWithItem(wall))
                wallPillar.removeAt(wallPillar.indexOf(wall));
    }
    if(!wallPillar.isEmpty())
        foreach(QGraphicsItem *item,this->itemScene)
        {
            GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
            foreach(GraphicsWallItem *wall,wallPillar)
                if()
        }*/
}

void Alignment::alignmentLengthPillar(int length, QList<QGraphicsItem *> items)
{
    if(items.isEmpty())
        return;
    foreach(QGraphicsItem *item,items)
    {
        if(item->type()!=GraphicsPillarItem::Type)
            items.removeAt(items.indexOf(item));
        item->setSelected(false);
    }
    if(items.isEmpty())
        return;
    this->itemScene=items;
    this->appendVertex(qgraphicsitem_cast<GraphicsPillarItem*>(items.first()));
}
