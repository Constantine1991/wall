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
    if(listPillar.isEmpty())
        return;
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
        listPillar.at(i+1)->setPosition(this->rotatePoint(center,QPointF(center.x()-(distance.at(i)+a),
                                                                         center.y()),angle));
        a+=distance.at(i);
    }
}

float Alignment::anglePointToPoint(QPointF p1, QPointF p2)
{
    float angle=::atan2(p1.y()-p2.y(),p1.x()-p2.x())/PI*180;
    angle=angle<0?angle+360:angle;
    return angle;
}

bool Alignment::coliding(QGraphicsItem *wallItem, QGraphicsItem *pillarItem)
{
    GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(pillarItem);
    GraphicsWallItem *wall=qgraphicsitem_cast<GraphicsWallItem*>(wallItem);
    if(((pillar->centre().x()+pillar->boundingRect().width()/2)>=wall->line().p1().x())&&
       ((pillar->centre().x()-pillar->boundingRect().width()/2)<=wall->line().p1().x())&&
       ((pillar->centre().y()+pillar->boundingRect().height()/2)>=wall->line().p1().y())&&
       ((pillar->centre().y()-pillar->boundingRect().height()/2)<=wall->line().p1().y()))
        return true;
    if(((pillar->centre().x()+pillar->boundingRect().width()/2)>=wall->line().p2().x())&&
       ((pillar->centre().x()-pillar->boundingRect().width()/2)<=wall->line().p2().x())&&
       ((pillar->centre().y()+pillar->boundingRect().height()/2)>=wall->line().p2().y())&&
       ((pillar->centre().y()-pillar->boundingRect().height()/2)<=wall->line().p2().y()))
        return true;
    return false;
}

QList<Alignment::Child*> Alignment::childToParent(QGraphicsItem *item,QList<QGraphicsItem*> selectedItem)
{
    GraphicsPillarItem *parentPillar=qgraphicsitem_cast<GraphicsPillarItem*>(item);
    QList<Alignment::Child*> listChild;
    foreach(GraphicsWallItem *itemWall,parentPillar->itemsWall())
    {
        foreach(QGraphicsItem *selected,selectedItem)
            if(this->coliding(itemWall,selected))
            {
                bool appendChild=true;
                foreach(Alignment::Parent *parent,this->parentItem)
                {
                    if(parent->parent==selected)
                    {
                        appendChild=false;
                        break;
                    }
                    foreach(Alignment::Child *child,parent->listChild)
                        if(child->child==selected)
                        {
                            appendChild=false;
                            break;
                        }
                }
                if(appendChild)
                {
                    Alignment::Child *append=new Alignment::Child;
                    append->child=selected;
                    append->angleChildToParent=this->anglePointToPoint(item->pos(),selected->pos());
                    listChild.append(append);
                }
            }
    }
    return listChild;

}

void Alignment::av(QGraphicsItem *parent, QList<QGraphicsItem *> selectedItem)
{
    QList<Alignment::Child*> appendChildToParent=this->childToParent(parent,selectedItem);
    if(appendChildToParent.isEmpty())
        return;
    Alignment::Parent *appendParent=new Alignment::Parent;
    appendParent->parent=parent;
    appendParent->listChild.append(appendChildToParent);
    this->parentItem.append(appendParent);
    foreach(Alignment::Child *child,appendChildToParent)
        this->av(child->child,selectedItem);
}

void Alignment::alignmentLengthPillar(int length,QList<QGraphicsItem*> aligmentItem)
{
    if(aligmentItem.isEmpty())
        return;
    Alignment::Parent *parent=new Alignment::Parent;
    parent->parent=aligmentItem.at(0);
    this->parentItem.append(parent);
    this->av(aligmentItem.at(0),aligmentItem);
    if(this->parentItem.count()==1)
        return;
//    for(int i=0;i<parentItem.count();i++)
//    {
//        QString caption=QString::fromLocal8Bit("Родитель ")+QString::number(i)+"("+QString::number(parentItem.at(i)->parent->pos().x())+
//                        ","+QString::number(parentItem.at(i)->parent->pos().y())+"):";
//        foreach(Alignment::Child *child,parentItem.at(i)->listChild)
//            caption+="("+QString::number(child->child->pos().x())+","+QString::number(child->child->pos().y())+
//                    "):"+QString::number(child->angleChildToParent)+",";
//        GraphicsPillarItem *p=qgraphicsitem_cast<GraphicsPillarItem*>(parentItem.at(i)->parent);
//        p->setText(caption);
//        qDebug()<<"Parent:"<<i<<" Count Child:"<<this->parentItem.at(i)->listChild.count();
//    }
//    QGraphicsItemGroup *group=new QGraphicsItemGroup;
//    this->scene->addItem(group);
//    foreach(QGraphicsItem *item,aligmentItem)
//        group->addToGroup(item);
//    qDebug()<<"boundiingRect:"<<group->boundingRect();
//    foreach(QGraphicsItem *item,aligmentItem)
//        group->removeFromGroup(item);

    foreach(Alignment::Parent *parent,parentItem)
        foreach(Alignment::Child *child,parent->listChild)
        {
            GraphicsPillarItem *pillar=qgraphicsitem_cast<GraphicsPillarItem*>(child->child);
            pillar->setPosition(this->rotatePoint(parent->parent->pos(),QPointF(parent->parent->pos().x()-length,
                                                                                 parent->parent->pos().y()),
                                                  child->angleChildToParent));
        }

}
