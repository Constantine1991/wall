#include "propertiespillarwindow.h"
#include "ui_propertiespillarwindow.h"
#include <QDebug>

PropertiesPillarWindow::PropertiesPillarWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropertiesPillarWindow)
{
    ui->setupUi(this);
    this->lastIndexCheckBox=0;
    this->saveFlag=false;
}

PropertiesPillarWindow::~PropertiesPillarWindow()
{
    delete ui;
}

void PropertiesPillarWindow::SetPropertiesPillar(GraphicsPillarItem *item, QList<COLOR *> listColor)
{
    ui->widget->heightBrick=this->heightBrick;
    this->Pillar=item;
    this->listColor=listColor;
    ui->lineEdit->setText(QString::number(this->Pillar->height()));
    if(this->Pillar->height()==0)
    {
        this->Pillar->setHeightSide(0,0);
        this->Pillar->setHeightSide(1,0);
        this->Pillar->setHeightSide(2,0);
        this->Pillar->setHeightSide(3,0);
    }
    ui->lineEdit_3->setText(QString::number(this->Pillar->heightSide(GraphicsPillarItem::SIDE_FRONT)));
    ui->checkBox->setChecked(this->Pillar->isTop());
    ui->comboBox_2->setEnabled(this->Pillar->isTop());
    ui->checkBox_5->setChecked(this->Pillar->isPazzle());
    ui->spinBox->setEnabled(!ui->checkBox_5->isChecked());
    ui->comboBox_3->setEnabled(!ui->checkBox_5->isChecked());
    ui->checkBox_3->setEnabled(!ui->checkBox_5->isChecked());
    ui->comboBox_4->setEnabled(ui->checkBox_5->isChecked());
    ui->comboBox_5->setEnabled(ui->checkBox_5->isChecked());
    if(this->Pillar->isBottomType()==GraphicsPillarItem::BOTTOM_NONE)
        ui->checkBox_6->setChecked(false);
    else{
        ui->checkBox_6->setChecked(true);
        ui->comboBox_6->setCurrentIndex((int)this->Pillar->isBottomType());
        ui->comboBox_6->setEnabled(true);
    }

    ui->comboBox_2->setFocusPolicy(Qt::NoFocus);
    int size = ui->comboBox_2 ->style()->pixelMetric(QStyle::PM_IconViewIconSize);
    QPixmap pixmap(size,size-5);
    int con=0;
    foreach (COLOR* color,listColor) {
        ui->comboBox_5 ->addItem(color->caption);
        ui->comboBox_2->addItem(color->caption);
        ui->comboBox_3->addItem(color->caption);
        ui->comboBox_4->addItem(color->caption);
        pixmap.fill(color->color);

        QRect rBorder(0,0,size,size);
        QPainter p(&pixmap);
        QPen pen(Qt::lightGray, 1, Qt::SolidLine);
        p.setPen(pen);
        p.drawRect(rBorder);

        ui->comboBox_5->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_2->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_3->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_4->setItemData(con, pixmap, Qt::DecorationRole);
        con=con+1;
    }
    foreach(COLOR *color,this->listColor)
    {
        if(this->Pillar->isPazzle())
        {
            if(*color==this->Pillar->colorPazzle(0))
                ui->comboBox_4->setCurrentIndex(this->listColor.indexOf(color));
            if(*color==this->Pillar->colorPazzle(1))
                ui->comboBox_5->setCurrentIndex(this->listColor.indexOf(color));
        }
        if(this->Pillar->isTop())
            if(*color==this->Pillar->topColor())
                ui->comboBox_2->setCurrentIndex(this->listColor.indexOf(color));
        if(!this->Pillar->isPazzle()&& this->Pillar->countColorRow()!=0)
            if(*color==this->Pillar->colorRow(0))
                ui->comboBox_3->setCurrentIndex(this->listColor.indexOf(color));
    }
    if(this->Pillar->height()<this->heightBrick)
        return;
    ui->widget->setHeight(this->Pillar->height());
    ui->widget->setInsertBottom(this->Pillar->heightSide(GraphicsPillarItem::SIDE_FRONT));
    if(ui->widget->row()==0)
        ui->spinBox->setMaximum(0);
    else{
        ui->spinBox->setMaximum(ui->widget->row());
        ui->spinBox->setMinimum(1);
        ui->spinBox->setSingleStep(1);
    }
    if(ui->widget->row()!=0)
    {
        ui->widget->setEnabledTop(this->Pillar->isTop());
        ui->widget->setColorTop(this->Pillar->topColor().color);
        ui->widget->setEnabledPazzle(this->Pillar->isPazzle(),this->Pillar->colorPazzle(0).color,
                                     this->Pillar->colorPazzle(1).color);
        if(!this->Pillar->isPazzle()&& this->Pillar->countColorRow()!=0)
            for(int i=0;i<ui->widget->row();i++)
                ui->widget->setColorRow(i+1,this->Pillar->colorRow(i).color);
    }

}

void PropertiesPillarWindow::on_pushButton_clicked()
{
    this->saveFlag=true;
    this->saveSetting();
    this->close();
}

void PropertiesPillarWindow::on_pushButton_3_clicked()
{
}

void PropertiesPillarWindow::on_comboBox_activated(const QString &arg1)
{

}

void PropertiesPillarWindow::on_comboBox_activated(int index)
{
    this->Pillar->setHeightSide(this->lastIndexCheckBox,ui->lineEdit_3->text().toInt());
    ui->widget->setRenderingSide(index);
    ui->lineEdit_3->clear();
    ui->lineEdit_3->setText(QString::number(this->Pillar->heightSide(index)));
    this->lastIndexCheckBox=index;

}

void PropertiesPillarWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.toInt()<this->heightBrick)
        return;
    ui->widget->setHeight(arg1.toInt());
    if(ui->widget->row()>0)
    {
        ui->spinBox->setMaximum(ui->widget->row());
        ui->spinBox->setMinimum(1);
        ui->spinBox->setSingleStep(1);
    }else ui->spinBox->setMaximum(0);
}

void PropertiesPillarWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
}

void PropertiesPillarWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    ui->widget->setInsertBottom(arg1.toInt());
}

void PropertiesPillarWindow::on_checkBox_clicked()
{
    ui->widget->setEnabledTop(ui->checkBox->isChecked());
    ui->comboBox_2->setEnabled(ui->checkBox->isChecked());
}

void PropertiesPillarWindow::on_comboBox_2_activated(int index)
{
    if(ui->checkBox->isChecked())
        ui->widget->setColorTop(this->listColor.at(index)->color);
}

void PropertiesPillarWindow::on_spinBox_valueChanged(int arg1)
{
    foreach(COLOR * color,this->listColor)
        if(color->color==ui->widget->colorRow(arg1))
        {
            ui->comboBox_3->setCurrentIndex(this->listColor.indexOf(color));
            break;
        }
}

void PropertiesPillarWindow::on_comboBox_3_activated(int index)
{
   if(!ui->checkBox_3->isChecked())
        ui->widget->setColorRow(ui->spinBox->value(),this->listColor.at(index)->color);
    else ui->widget->setColorAllRow(this->listColor.at(index)->color);
}

void PropertiesPillarWindow::on_checkBox_5_clicked()
{
    ui->spinBox->setEnabled(!ui->checkBox_5->isChecked());
    ui->comboBox_3->setEnabled(!ui->checkBox_5->isChecked());
    ui->checkBox_3->setEnabled(!ui->checkBox_5->isChecked());
    ui->widget->setEnabledPazzle(ui->checkBox_5->isChecked(),this->listColor.at(ui->comboBox_4->currentIndex())->color,
                                 this->listColor.at(ui->comboBox_5->currentIndex())->color);
    ui->comboBox_4->setEnabled(ui->checkBox_5->isChecked());
    ui->comboBox_5->setEnabled(ui->checkBox_5->isChecked());
}

void PropertiesPillarWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked())
         ui->widget->setColorAllRow(this->listColor.at(ui->comboBox_3->currentIndex())->color);
}

void PropertiesPillarWindow::on_comboBox_4_activated(int index)
{
    ui->widget->setEnabledPazzle(ui->checkBox_5->isChecked(),this->listColor.at(index)->color,
                                 this->listColor.at(ui->comboBox_5->currentIndex())->color);
}

void PropertiesPillarWindow::on_comboBox_5_activated(int index)
{
    ui->widget->setEnabledPazzle(ui->checkBox_5->isChecked(),this->listColor.at(ui->comboBox_4->currentIndex())->color,
                                 this->listColor.at(index)->color);
}

void PropertiesPillarWindow::saveSetting()
{
    if(ui->lineEdit->text().toInt()>=this->heightBrick)
    {
        this->Pillar->setHeight(ui->lineEdit->text().toInt());
        this->Pillar->setHeightSide(ui->comboBox->currentIndex(),ui->lineEdit_3->text().toInt());
        for(int i=0;i<4;i++)
            if((this->Pillar->heightSide(i)>this->Pillar->height()|| (this->Pillar->heightSide(i)<0)))
                this->Pillar->setHeightSide(i,0);
        this->Pillar->setTop(ui->checkBox->isChecked());
        this->Pillar->setTopColor(*this->listColor.at(ui->comboBox_2->currentIndex()));
        this->Pillar->setPazzle(ui->checkBox_5->isChecked());
        this->Pillar->setColorPazzle(0,*this->listColor.at(ui->comboBox_4->currentIndex()));
        this->Pillar->setColorPazzle(1,*this->listColor.at(ui->comboBox_5->currentIndex()));
        if(ui->checkBox_6->isChecked())
            this->Pillar->setBottomType(ui->comboBox_6->currentIndex());
        else this->Pillar->setBottomType(GraphicsPillarItem::BOTTOM_NONE);
        this->Pillar->clearColorRow();
        if(!this->Pillar->isPazzle())
        {
            for(int i=0;i<ui->widget->row();i++)
                foreach(COLOR *color,this->listColor)
                    if(color->color==ui->widget->colorRow(i))
                        this->Pillar->addColorRow(*color);
        }
        emit this->closeProperties(ITEM_PILLAR,ui->checkBox_4->isChecked());
    }
}

void PropertiesPillarWindow::closeEvent(QCloseEvent *event)
{
    if(!this->saveFlag)
    {
        int result=QMessageBox::warning(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Сохранить измененые данные?"),
                             QMessageBox::Ok,QMessageBox::Cancel);
        if(result==QMessageBox::Ok)
            this->saveSetting();
    }
    QMainWindow::closeEvent(event);
}

void PropertiesPillarWindow::on_pushButton_2_clicked()
{
    this->close();
}

void PropertiesPillarWindow::on_checkBox_2_clicked()
{

}

void PropertiesPillarWindow::on_checkBox_6_clicked()
{
    ui->comboBox_6->setEnabled(ui->checkBox_6->isChecked());
}
