#ifndef ACTIVATIONFORM_H
#define ACTIVATIONFORM_H

#include <QMainWindow>
#include <QWidget>
#include <Qt/qmessagebox.h>
#include <QSettings>
#include <QDateTime>
#include <QCryptographicHash>
#include "cryptxor.h""
namespace Ui {
class ActivationForm;
}

class ActivationForm : public QMainWindow
{
    Q_OBJECT
public:
     explicit ActivationForm(QWidget *parent);
    ~ActivationForm();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
private:
    Ui::ActivationForm *ui;
};
#endif
