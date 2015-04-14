#ifndef ACTIVATIONWINDOW_H
#define ACTIVATIONWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <Qt/qmessagebox.h>
#include <QSettings>
#include <QDateTime>
#include <QCryptographicHash>
#include "cryptxor.h"

namespace Ui {
class ActivationWindow;
}

class ActivationWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ActivationWindow(QWidget *parent = 0);
    ~ActivationWindow();
    
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ActivationWindow *ui;
};

#endif // ACTIVATIONWINDOW_H
