#include "interval.h"
#include "ui_interval.h"

Interval::Interval(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Interval)
{
    ui->setupUi(this);
    this->apply=false;
}

Interval::~Interval()
{
    delete ui;
}

void Interval::on_pushButton_clicked()
{
    this->apply=true;
    this->close();
}

void Interval::on_pushButton_2_clicked()
{
    this->apply=false;
    this->close();
}

void Interval::closeEvent(QCloseEvent *event)
{
    if(this->apply)
        emit this->setInterval(ui->lineEdit->text().toFloat(),ui->lineEdit->text().isEmpty());
    else emit this->setInterval(0,true);
}
