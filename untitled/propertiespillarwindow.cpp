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
    ui->widget->graphicPillar.setSizeTopTile(100,80);
    ui->widget->graphicPillar.setSizeBrickTile(50,50);
    ui->widget->graphicPillar.setSizeBottomTile(100,80);
    ui->widget->setRectScene(480,550);
    ui->widget->graphicPillar.setPos(225,550);
    ui->widget->graphicPillar.showSide(DiagramPillar::FRONT);
    ui->widget->showText(true);
    ui->widget->setPosText(200,450,50);
}

PropertiesPillarWindow::~PropertiesPillarWindow()
{
    delete ui;
}

void PropertiesPillarWindow::setCurrentTextComboBox(QComboBox *comboBox, QString text)
{
    if(text.isEmpty())
        return;
    for(int i=0;i<comboBox->count();i++)
        if(comboBox->itemText(i)==text)
        {
            comboBox->setCurrentIndex(i);
            break;
        }
}

void PropertiesPillarWindow::setColorCommboBox(QComboBox *comboBox, QList<SettingColor::COLOR_BRICK *> listColor)
{
    comboBox->setFocusPolicy(Qt::NoFocus);
    foreach(SettingItem::COLOR_BRICK *color,listColor)
        comboBox->addItem(QIcon(QPixmap::fromImage(color->image1)),color->nameColor);
}

void PropertiesPillarWindow::SetPropertiesPillar(GraphicsPillarItem *item, SettingItem *itemSetting, bool fundament)
{
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
    this->setColorCommboBox(ui->comboBox_2,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_TOP));
    this->setColorCommboBox(ui->comboBox_3,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG));
    this->setColorCommboBox(ui->comboBox_4,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG));
    this->setColorCommboBox(ui->comboBox_5,this->itemSetting->colorBrick(SettingItem::COLOR_BRICK_PILLAR_BIG));

    for(int i=0;i<4;i++)
        ui->widget->graphicPillar.setInsert(i,this->Pillar->heightSide(i));

    ui->checkBox->setChecked(this->Pillar->isTop());
    ui->comboBox_2->setEnabled(this->Pillar->isTop());
    ui->widget->graphicPillar.setTop(this->Pillar->isTop());
    if(this->Pillar->isTop())
    {
        this->setCurrentTextComboBox(ui->comboBox_2,this->Pillar->topColor());
        ui->widget->graphicPillar.setTopColor(this->Pillar->topColor());
    }

    ui->checkBox_5->setChecked(this->Pillar->isPazzle());
    ui->spinBox->setEnabled(!ui->checkBox_5->isChecked());
    ui->comboBox_3->setEnabled(!ui->checkBox_5->isChecked());
    ui->checkBox_3->setEnabled(!ui->checkBox_5->isChecked());
    ui->comboBox_4->setEnabled(ui->checkBox_5->isChecked());
    ui->comboBox_5->setEnabled(ui->checkBox_5->isChecked());
    ui->widget->graphicPillar.setPazzleColor(this->Pillar->isPazzle());
    if(this->Pillar->isPazzle())
    {
        this->setCurrentTextComboBox(ui->comboBox_4,this->Pillar->colorPazzle(0));
        this->setCurrentTextComboBox(ui->comboBox_5,this->Pillar->colorPazzle(1));
        ui->widget->graphicPillar.setRowPazzleColor(this->Pillar->colorPazzle(0),this->Pillar->colorPazzle(1));
    }else{
        if(!this->Pillar->colorListRow().isEmpty())
        {
            this->setCurrentTextComboBox(ui->comboBox_3,this->Pillar->colorRow(0));
            ui->widget->graphicPillar.setRowColor(this->Pillar->colorListRow());
        }
    }

    ui->checkBox_6->setChecked(this->Pillar->isBottomTypeEnable());
    ui->comboBox_6->setCurrentIndex(this->Pillar->isBottomType());
    ui->comboBox_6->setEnabled(this->Pillar->isBottomTypeEnable());
    ui->widget->graphicPillar.setBottom(this->Pillar->isBottomTypeEnable());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
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
    ui->lineEdit_3->setText(QString::number(this->Pillar->heightSide(index)));
    this->lastIndexCheckBox=index;
    ui->widget->graphicPillar.showSide(index);
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.toInt()<this->itemSetting->heightBrickAngle)
        return;
    ui->widget->graphicPillar.setHeight(arg1.toInt());
    if(ui->widget->graphicPillar.row()>0)
    {
        ui->spinBox->setMaximum(ui->widget->graphicPillar.row());
        ui->spinBox->setMinimum(1);
        ui->spinBox->setSingleStep(1);
    }else ui->spinBox->setMaximum(0);
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
}

void PropertiesPillarWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    if(arg1.toInt()<=ui->lineEdit->text().toInt())
    {
        ui->widget->graphicPillar.setInsert(ui->comboBox->currentIndex(),arg1.toInt());
        ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
        this->Pillar->setHeightSide(ui->comboBox->currentIndex(),arg1.toInt());
        if(ui->checkBox_6->isChecked())
            ui->comboBox_6->setCurrentIndex(this->Pillar->isAutoBottomType());
    }
    else ui->lineEdit_3->setText(ui->lineEdit->text());
}

void PropertiesPillarWindow::on_checkBox_clicked()
{
    ui->comboBox_2->setEnabled(ui->checkBox->isChecked());
    ui->widget->graphicPillar.setTop(ui->checkBox->isChecked());
    ui->widget->graphicPillar.setTopColor(ui->comboBox_2->currentText());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::on_comboBox_2_activated(int index)
{
    if(ui->checkBox->isChecked())
    {
        ui->widget->graphicPillar.setTopColor(ui->comboBox_2->currentText());
        ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
    }
}

void PropertiesPillarWindow::on_spinBox_valueChanged(int arg1)
{
    QString nameColor=ui->widget->graphicPillar.rowColor(arg1-1);
    this->setCurrentTextComboBox(ui->comboBox_3,nameColor);
}

void PropertiesPillarWindow::on_comboBox_3_activated(int index)
{
   if(!ui->checkBox_3->isChecked())
   {
       ui->widget->graphicPillar.setRowColor(ui->spinBox->value(),ui->comboBox_3->currentText());
       ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
   }
   else {
       ui->widget->graphicPillar.setRowColorAll(ui->comboBox_3->currentText());
       ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
   }
}

void PropertiesPillarWindow::on_checkBox_5_clicked()
{
      ui->spinBox->setEnabled(!ui->checkBox_5->isChecked());
      ui->comboBox_3->setEnabled(!ui->checkBox_5->isChecked());
      ui->checkBox_3->setEnabled(!ui->checkBox_5->isChecked());
      ui->comboBox_4->setEnabled(ui->checkBox_5->isChecked());
      ui->comboBox_5->setEnabled(ui->checkBox_5->isChecked());
      ui->widget->graphicPillar.setPazzleColor(ui->checkBox_5->isChecked());
      ui->widget->graphicPillar.setRowPazzleColor(ui->comboBox_4->currentText(),ui->comboBox_5->currentText());
      ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::on_checkBox_3_clicked()
{
    if(ui->checkBox_3->isChecked())
    {
         ui->widget->graphicPillar.setRowColorAll(ui->comboBox_3->currentText());
         ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
    }
}

void PropertiesPillarWindow::on_comboBox_4_activated(int index)
{
    ui->widget->graphicPillar.setRowPazzleColor(ui->comboBox_4->currentText(),ui->comboBox_5->currentText());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::on_comboBox_5_activated(int index)
{
    ui->widget->graphicPillar.setRowPazzleColor(ui->comboBox_4->currentText(),ui->comboBox_5->currentText());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::saveSetting()
{
    qDebug()<<QString::fromLocal8Bit("Цвет крышки столба:")<<ui->comboBox_2->currentText();
    if(ui->lineEdit->text().toInt()>=this->itemSetting->heightBrickAngle)
    {
        qDebug()<<"-------SAVE PILLAR-------";
        this->Pillar->setHeight(ui->lineEdit->text().toInt());
        qDebug()<<QString::fromLocal8Bit("Высота столба")<<this->Pillar->height();
        this->Pillar->setHeightSide(ui->comboBox->currentIndex(),ui->lineEdit_3->text().toInt());
        for(int i=0;i<4;i++)
            if((this->Pillar->heightSide(i)>this->Pillar->height()|| (this->Pillar->heightSide(i)<0)))
                this->Pillar->setHeightSide(i,0);
        this->Pillar->setTop(ui->checkBox->isChecked());
        qDebug()<<QString::fromLocal8Bit("Крышка столба:")<<this->Pillar->isTop();
        this->Pillar->setTopColor(ui->comboBox_2->currentText());
        qDebug()<<QString::fromLocal8Bit("Цвет крышки столба:")<<this->Pillar->topColor();
        this->Pillar->setPazzle(ui->checkBox_5->isChecked());
        qDebug()<<QString::fromLocal8Bit("Пазл:")<<this->Pillar->isPazzle();
        this->Pillar->setColorPazzle(0,ui->comboBox_4->currentText());
        qDebug()<<QString::fromLocal8Bit("Цвет пазла 1:")<<this->Pillar->colorPazzle(0);
        this->Pillar->setColorPazzle(1,ui->comboBox_5->currentText());
        qDebug()<<QString::fromLocal8Bit("Цвет пазла 2:")<<this->Pillar->colorPazzle(1);
        this->Pillar->setBottomTypeEnable(ui->checkBox_6->isChecked());
        qDebug()<<QString::fromLocal8Bit("Основание столба:")<<this->Pillar->isBottomTypeEnable();
        this->Pillar->setBottomType(ui->comboBox_6->currentIndex());
        qDebug()<<QString::fromLocal8Bit("Название основания столба:")<<this->Pillar->isBottomType();
        this->Pillar->clearColorRow();
        if(!this->Pillar->isPazzle())
        {
            this->Pillar->setColorRow(ui->widget->graphicPillar.rowColor());
            qDebug()<<QString::fromLocal8Bit("Количество цветов:")<<this->Pillar->colorListRow().count();
        }
        emit this->closeProperties(SettingItem::ITEM_PILLAR,ui->checkBox_4->isChecked());
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
    ui->widget->graphicPillar.setBottom(ui->checkBox_6->isChecked());
    ui->widget->draw(DiagramViewFrontItem::ITEM_PILLAR);
}

void PropertiesPillarWindow::on_lineEdit_3_textEdited(const QString &arg1)
{

}
