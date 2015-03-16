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

    void on_pushButton_8_clicked();
    void isTypeComponent(TYPEITEM type,int width);
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    SETTINGS * settingItem;
    void SaveSettingItem();
    void LoadSettingItem();
    QString nameFile;
    bool saveFlag;
};

#endif // MAINWINDOW_H
