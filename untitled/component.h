#ifndef COMPONENT_H
#define COMPONENT_H

#include <QDialog>
#include "propertiesitem.h"
namespace Ui {
class Component;
}

class Component : public QDialog
{
    Q_OBJECT
    
public:
    explicit Component(QWidget *parent = 0);
    ~Component();
signals:
    void isTypeComponent(TYPEITEM type,int width);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Component *ui;
};

#endif // COMPONENT_H
