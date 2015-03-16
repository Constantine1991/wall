#include "component.h"
#include "ui_component.h"

Component::Component(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Component)
{
    ui->setupUi(this);
}

Component::~Component()
{
    delete ui;
}

void Component::on_pushButton_clicked()
{
    TYPEITEM type;
    if(ui->radioButton->isChecked())
        type=ITEM_WICKET;
    if(ui->radioButton_2->isChecked())
        type=ITEM_GATE_A;
    if(ui->radioButton_3->isChecked())
        type=ITEM_GATE_B;
    emit this->isTypeComponent(type,ui->lineEdit->text().toInt());
    this->close();
}

void Component::on_pushButton_2_clicked()
{
    this->isTypeComponent(ITEM_NONE,0);
    this->close();
}
