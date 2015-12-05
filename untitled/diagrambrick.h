#ifndef DIAGRAMBRICK_H
#define DIAGRAMBRICK_H
#include <QGraphicsRectItem>
#include <QPointF>
#include <QBrush>
#include <QPen>

class DiagramBrick
{
public:
    DiagramBrick();
    ~DiagramBrick();
    void setSize(int width,int height);//Задать ширину и высоту
    void setPos(float x,float y);// Задать позицию
    void setPos(QPointF pos);//Задать позицию
    void setBrush(QBrush brush);//Задать цвет
    QGraphicsRectItem *brick()const; // Возвратить брик
private:
    QGraphicsRectItem *Brick;
};

#endif // DIAGRAMBRICK_H
