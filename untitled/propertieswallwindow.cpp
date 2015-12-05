#include "propertieswallwindow.h"
#include "ui_propertieswallwindow.h"
#include "QDebug"

PropertiesWallWindow::PropertiesWallWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropertiesWallWindow)
{
    ui->setupUi(this);
    this->saveFlag=false;
}

PropertiesWallWindow::~PropertiesWallWindow()
{
    delete ui;
}

void PropertiesWallWindow::SetPropertiesWall(GraphicsWallItem *item, SettingItem *itemSetting,GraphicsPillarItem *itemPillar,bool fundament)
{
    /*ui->widget->setSetting(itemSetting);
    ui->widget->setHeightPillar(itemPillar->height());
    ui->widget->setTopPillar(itemPillar->isTop(),itemPillar->topColor());
    ui->widget->setPazzlePillar(itemPillar->isPazzle(),itemPillar->colorPazzle(0),itemPillar->colorPazzle(1));
    ui->widget->setColorListPillar(itemPillar->colorListRow());
    this->wall=item;
    this->itemSetting=itemSetting;
    this->itemPillar=itemPillar;

    qDebug()<<this->wall->isGirthRail();

    ui->checkBox_5->setChecked(this->wall->isGirthRail()|| !fundament);
    ui->lineEdit_2->setText(QString::number(this->wall->height()));
    ui->lineEdit->setText(QString::number(this->wall->width()));
    ui->checkBox_3->setChecked(this->wall->isTop());
    ui->comboBox_4->setEnabled(this->wall->isTop());

    ui->checkBox_4->setChecked(this->wall->isPazzle());
    ui->comboBox_2->setEnabled(this->wall->isPazzle());
    ui->comboBox_3->setEnabled(this->wall->isPazzle());
    ui->spinBox->setEnabled(!this->wall->isPazzle());
    ui->comboBox->setEnabled(!this->wall->isPazzle());
    ui->checkBox->setEnabled(!this->wall->isPazzle());

    ui->comboBox->setFocusPolicy(Qt::NoFocus);
    int size = ui->comboBox ->style()->pixelMetric(QStyle::PM_IconViewIconSize);
    QPixmap pixmap(size,size-5);
    int con=0;
    foreach (COLOR* color,this->itemSetting->color) {
        ui->comboBox ->addItem(color->caption);
        ui->comboBox_2->addItem(color->caption);
        ui->comboBox_3->addItem(color->caption);
        ui->comboBox_4->addItem(color->caption);
        ui->comboBox_5->addItem(color->caption);
        ui->comboBox_6->addItem(color->caption);
        ui->comboBox_7->addItem(color->caption);
        pixmap.fill(color->color);

        QRect rBorder(0,0,size,size);
        QPainter p(&pixmap);
        QPen pen(Qt::lightGray, 1, Qt::SolidLine);
        p.setPen(pen);
        p.drawRect(rBorder);

        ui->comboBox->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_2->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_3->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_4->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_5->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_6->setItemData(con, pixmap, Qt::DecorationRole);
        ui->comboBox_7->setItemData(con, pixmap, Qt::DecorationRole);
        con=con+1;
    }
    ui->widget->setGraphicsWall(this->wall->width(),this->wall->height());
    ui->widget->setEnableTopWall(this->wall->isTop(),this->wall->colorTop().color);
    ui->widget->setEnableColorPazzle(this->wall->isPazzle(),this->wall->colorPazzle(0).color,
                                     this->wall->colorPazzle(1).color);
    for(int i=0;i<this->wall->countColorRow();i++)
        ui->widget->setColorRowWall(i+1,this->wall->colorRow(i).color);
    if(ui->widget->countRow()==0)
        ui->spinBox->setMaximum(0);
    else{
        ui->spinBox->setMaximum(ui->widget->countRow());
        ui->spinBox->setMinimum(1);
        ui->spinBox->setSingleStep(1);
    }
    foreach(COLOR *color,this->itemSetting->color)
    {
        if(this->wall->isTop())
            if(this->wall->colorTop()==*color)
                ui->comboBox_4->setCurrentIndex(this->itemSetting->color.indexOf(color));
        if(this->wall->isPazzle())
        {
            if(this->wall->colorPazzle(0)==*color)
                ui->comboBox_2->setCurrentIndex(this->itemSetting->color.indexOf(color));
            if(this->wall->colorPazzle(1)==*color)
                ui->comboBox_3->setCurrentIndex(this->itemSetting->color.indexOf(color));
        }else
            if(!this->wall->isEmptyColorRow())
                if(this->wall->colorRow(0)==*color)
                    ui->comboBox->setCurrentIndex(this->itemSetting->color.indexOf(color));
    }
    switch(this->wall->isDecoreid())
    {
        case 0:{
            ui->radioButton_4->setChecked(true);
            ui->widget->setEnableDecoreit(false,QColor(),false,QColor(),false,QColor());
            break;
        }
        case 1:{
            foreach(COLOR *color,this->itemSetting->color)
                if(*color==this->wall->colorDecoreid())
                    ui->comboBox_5->setCurrentIndex(this->itemSetting->color.indexOf(color));
            ui->widget->setEnableDecoreit(true,this->wall->colorDecoreid().color,false,QColor(),false,QColor());
            ui->radioButton->setChecked(true);
            break;
        }
        case 2:{
            foreach(COLOR *color,this->itemSetting->color)
                if(*color==this->wall->colorDecoreid())
                    ui->comboBox_6->setCurrentIndex(this->itemSetting->color.indexOf(color));
            ui->widget->setEnableDecoreit(false,QColor(),true,this->wall->colorDecoreid().color,false,QColor());
            ui->radioButton_2->setChecked(true);
            break;
        }
        case 3:{
            foreach(COLOR *color,this->itemSetting->color)
                if(*color==this->wall->colorDecoreid())
                    ui->comboBox_7->setCurrentIndex(this->itemSetting->color.indexOf(color));
            ui->widget->setEnableDecoreit(false,QColor(),false,QColor(),true,this->wall->colorDecoreid().color);
            ui->radioButton_3->setChecked(true);
            break;
        }
    }*/
}

void PropertiesWallWindow::on_pushButton_4_clicked()
{
    this->saveFlag=true;
    this->saveSetting();
    this->close();
}

void PropertiesWallWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        return;
    if(arg1.toInt()<=0)
    {
        ui->lineEdit->setText(QString::number(this->itemSetting->minWidthBrickR));
        return;
    }
    if(ui->checkBox_5->isChecked())
        if(arg1.toInt()>this->itemSetting->maxWidthGirth)
        {
            ui->lineEdit->setText(QString::number(this->itemSetting->maxWidthGirth));
            return;
        }
    ui->widget->setWidthWall(arg1.toInt());
}

void PropertiesWallWindow::changeRowWall()
{
    if(ui->widget->countRow()>0)
    {
        ui->spinBox->setMaximum(ui->widget->countRow());
        ui->spinBox->setMinimum(1);
        ui->spinBox->setSingleStep(1);
    }else ui->spinBox->setMaximum(0);
}

void PropertiesWallWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
        return;
    if(arg1.toInt()<=0)
    {
        ui->lineEdit_2->setText(QString::number(this->itemSetting->heightBrickR));
        return;
    }
    if(arg1.toInt()>this->itemPillar->height())
    {
        ui->lineEdit_2->setText(QString::number(this->itemPillar->height()));
        return;
    }
    ui->widget->setHeightWall(arg1.toInt());
    this->changeRowWall();
}

void PropertiesWallWindow::on_checkBox_3_clicked()
{
//    ui->comboBox_4->setEnabled(ui->checkBox_3->isChecked());
//    ui->widget->setEnableTopWall(ui->checkBox_3->isChecked(),this->itemSetting->color.at(ui->comboBox_4->currentIndex())->color);
}

void PropertiesWallWindow::on_spinBox_valueChanged(int arg1)
{
    /*foreach(COLOR * color,this->itemSetting->color)
        if(color->color==ui->widget->getColorRow(arg1-1))
        {
            ui->comboBox->setCurrentIndex(this->itemSetting->color.indexOf(color));
            break;
        }*/
}

void PropertiesWallWindow::on_comboBox_currentIndexChanged(int index)
{
//    if(!ui->checkBox->isChecked())
//        ui->widget->setColorRowWall(ui->spinBox->value(),this->itemSetting->color.at(index)->color);
//    else ui->widget->setColorAllRawWall(this->itemSetting->color.at(index)->color);
}

void PropertiesWallWindow::on_checkBox_clicked()
{
//    if(ui->checkBox->isChecked())
//        ui->widget->setColorAllRawWall(this->itemSetting->color.at(ui->comboBox->currentIndex())->color);
}

void PropertiesWallWindow::on_checkBox_4_clicked()
{
//    ui->comboBox_2->setEnabled(ui->checkBox_4->isChecked());
//    ui->comboBox_3->setEnabled(ui->checkBox_4->isChecked());
//    ui->spinBox->setEnabled(!ui->checkBox_4->isChecked());
//    ui->comboBox->setEnabled(!ui->checkBox_4->isChecked());
//    ui->checkBox->setEnabled(!ui->checkBox_4->isChecked());
//    ui->widget->setEnableColorPazzle(ui->checkBox_4->isChecked(),this->itemSetting->color.at(ui->comboBox_2->currentIndex())->color,
//                                     this->itemSetting->color.at(ui->comboBox_3->currentIndex())->color);
}

void PropertiesWallWindow::on_comboBox_2_currentIndexChanged(int index)
{
}

void PropertiesWallWindow::on_comboBox_3_currentIndexChanged(int index)
{
}

void PropertiesWallWindow::on_comboBox_2_activated(int index)
{
//    ui->widget->setEnableColorPazzle(ui->checkBox_4->isChecked(),this->itemSetting->color.at(index)->color,
//                                     this->itemSetting->color.at(ui->comboBox_3->currentIndex())->color);
}

void PropertiesWallWindow::on_comboBox_3_activated(int index)
{
//    ui->widget->setEnableColorPazzle(ui->checkBox_4->isChecked(),this->itemSetting->color.at(ui->comboBox_2->currentIndex())->color,
//                                     this->itemSetting->color.at(index)->color);
}

void PropertiesWallWindow::on_comboBox_4_activated(int index)
{
//    ui->widget->setEnableTopWall(ui->checkBox_3->isChecked(),this->itemSetting->color.at(index)->color);
}

void PropertiesWallWindow::saveSetting()
{
    /*if((ui->lineEdit_2->text().toInt()<this->itemSetting->heightBrickR)||
       (ui->lineEdit_2->text().toInt()<this->itemSetting->minWidthBrickR))
        return;
    this->wall->setHeight(ui->lineEdit_2->text().toInt());
    this->wall->setWidth(ui->lineEdit->text().toInt());
    this->wall->setTop(ui->checkBox_3->isChecked());
    if(this->wall->isTop())
        this->wall->setColorTop(*this->itemSetting->color.at(ui->comboBox_4->currentIndex()));
    this->wall->setGirthRail(ui->checkBox_5->isChecked());
    this->wall->setPazzle(ui->checkBox_4->isChecked());
    this->wall->clearColorRow();
    if(this->wall->isPazzle())
    {
        this->wall->setColorPazzle(0,*this->itemSetting->color.at(ui->comboBox_2->currentIndex()));
        this->wall->setColorPazzle(1,*this->itemSetting->color.at(ui->comboBox_3->currentIndex()));
    }else
    {
        foreach(QColor qcolor,ui->widget->getColorAllRow())
            foreach(COLOR *color,this->itemSetting->color)
                if(color->color==qcolor)
                    this->wall->addColorRow(*color);
    }
    if(ui->radioButton_4->isChecked())
        this->wall->setDecoreid(0);
    if(ui->radioButton->isChecked())
    {
        this->wall->setDecoreid(1);
        this->wall->setColorDecoreid(*this->itemSetting->color.at(ui->comboBox_5->currentIndex()));
    }
    if(ui->radioButton_2->isChecked())
    {
        this->wall->setDecoreid(2);
        this->wall->setColorDecoreid(*this->itemSetting->color.at(ui->comboBox_6->currentIndex()));
        qDebug()<<this->itemSetting->color.at(ui->comboBox_6->currentIndex())->caption;
    }
    if(ui->radioButton_3->isChecked())
    {
        this->wall->setDecoreid(3);
        this->wall->setColorDecoreid(*this->itemSetting->color.at(ui->comboBox_7->currentIndex()));
    }
    emit this->closeProperties(ITEM_WALL,ui->checkBox_2->isChecked());*/
}

void PropertiesWallWindow::closeEvent(QCloseEvent *event)
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

void PropertiesWallWindow::on_pushButton_5_clicked()
{
    this->close();
}

void PropertiesWallWindow::on_radioButton_clicked()
{
//    ui->widget->setEnableDecoreit(true,this->itemSetting->color.at(ui->comboBox_5->currentIndex())->color,false,QColor(),false,QColor());
}

void PropertiesWallWindow::on_comboBox_5_activated(int index)
{
//    ui->widget->setEnableDecoreit(ui->radioButton->isChecked(),this->itemSetting->color.at(index)->color,false,QColor(),false,QColor());
}

void PropertiesWallWindow::on_radioButton_2_clicked()
{
//    ui->widget->setEnableDecoreit(false,QColor(),true,this->itemSetting->color.at(ui->comboBox_6->currentIndex())->color,false,QColor());
}

void PropertiesWallWindow::on_comboBox_6_activated(int index)
{
//   ui->widget->setEnableDecoreit(false,QColor(),ui->radioButton_2->isChecked(),this->itemSetting->color.at(index)->color,false,QColor());
}

void PropertiesWallWindow::on_radioButton_3_clicked()
{
//    ui->widget->setEnableDecoreit(false,QColor(),false,QColor(),true,this->itemSetting->color.at(ui->comboBox_7->currentIndex())->color);
}

void PropertiesWallWindow::on_comboBox_7_activated(int index)
{
//    ui->widget->setEnableDecoreit(false,QColor(),false,QColor(),ui->radioButton_3->isChecked(),this->itemSetting->color.at(index)->color);
}

void PropertiesWallWindow::on_radioButton_4_clicked()
{
    ui->widget->setEnableDecoreit(false,QColor(),false,QColor(),false,QColor());
}
