#include "graphicssizewall.h"
#include "ui_graphicssizewall.h"

GraphicsSizeWall::GraphicsSizeWall(DiagramView *diagramView, AlignmentType type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicsSizeWall)
{
    ui->setupUi(this);
    this->diagramView=diagramView;
    this->type=type;
    if(type==GraphicsSizeWall::ALIGNMENT_ANGLE)
    {
        this->setWindowTitle(QString::fromLocal8Bit("������������ ������� �� ��������� ����"));
        ui->label->setText(QString::fromLocal8Bit("������� �������:"));
    } else {
        this->setWindowTitle(QString::fromLocal8Bit("������������ ���������� ����� ����� �������"));
        ui->label->setText(QString::fromLocal8Bit("������� ���������� ����� ����� �������:"));
    }
}

GraphicsSizeWall::~GraphicsSizeWall()
{
    delete ui;
}

void GraphicsSizeWall::on_pushButton_clicked()
{
    if(this->type==GraphicsSizeWall::ALIGNMENT_ANGLE)
        this->diagramView->alignmentAngelSelectedWall(ui->lineEdit->text().toInt());
    else this->diagramView->alignmentLengthSelectedItem(ui->lineEdit->text().toInt());
    this->close();
}

void GraphicsSizeWall::on_pushButton_2_clicked()
{
    this->close();
}
