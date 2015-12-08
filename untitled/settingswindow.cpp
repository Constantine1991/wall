#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "QDebug"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->settingItem=NULL;
    this->saveFlag=false;
    this->isLoadImg1=false;
    this->isLoadImg2=false;
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::SetSettingItem(SettingItem *settingItem)
{
    this->settingItem=settingItem;
    if(this->settingItem==NULL)
        return;
    ui->lineEdit_5->setText(QString::number(this->settingItem->minWidthBrickR));
    ui->lineEdit_6->setText(QString::number(this->settingItem->maxWidthBrickR));
    ui->lineEdit_7->setText(QString::number(this->settingItem->heightBrickR));
    ui->lineEdit_4->setText(QString::number(this->settingItem->heightBrickAngle));
    ui->lineEdit->setText(QString::number(this->settingItem->minWidthGirth));
    ui->lineEdit_3->setText(QString::number(this->settingItem->maxWidthGirth));
    ui->lineEdit_8->setText(QString::number(this->settingItem->widthWallTop));
    for(int i=0;i<(int)SettingItem::COLOR_BRICK_TYPE_ALL;i++)
        ui->comboBox->addItem(this->settingItem->nameType(i));
    this->setHeaderTable(this->settingItem->colorType(ui->comboBox->currentIndex()));
    this->setBlockLoadImage(this->settingItem->colorType(ui->comboBox->currentIndex()));
}

void SettingsWindow::on_pushButton_3_clicked()//Загрузить кртинку 1
{
    this->isLoadImg1=this->img1.load(this->pathImage());
    if(!this->isLoadImg1)
        return;
    ui->label_2->setPixmap(QPixmap::fromImage(this->img1));
}

void SettingsWindow::on_pushButton_6_clicked()//Загрузить кртинку 2
{
    this->isLoadImg2=this->img2.load(this->pathImage());
    if(!this->isLoadImg2)
        return;
    ui->label_16->setPixmap(QPixmap::fromImage(this->img2));
}

void SettingsWindow::on_pushButton_4_clicked()//Добавление цвета в таблицу
{
    if(ui->lineEdit_9->text().isEmpty())
    {
        QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),
                           QString::fromLocal8Bit("Заполните пустое поле название цвета"));
        return;
    }
    SettingItem::COLOR_BRICK_TYPE type=this->settingItem->colorType(ui->comboBox->currentIndex());
    if(type==SettingItem::COLOR_BRICK_PILLAR_TOP || type==SettingItem::COLOR_BRICK_WALL_BIG ||
       type==SettingItem::COLOR_BRICK_WALL_BOTTOM || type==SettingItem::COLOR_BRICK_WALL_SMALL ||
       type==SettingItem::COLOR_BRICK_WALL_TOP)
    {
        if(!this->isValidateBlockImage1())
            return;
        if(!this->settingItem->append(type,SettingItem::COLOR_BRICK(ui->lineEdit_9->text(),
                                                                    ui->lineEdit_2->text(),
                                                                    this->img1)))
        {
            QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),
                               QString::fromLocal8Bit("Данные вводимых полях должны быть уникальны!\nПроверьте вводимые поля!"));
            return;
        }
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(ui->lineEdit_9->text()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(ui->lineEdit_2->text()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(" "));
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,
                              2)->setBackground(QBrush(this->img1.scaled(128,64)));

    }else{
        if(!this->isValidateBlockImage1() || !this->isValidateBlockImage2())
            return;
        if(ui->lineEdit_2->text()==ui->lineEdit_10->text())
        {
            QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Название изображений должны быть уникальными"));
            return;
        }
        if(!this->settingItem->append(type,SettingItem::COLOR_BRICK(ui->lineEdit_9->text(),
                                                                    ui->lineEdit_2->text(),
                                                                    this->img1,
                                                                    ui->lineEdit_10->text(),
                                                                    this->img2)))
        {
            QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),
                               QString::fromLocal8Bit("Данные вводимых полях должны быть уникальны!\nПроверьте вводимые поля!"));
            return;
        }
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(ui->lineEdit_9->text()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(ui->lineEdit_2->text()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(" "));
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,
                              2)->setBackground(QBrush(this->img1.scaled(128,64)));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(ui->lineEdit_10->text()));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(" "));
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,
                              4)->setBackground(QBrush(this->img2.scaled(128,64)));

    }
    ui->lineEdit_9->clear();
    ui->label_2->clear();
    this->isLoadImg1=false;
    ui->lineEdit_2->clear();
    ui->label_16->clear();
    this->isLoadImg2=false;
    ui->lineEdit_10->clear();
    this->setHeaderTable(this->settingItem->colorType(ui->comboBox->currentIndex()));
}

void SettingsWindow::on_pushButton_5_clicked()//Удаление цвета из таблицы
{
    if(ui->tableWidget->currentRow()==-1)
    {
        QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Выделите запись в таблице"));
        return;
    }
    this->settingItem->remove(this->settingItem->colorType(ui->comboBox->currentIndex()),
                              ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void SettingsWindow::on_pushButton_2_clicked()//Закрыть окно настроек
{
    this->close();
}

void SettingsWindow::on_pushButton_clicked()//Сохранение настроек
{
    this->saveFlag=true;
    this->save();
    this->close();
}

void SettingsWindow::on_label_10_linkActivated(const QString &link)
{

}

bool SettingsWindow::eventFilter(QObject *obj, QEvent *event)
{
    /*if(event->type() == QEvent::MouseButtonPress)
        {
            // Выбор цвета из палитры цветов
            QColor color=QColorDialog::getColor(Qt::white,this);
            if(color.isValid())
                ui->label_10->setStyleSheet("border: 1px solid #000000; background-color:"+color.name()+";");
            return true;
        }
        else {
             // standard event processing
             return QObject::eventFilter(obj, event);
         }*/
    return QObject::eventFilter(obj, event);
}

void SettingsWindow::save()
{
    this->settingItem->minWidthBrickR=ui->lineEdit_5->text().toInt()>0?ui->lineEdit_5->text().toInt():1;
    this->settingItem->maxWidthBrickR=ui->lineEdit_6->text().toInt()>0?ui->lineEdit_6->text().toInt():1;
    this->settingItem->heightBrickR=ui->lineEdit_7->text().toInt()>0?ui->lineEdit_7->text().toInt():1;
    this->settingItem->heightBrickAngle=ui->lineEdit_4->text().toInt()>0?ui->lineEdit_4->text().toInt():1;
    this->settingItem->minWidthGirth=ui->lineEdit->text().toInt()>0?ui->lineEdit->text().toInt():1;
    this->settingItem->maxWidthGirth=ui->lineEdit_3->text().toInt()>0?ui->lineEdit_3->text().toInt():1;
    this->settingItem->widthWallTop=ui->lineEdit_8->text().toInt()>0?ui->lineEdit_8->text().toInt():1;
    this->settingItem->save();
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    if(!this->saveFlag)
    {
        int result=QMessageBox::warning(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Сохранить измененые данные?"),
                             QMessageBox::Ok,QMessageBox::Cancel);
        if(result==QMessageBox::Ok)
            this->save();
        if(result==QMessageBox::Cancel)
            this->settingItem->dontSave();
    }
    QMainWindow::closeEvent(event);
}

void SettingsWindow::on_comboBox_activated(int index)
{
    this->setHeaderTable(this->settingItem->colorType(index));
    this->setBlockLoadImage(this->settingItem->colorType(index));
}

//---------------------------------private------------------------------------------------//

void SettingsWindow::setHeaderTable(SettingColor::COLOR_BRICK_TYPE type)
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    switch(type)
    {
        case SettingItem::COLOR_BRICK_PILLAR_TOP:{
            ui->tableWidget->setColumnCount(3);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(this->settingItem->nameType(SettingItem::COLOR_BRICK_PILLAR_TOP)));
            break;
        }
        case SettingItem::COLOR_BRICK_PILLAR_BIG:{
            ui->tableWidget->setColumnCount(5);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("Брик угловой большой")));
            ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QString::fromLocal8Bit("Брик угловой маленький")));
            break;
        }
        case SettingItem::COLOR_BRICK_PILLAR_SMALL:{
            ui->tableWidget->setColumnCount(5);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("Брик угловой вставка правый")));
            ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QString::fromLocal8Bit("Брик угловой вставка левый")));
            break;
        }
        case SettingItem::COLOR_BRICK_PILLAR_BOTTOM:{
            ui->tableWidget->setColumnCount(5);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("Основание столба с вставкой")));
            ui->tableWidget->setHorizontalHeaderItem(3,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(4,new QTableWidgetItem(QString::fromLocal8Bit("Основание столба без вставки")));
            break;
        }
        case SettingItem::COLOR_BRICK_WALL_TOP:{
            ui->tableWidget->setColumnCount(3);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("Крышка полотна")));
            break;
        }
        case SettingItem::COLOR_BRICK_WALL_BIG:{
            ui->tableWidget->setColumnCount(3);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("Брик рядовой")));
            break;
        }
        case SettingItem::COLOR_BRICK_WALL_SMALL:{
            ui->tableWidget->setColumnCount(3);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("Брик рядовой доборный")));
            break;
        }
        case SettingItem::COLOR_BRICK_WALL_BOTTOM:{
            ui->tableWidget->setColumnCount(3);
            ui->tableWidget->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromLocal8Bit("Название цвета")));
            ui->tableWidget->setHorizontalHeaderItem(1,new QTableWidgetItem(QString::fromLocal8Bit("Название картинки")));
            ui->tableWidget->setHorizontalHeaderItem(2,new QTableWidgetItem(QString::fromLocal8Bit("Ригель")));
            break;
        }
        default:break;
    }
    this->showDataTable(type);
}

void SettingsWindow::showDataTable(SettingColor::COLOR_BRICK_TYPE type)
{
    foreach(SettingItem::COLOR_BRICK *brick,this->settingItem->colorBrick(type))
    {
        qDebug()<<brick->change;
        if(brick->change==SettingColor::CHANGE_REMOVE)
            continue;
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(brick->nameColor));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(brick->nameImage1));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,new QTableWidgetItem(""));
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,
                              2)->setBackground(QBrush(brick->image1.scaled(128,64)));
        if(ui->tableWidget->columnCount()==5)
        {
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,new QTableWidgetItem(brick->nameImage2));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,new QTableWidgetItem(""));
            ui->tableWidget->item(ui->tableWidget->rowCount()-1,
                                  4)->setBackground(QBrush(brick->image2.scaled(128,64)));
        }
    }


}

void SettingsWindow::setBlockLoadImage(SettingColor::COLOR_BRICK_TYPE type)
{
    ui->label_2->clear();
    this->isLoadImg1=false;
    ui->label_16->clear();
    this->isLoadImg2=false;
    if(type==SettingItem::COLOR_BRICK_PILLAR_TOP || type==SettingItem::COLOR_BRICK_WALL_BIG ||
       type==SettingItem::COLOR_BRICK_WALL_BOTTOM || type==SettingItem::COLOR_BRICK_WALL_SMALL ||
       type==SettingItem::COLOR_BRICK_WALL_TOP)
    {
        ui->label_15->setVisible(false);
        ui->pushButton_6->setVisible(false);
        ui->label_16->setVisible(false);
        ui->label_17->setVisible(false);
        ui->lineEdit_10->setVisible(false);
    }else{
        ui->label_15->setVisible(true);
        ui->pushButton_6->setVisible(true);
        ui->label_16->setVisible(true);
        ui->label_17->setVisible(true);
        ui->lineEdit_10->setVisible(true);
    }
    switch(type)
    {
        case SettingItem::COLOR_BRICK_PILLAR_TOP:{
            ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nкрышки столба:"));
            break;
        }
        case SettingItem::COLOR_BRICK_PILLAR_BIG:{
             ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nбрик угловой большой:"));
             ui->label_15->setText(QString::fromLocal8Bit("Загрузите изображение\nбрик угловой маленький:"));
             break;
        }
        case SettingItem::COLOR_BRICK_PILLAR_SMALL:{
             ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nбрик угловой вставка правый:"));
             ui->label_15->setText(QString::fromLocal8Bit("Загрузите изображение\nбрик угловой вставка левый:"));
             break;
        }
        case SettingItem::COLOR_BRICK_PILLAR_BOTTOM:{
             ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nоснование столба с вставкой:"));
             ui->label_15->setText(QString::fromLocal8Bit("Загрузите изображение\nоснование столба без вставки:"));
             break;
        }
        case SettingItem::COLOR_BRICK_WALL_TOP:{
             ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nкрышки полотна:"));
             break;
        }
        case SettingItem::COLOR_BRICK_WALL_BIG:{
             ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nбрик рядовой:"));
             break;
        }
        case SettingItem::COLOR_BRICK_WALL_SMALL:{
             ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nбрик рядовой доборный:"));
             break;
        }
        case SettingItem::COLOR_BRICK_WALL_BOTTOM:{
             ui->label_10->setText(QString::fromLocal8Bit("Загрузите изображение\nригель:"));
             break;
        }
        default:break;
    }
}

bool SettingsWindow::isValidateBlockImage1()
{
    if(!this->isLoadImg1)
    {
        QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Загрузите картинку №1"));
        return false;
    }
    if(ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Дайте имя картинке №1"));
        return false;
    }
    return true;
}

bool SettingsWindow::isValidateBlockImage2()
{
    if(!this->isLoadImg2)
    {
        QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Загрузите картинку №2"));
        return false;
    }
    if(ui->lineEdit_10->text().isEmpty())
    {
        QMessageBox::about(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Дайте имя картинке №2"));
        return false;
    }
    return true;
}

QString SettingsWindow::pathImage()
{
    return QFileDialog::getOpenFileName(this,"","","BMP (*.bmp);;PNG (*.png);;JPEG (*.jpg *.jpeg);;");
}




