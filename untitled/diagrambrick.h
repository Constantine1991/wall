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
    void setSize(int width,int height);//������ ������ � ������
    void setPos(float x,float y);// ������ �������
    void setPos(QPointF pos);//������ �������
    void setBrush(QBrush brush);//������ ����
    QGraphicsRectItem *brick()const; // ���������� ����
private:
    QGraphicsRectItem *Brick;
};

#endif // DIAGRAMBRICK_H
