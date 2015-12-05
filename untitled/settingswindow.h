#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QPalette>
#include <QPainter>
#include <Qt/qmessagebox.h>
#include <QDir>
#include <QFileDialog>
#include <QPixmap>
#include <QTableWidget>
#include "propertiesitem.h"

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();
    void SetSettingItem(SettingItem *settingItem);
    void save();
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_label_10_linkActivated(const QString &link);
    void on_comboBox_activated(int index);

    void on_pushButton_6_clicked();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    Ui::SettingsWindow *ui;
    SettingItem *settingItem;
    bool saveFlag;
    QString dirGraphicFile;
    QImage img1;
    bool isLoadImg1;
    QImage img2;
    bool isLoadImg2;
    void setHeaderTable(SettingItem::COLOR_BRICK_TYPE type);
    void showDataTable(SettingItem::COLOR_BRICK_TYPE type);
    void setBlockLoadImage(SettingItem::COLOR_BRICK_TYPE type);
    bool isValidateBlockImage1();
    bool isValidateBlockImage2();
    QString  pathImage();
};

#endif // SETTINGSWINDOW_H
