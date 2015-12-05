#ifndef PROPERTIESWALLWINDOW_H
#define PROPERTIESWALLWINDOW_H

#include <QMainWindow>
#include <Qt/qmessagebox.h>
#include <QDir>
#include "propertiesitem.h"
#include "graphicspillaritem.h"

namespace Ui {
class PropertiesWallWindow;
}

class PropertiesWallWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit PropertiesWallWindow(QWidget *parent = 0);
    ~PropertiesWallWindow();
    void SetPropertiesWall(GraphicsWallItem *item, SettingItem *itemSetting,GraphicsPillarItem *itemPillar,bool fundament=false);
signals:
    void closeProperties(SettingItem::TYPEITEM itemType,bool all);
private slots:
    void on_pushButton_4_clicked();
    void on_lineEdit_textChanged(const QString &arg1);
    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_checkBox_3_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_checkBox_clicked();

    void on_checkBox_4_clicked();

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_comboBox_2_activated(int index);

    void on_comboBox_3_activated(int index);

    void on_comboBox_4_activated(int index);
    void on_pushButton_5_clicked();

    void on_radioButton_clicked();

    void on_comboBox_5_activated(int index);

    void on_radioButton_2_clicked();

    void on_comboBox_6_activated(int index);

    void on_radioButton_3_clicked();

    void on_comboBox_7_activated(int index);

    void on_radioButton_4_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void saveSetting();
    Ui::PropertiesWallWindow *ui;
    GraphicsWallItem *wall;
    SettingItem *itemSetting;
    GraphicsPillarItem *itemPillar;
    void changeRowWall();
    bool saveFlag;
};

#endif // PROPERTIESWALLWINDOW_H
