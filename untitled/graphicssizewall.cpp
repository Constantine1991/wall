#include "graphicssizewall.h"
#include "ui_graphicssizewall.h"

GraphicsSizeWall::GraphicsSizeWall(DiagramView *diagramView,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicsSizeWall)
{
    ui->setupUi(this);
    this->diagramView=diagramView;
}

GraphicsSizeWall::~GraphicsSizeWall()
{
    delete ui;
}

void GraphicsSizeWall::on_pushButton_clicked()
{
    this->diagramView->alignmentSelectedWall(ui->lineEdit->text().toInt());
    this->close();
}

void GraphicsSizeWall::on_pushButton_2_clicked()
{
    this->close();
}
