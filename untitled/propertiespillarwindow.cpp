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
    ui->widget->graphicPillar.setSizeTopTile(100,50);
    ui->widget->graphicPillar.setSizeBrickTile(50,50);
    ui->widget->graphicPillar.setSizeBottomTile(100,50);
    ui->widget->setRectScene(480,550);
    ui->widget->graphicPillar.setPos(225,500);
}

PropertiesPillarWindow::~PropertiesPillarWindow()
{
    delete ui;
}

void PropertiesPillarWindow::setColorCommboBox(QComboBox *comboBox, QList<SettingColor::COLOR_BRICK *> listColor)
{
    comboBox->setFocusPolicy(Qt::NoFocus);
    foreach(SettingItem::COLOR_BRICK *color,listColor)
        comboBox->addItem(QIcon(QPixmap::fromImage(color->image1)),color->nameColor);
}

void PropertiesPillarWindow::SetPropertiesPillar(GraphicsPillarItem *item, SettingItem *itemSetting, bool fundament)
{
    //ui->widget->heightBrick=this->itemSetting->heightBrickAngle;
    ui->widget->graphicPillar.setSettingItem(itemSetting);
    this->Pillar=item;
    this->itemSetting=itemSetting;
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
    ui->checkBox_6->setChecked(this->Pillar->isBottomTypeEnable() || !fundament);
    ui->comboBox_6->setCurrentIndex(this->Pillar->isBottomType());
    ui->comboBox_6->setEnabled(this->Pillar->isBottomTypeEnable() || !fundament);
    this->setColorCommboBox(ui->comboBox_2,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_TOP));
    this->setColorCommboBox(ui->comboBox_3,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG));
    this->setColorCommboBox(ui->comboBox_4,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG));
    this->setColorCommboBox(ui->comboBox_5,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG));
//    foreach(COLOR *color,this->listColor)
//    {
//        if(this->Pillar->isPazzle())
//        {
//            if(*color==this->Pillar->colorPazzle(0))
//                ui->comboBox_4->setCurrentIndex(this->listColor.indexOf(color));
//            if(*color==this->Pillar->colorPazzle(1))
//                ui->comboBox_5->setCurrentIndex(this->listColor.indexOf(color));
//        }
//        if(this->Pillar->isTop())
//            if(*color==this->Pillar->topColor())
//                ui->comboBox_2->setCurrentIndex(this->listColor.indexOf(color));
//        if(!this->Pillar->isPazzle()&& this->Pillar->countColorRow()!=0)
//            if(*color==this->Pillar->colorRow(0))
//                ui->comboBox_3->setCurrentIndex(this->listColor.indexOf(color));
//    }
//    if(this->Pillar->height()<this->heightBrick)
//        return;
//    ui->widget->setHeight(this->Pillar->height());
//    ui->widget->setInsertBottom(this->Pillar->heightSide(GraphicsPillarItem::SIDE_FRONT));
//    if(ui->widget->row()==0)
//        ui->spinBox->setMaximum(0);
//    else{
//        ui->spinBox->setMaximum(ui->widget->row());
//        ui->spinBox->setMinimum(1);
//        ui->spinBox->setSingleStep(1);
//    }
//    if(ui->widget->row()!=0)
//    {
//        ui->widget->setEnabledTop(this->Pillar->isTop());
//        ui->widget->setColorTop(this->Pillar->topColor().color);
//        ui->widget->setEnabledPazzle(this->Pillar->isPazzle(),this->Pillar->colorPazzle(0).color,
//                                     this->Pillar->colorPazzle(1).color);
//        if(!this->Pillar->isPazzle()&& this->Pillar->countColorRow()!=0)
//            for(int i=0;i<ui->widget->row();i++)
//                ui->widget->setColorRow(i+1,this->Pillar->colorRow(i).color);
//    }

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
   // this->Pillar->setHeightSide(this->lastIndexCheckBox,ui->lineEdit_3->text().toInt());
    //ui->widget->setRenderingSide(index);
    ui->lineEdit_3->setText(QString::number(this->Pillar->heightSide(index)));
   // this->lastIndexCheckBox=index;

}

void PropertiesPillarWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.toInt()<this->itemSetting->heightBrickAngle)
        return;
    ui->widget->graphicPillar.setHeight(arg1.toInt());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
//    ui->widget->setHeight(arg1.toInt());
//    if(ui->widget->row()>0)
//    {
//        ui->spinBox->setMaximum(ui->widget->row());
//        ui->spinBox->setMinimum(1);
//        ui->spinBox->setSingleStep(1);
//    }else ui->spinBox->setMaximum(0);
}

void PropertiesPillarWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
}

void PropertiesPillarWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
//    if(arg1.toInt()<=ui->lineEdit->text().toInt())
//    {
//        ui->widget->setInsertBottom(arg1.toInt());
//        this->Pillar->setHeightSide(ui->comboBox->currentIndex(),arg1.toInt());
//        if(ui->checkBox_6->isChecked())
//            ui->comboBox_6->setCurrentIndex(this->Pillar->isAutoBottomType());
//    }
//    else ui->lineEdit_3->setText(ui->lineEdit->text());
}

void PropertiesPillarWindow::on_checkBox_clicked()
{
   // ui->widget->setEnabledTop(ui->checkBox->isChecked());
    ui->widget->graphicPillar.setTop(ui->checkBox->isChecked());
    ui->comboBox_2->setEnabled(ui->checkBox->isChecked());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::on_comboBox_2_activated(int index)
{
//    if(ui->checkBox->isChecked())
//        ui->widget->setColorTop(this->listColor.at(index)->color);
}

void PropertiesPillarWindow::on_spinBox_valueChanged(int arg1)
{
    /*foreach(COLOR * color,this->listColor)
        if(color->color==ui->widget->colorRow(arg1))
        {
            ui->comboBox_3->setCurrentIndex(this->listColor.indexOf(color));
            break;
        }*/
}

void PropertiesPillarWindow::on_comboBox_3_activated(int index)
{
//   if(!ui->checkBox_3->isChecked())
//        ui->widget->setColorRow(ui->spinBox->value(),this->listColor.at(index)->color);
//    else ui->widget->setColorAllRow(this->listColor.at(index)->color);
}

void PropertiesPillarWindow::on_checkBox_5_clicked()
{
//    ui->spinBox->setEnabled(!ui->checkBox_5->isChecked());
//    ui->comboBox_3->setEnabled(!ui->checkBox_5->isChecked());
//    ui->checkBox_3->setEnabled(!ui->checkBox_5->isChecked());
//    ui->widget->setEnabledPazzle(ui->checkBox_5->isChecked(),this->listColor.at(ui->comboBox_4->currentIndex())->color,
//                                 this->listColor.at(ui->comboBox_5->currentIndex())->color);
//    ui->comboBox_4->setEnabled(ui->checkBox_5->isChecked());
//    ui->comboBox_5->setEnabled(ui->checkBox_5->isChecked());
}

void PropertiesPillarWindow::on_checkBox_3_clicked()
{
//    if(ui->checkBox_3->isChecked())
//         ui->widget->setColorAllRow(this->listColor.at(ui->comboBox_3->currentIndex())->color);
}

void PropertiesPillarWindow::on_comboBox_4_activated(int index)
{
//    ui->widget->setEnabledPazzle(ui->checkBox_5->isChecked(),this->listColor.at(index)->color,
//                                 this->listColor.at(ui->comboBox_5->currentIndex())->color);
}

void PropertiesPillarWindow::on_comboBox_5_activated(int index)
{
//    ui->widget->setEnabledPazzle(ui->checkBox_5->isChecked(),this->listColor.at(ui->comboBox_4->currentIndex())->color,
//                                 this->listColor.at(index)->color);
}

void PropertiesPillarWindow::saveSetting()
{
    /*if(ui->lineEdit->text().toInt()>=this->heightBrick)
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
        this->Pillar->setBottomTypeEnable(ui->checkBox_6->isChecked());
        this->Pillar->setBottomType(ui->comboBox_6->currentIndex());
        /*if(ui->checkBox_6->isChecked())
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
    }*/
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
    ui->widget->graphicPillar.setBottom(ui->checkBox_6->isChecked());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
    //ui->widget->setEnabledBottom(ui->checkBox_6->isChecked());
}

void PropertiesPillarWindow::on_lineEdit_3_textEdited(const QString &arg1)
{

}
