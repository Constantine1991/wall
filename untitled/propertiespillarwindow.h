#ifndef PROPERTIESPILLARWINDOW_H
#define PROPERTIESPILLARWINDOW_H

#include <QMainWindow>
#include <Qt/qmessagebox.h>
#include <QDesktopWidget>
#include <QDir>
#include <QComboBox>
#include "propertiesitem.h"
#include "graphicspillaritem.h"

namespace Ui {
class PropertiesPillarWindow;
}

class PropertiesPillarWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PropertiesPillarWindow(QWidget *parent = 0);
    ~PropertiesPillarWindow();
    void SetPropertiesPillar(GraphicsPillarItem *item,SettingItem *itemSetting,bool fundament=false);
    int heightBrick;
signals:
    void closeProperties(SettingItem::TYPEITEM itemType,bool all);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_activated(int index);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_checkBox_clicked();

    void on_comboBox_2_activated(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_3_activated(int index);

    void on_checkBox_5_clicked();

    void on_checkBox_3_clicked();

    void on_comboBox_4_activated(int index);

    void on_comboBox_5_activated(int index);
    void on_pushButton_2_clicked();

    void on_checkBox_2_clicked();

    void on_checkBox_6_clicked();

    void on_lineEdit_3_textEdited(const QString &arg1);

protected:
    void closeEvent(QCloseEvent *event);
private:
    void saveSetting();
    void setCurrentTextComboBox(QComboBox *comboBox,QString text);
    void setColorCommboBox(QComboBox *comboBox,QList<SettingItem::COLOR_BRICK*> listColor);
    Ui::PropertiesPillarWindow *ui;
    GraphicsPillarItem *Pillar;
    int lastIndexCheckBox;
    SettingItem *itemSetting;
    bool saveFlag;
};

#endif // PROPERTIESPILLARWINDOW_H
