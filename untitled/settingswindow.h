#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QPalette>
#include <QPainter>
#include <Qt/qmessagebox.h>
#include <QDir>
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
    void SetSettingItem(SETTINGS *settingItem);
    void save();
private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_label_10_linkActivated(const QString &link);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void closeEvent(QCloseEvent *event);
private:
    Ui::SettingsWindow *ui;
    SETTINGS *settingItem;
    bool saveFlag;
};

#endif // SETTINGSWINDOW_H
