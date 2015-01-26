#include "settingswindow.h"
#include "ui_settingswindow.h"
#include "QDebug"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    this->settingItem=NULL;
    ui->label_10->installEventFilter(this);
    ui->label_10->setStyleSheet("border: 1px solid #000000; background-color:white");
    this->saveFlag=false;
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::SetSettingItem(SETTINGS *settingItem)
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
    foreach(COLOR* color,this->settingItem->color)
    {
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(" "));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(color->caption));
        ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setBackground(QBrush(color->color));
    }
}

void SettingsWindow::on_pushButton_3_clicked()
{


}

void SettingsWindow::on_pushButton_4_clicked()//Добавление цвета в таблицу
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(" "));
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(ui->lineEdit_2->text()));
    QStringList colorNames;
    colorNames = QColor::colorNames();
    ui->tableWidget->item(ui->tableWidget->rowCount()-1,0)->setBackground(ui->label_10->palette().background());
}

void SettingsWindow::on_pushButton_5_clicked()//Удаление цвета из таблицы
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}

void SettingsWindow::on_pushButton_2_clicked()
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
    if(event->type() == QEvent::MouseButtonPress)
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
         }
}

void SettingsWindow::save()
{
    this->settingItem->color.clear();
    this->settingItem->minWidthBrickR=ui->lineEdit_5->text().toInt()>0?ui->lineEdit_5->text().toInt():1;
    this->settingItem->maxWidthBrickR=ui->lineEdit_6->text().toInt()>0?ui->lineEdit_6->text().toInt():1;
    this->settingItem->heightBrickR=ui->lineEdit_7->text().toInt()>0?ui->lineEdit_7->text().toInt():1;
    this->settingItem->heightBrickAngle=ui->lineEdit_4->text().toInt()>0?ui->lineEdit_4->text().toInt():1;
    this->settingItem->minWidthGirth=ui->lineEdit->text().toInt()>0?ui->lineEdit->text().toInt():1;
    this->settingItem->maxWidthGirth=ui->lineEdit_3->text().toInt()>0?ui->lineEdit_3->text().toInt():1;
    this->settingItem->widthWallTop=ui->lineEdit_8->text().toInt()>0?ui->lineEdit_8->text().toInt():1;
    for (int i=0;i<ui->tableWidget->rowCount();i++)
        this->settingItem->color.append(new COLOR(ui->tableWidget->item(i,0)->backgroundColor(),ui->tableWidget->item(i,1)->text()));
    this->settingItem=NULL;
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    if(!this->saveFlag)
    {
        int result=QMessageBox::warning(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Сохранить измененые данные?"),
                             QMessageBox::Ok,QMessageBox::Cancel);
        if(result==QMessageBox::Ok)
            this->save();
    }
    QMainWindow::closeEvent(event);
}
