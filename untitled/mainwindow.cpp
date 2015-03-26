#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->settingItem=new SETTINGS();
    ui->widget->setSettingItem(this->settingItem);
    this->LoadSettingItem();
    this->nameFile="";
    ////////////////////////
    QPixmap pixmap(250, 250);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter.setBrush(Qt::white);
    painter.translate(10, 10);
    painter.drawEllipse(0,0,230,230);
    QIcon iconPillar(pixmap);
    ui->pushButton->setIcon(iconPillar);
    ui->pushButton->setIconSize(QSize(32,32));
    ///////////////////////////////////////////////////////
    QPixmap pixmap1(250, 250);
    pixmap1.fill(Qt::transparent);
    QPainter painter1(&pixmap1);
    painter1.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter1.translate(10, 10);
    painter1.drawLine(10,125,230,125);
    QIcon iconWall(pixmap1);
    ui->pushButton_2->setIcon(iconWall);
    ui->pushButton_2->setIconSize(QSize(32,32));
    //////////////////////////////////////////////
    QPixmap pixmap2(250, 250);
    pixmap2.fill(Qt::transparent);
    QPainter painter2(&pixmap2);
    painter2.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter2.translate(10, 10);
    painter2.setBrush(Qt::white);
    painter2.drawEllipse(QPoint(20,125),35,35);
    painter2.setBrush(Qt::black);
    painter2.drawLine(20,50,210,50);
    painter2.drawLine(50,125,95,210);
    painter2.drawLine(180,125,135,210);
    painter2.setBrush(Qt::white);
    painter2.drawEllipse(QPoint(210,125),35,35);
    QIcon iconGateA(pixmap2);
    ui->pushButton_3->setIcon(iconGateA);
    ui->pushButton_3->setIconSize(QSize(32,32));
    //////////////////////////////////////////////////////////
    QPixmap pixmap3(250, 250);
    pixmap3.fill(Qt::transparent);
    QPainter painter3(&pixmap3);
    painter3.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter3.translate(10, 10);
    painter3.setBrush(Qt::black);
    painter3.drawLine(0,60,230,60);
    painter3.drawLine(0,60,0,185);
    painter3.drawLine(0,185,230,185);
    painter3.drawLine(230,60,230,185);
    painter3.drawLine(30,185,30,100);
    painter3.drawLine(60,185,60,120);
    painter3.drawLine(90,185,90,100);
    painter3.drawLine(120,185,120,120);
    painter3.drawLine(150,185,150,100);
    painter3.drawLine(180,185,180,120);
    painter3.drawLine(210,185,210,100);
    QIcon iconGateB(pixmap3);
    ui->pushButton_4->setIcon(iconGateB);
    ui->pushButton_4->setIconSize(QSize(32,32));
    //////////////////////////////////////////////////////////////////////
    /*QPixmap pixmap4(250, 250);
    pixmap4.fill(Qt::transparent);
    QPainter painter4(&pixmap4);
    painter4.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter4.translate(10, 10);
    painter4.setBrush(Qt::white);
    painter4.drawRect(0,75,230,100);
    QIcon iconGateC(pixmap4);
    ui->pushButton_5->setIcon(iconGateC);
    ui->pushButton_5->setIconSize(QSize(32,32));*/
    ui->pushButton_8->setVisible(false);
    /////////////////////////////////////////////////////////////////////////
    QPixmap pixmap5(250, 250);
    pixmap5.fill(Qt::transparent);
    QPainter painter5(&pixmap5);
    painter5.setPen(QPen(Qt::black, 6, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
    painter5.translate(10, 10);
    painter5.setBrush(Qt::black);
    painter5.drawEllipse(QPoint(20,125),30,30);
    painter5.drawLine(50,125,100,105);
    painter5.drawLine(50,125,100,145);
    painter5.drawLine(30,125,200,125);
    painter5.drawLine(190,125,150,105);
    painter5.drawLine(190,125,150,145);
    painter5.drawEllipse(QPoint(210,125),30,30);
    QIcon iconLine(pixmap5);
    ui->pushButton_5->setIcon(iconLine);
    ui->pushButton_5->setIconSize(QSize(32,32));
}

MainWindow::~MainWindow()
{
    this->SaveSettingItem();
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->widget->setTypeItem(ITEM_PILLAR);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->widget->setTypeItem(ITEM_WALL);
}

void MainWindow::isTypeComponent(TYPEITEM type, int width)
{
    if(type==ITEM_NONE || width==0)
        return;
    ui->widget->setTypeItem(type,width);
}

void MainWindow::on_pushButton_3_clicked()
{
    Component *c=new Component(this);
    connect(c,SIGNAL(isTypeComponent(TYPEITEM,int)),this,SLOT(isTypeComponent(TYPEITEM,int)));
    c->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->widget->setTypeItem(ITEM_LINE);
}

void MainWindow::on_pushButton_5_clicked()
{
        ui->widget->setTypeItem(ITEM_FILLING);
}

void MainWindow::on_action_6_activated()
{
    SettingsWindow *Setting=new SettingsWindow(this);
    Setting->SetSettingItem(this->settingItem);
    Setting->show();
}

void MainWindow::SaveSettingItem() // Сохранение структуры настроек компонентов
{
    QFile saveFile("setting.dat");
    if(!saveFile.open(QIODevice::WriteOnly))
        return;
    QDataStream outFile(&saveFile);
    outFile<<this->settingItem->minWidthBrickR<<this->settingItem->maxWidthBrickR<<this->settingItem->heightBrickR
          <<this->settingItem->heightBrickAngle<<this->settingItem->minWidthGirth<<this->settingItem->maxWidthGirth
          <<this->settingItem->widthWallTop<<this->settingItem->color.count();
    foreach(COLOR* color,this->settingItem->color)
        outFile<<color->color.name()<<color->caption;
    this->settingItem->color.clear();
    delete this->settingItem;
}

void MainWindow::LoadSettingItem() // Загрузка структуры настроек компонентов
{
    QFile loadFile("setting.dat");
    if(!loadFile.open(QIODevice::ReadOnly))
        return;
    QDataStream inFile(&loadFile);
    int sizeColor=0;
    inFile>>this->settingItem->minWidthBrickR>>this->settingItem->maxWidthBrickR>>this->settingItem->heightBrickR
         >>this->settingItem->heightBrickAngle>>this->settingItem->minWidthGirth>>this->settingItem->maxWidthGirth
         >>this->settingItem->widthWallTop>>sizeColor;
    for(int i=0;i<sizeColor;i++)
    {
        QString nameColor;
        QString captionColor;
        inFile>>nameColor>>captionColor;
        this->settingItem->color.append(new COLOR(QColor(nameColor),captionColor));
    }
}

void MainWindow::on_action_3_activated()// Сохранить проект
{
    this->saveFlag=true;
    ui->widget->Fundament=ui->checkBox_2->isChecked();
    ui->widget->SaveDiagramScene(this->nameFile);
}

void MainWindow::on_action_activated()// Создать новый проект
{
    int result=QMessageBox::warning(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Сохранить текущий проект?"),
                         QMessageBox::Ok,QMessageBox::Cancel);
    if(result==QMessageBox::Ok)
    {
        if(!this->nameFile.isEmpty())
            ui->widget->SaveDiagramScene(this->nameFile);
        else
        {
            this->nameFile=QFileDialog::getSaveFileName(this,"","","*.dm");
            if(!this->nameFile.isEmpty())
                ui->widget->SaveDiagramScene(this->nameFile);
        }
        this->saveFlag=false;
        this->nameFile="";
        ui->widget->ClearScene();
    }
    else{
        this->saveFlag=false;
        this->nameFile="";
        ui->widget->ClearScene();
    }
}

void MainWindow::on_action_2_activated()//Открыть проект
{
    this->nameFile=QFileDialog::getOpenFileName(this,"","","*.dm");
    if(!this->nameFile.isEmpty())
    {
        ui->widget->LoadDiagramScene(this->nameFile);
        this->saveFlag=false;
        ui->checkBox_2->setChecked(ui->widget->Fundament);
    }
}

void MainWindow::on_action_9_activated()// Сохранить проект как
{
    this->nameFile=QFileDialog::getSaveFileName(this,"","","*.dm");
    if(!this->nameFile.isEmpty())
    {
        ui->widget->Fundament=ui->checkBox_2->isChecked();
        ui->widget->SaveDiagramScene(this->nameFile);
        this->saveFlag=true;
    }
}

void MainWindow::on_action_4_activated()//Печать предпросмотр диаграммы
{
   ui->widget->PrintDiagram();
}

void MainWindow::on_action_5_activated()
{
    ui->widget->PrintContract();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(!this->saveFlag)
    {
        int result=QMessageBox::warning(this,QString::fromLocal8Bit("Сообщение!"),QString::fromLocal8Bit("Сохранить проект?"),
                             QMessageBox::Ok,QMessageBox::Cancel);
        if(result==QMessageBox::Ok)
        {
            if(!this->nameFile.isEmpty())
                ui->widget->SaveDiagramScene(this->nameFile);
            else
            {
                this->nameFile=QFileDialog::getSaveFileName(this,"","","*.dm");
                if(!this->nameFile.isEmpty())
                    ui->widget->SaveDiagramScene(this->nameFile);
            }
        }
    }
    QMainWindow::closeEvent(event);
}

void MainWindow::on_action_7_activated()
{
    about *a=new about(this);
    a->show();
}

void MainWindow::on_action_8_activated()
{
    this->close();
}

void MainWindow::on_pushButton_8_clicked()
{

}
