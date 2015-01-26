#ifndef EXCELEXPORT_H
#define EXCELEXPORT_H

#include <qaxobject.h>

#include <QMessageBox>

//Для работоспособности подключить библиотеку в проект "QT += axcontainer"
class ExcelExport
{
public:
    ExcelExport();
    //Открыть Excel под именем "filename", родитель Excel процесса "parent"
    void Open(QString filename, QObject* parent=0);
    //Задать значение для "Блок угловой 250х100х100"
    void SetBlokUg(QString value);
    void SetColorBlockUg(QString value);
    //Задать значение для "Блок угловой примыкания 250х100х100"
    void SetBlokUgPrim(QString value);
    void SetColorBlokUgPrim(QString value);
    //Задать значение для "Блок рядовой 300х100х100"
    void SetBlokRad(QString value);
    void SetColorBlokRad(QString value);
    //Задать значение для "Блок рядовой доборный 150х100х100"
    void SetBlokRadDob(QString value);
    void SetColorBlokRadDob(QString value);
    //Задать значение для "Ригель-основание полотна забора L=2850мм"
    void SetRigel2850(QString value);
    //Задать значение для "Ригель-основание полотна забора L=4050мм"
    void SetRigel4050(QString value);
    //Задать значение для "Крышка столба забора 450х450"
    void SetKrishka450(QString value);
    void SetColorKrishka450(QString value);
    //Задать значение для "Крышка полотна забора 500х180"
    void SetKrishka500(QString value);
    void SetColorKrishka500(QString value);
    //Задать общее количество поддонов
    void setTray(QString value);
    //Задать количество основний столба глухое
    void setPillarBase1(QString value);
    //Задать количество основний столба начальное/конечное
    void setPillarBase2(QString value);
    //Задать количество основний столба проходное
    void setPillarBase3(QString value);
    //Задать количество основний столба угловое двойное
    void setPillarBase4(QString value);
    //Задать количество основний столба угловое тройное
    void setPillarBase5(QString value);
private:
    QAxObject* excel;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* sheets;
    QAxObject* sheet;
};

#endif // EXCELEXPORT_H
