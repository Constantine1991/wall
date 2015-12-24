#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QDataStream>
#include <QFileDialog>
#include "propertiesitem.h"
#include "propertieswallwindow.h"
#include "propertiespillarwindow.h"
#include "settingswindow.h"
#include "about.h"
#include "component.h"
#include "graphicssizewall.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_action_6_activated();

    void on_action_3_activated();

    void on_action_activated();

    void on_action_2_activated();

    void on_action_9_activated();

    void on_action_4_activated();

    void on_action_5_activated();
    void on_action_7_activated();

    void on_action_8_activated();

    void isTypeComponent(SettingItem::TYPEITEM type,int width);

    void on_checkBox_2_clicked();

    void action_aligment_length_item();

    void action_aligment_angle_item();

    void action_locking_item_scene();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    SettingItem  settingItem;
    void resetPushButton();
    void resetPushButton_2();
    QString nameFile;
    bool saveFlag;
    bool checkedPushButton;
    bool checkedPushButton_2;
};

#endif // MAINWINDOW_H
