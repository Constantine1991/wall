#ifndef EXCELEXPORT_H
#define EXCELEXPORT_H

#include <qaxobject.h>

#include <QMessageBox>

//��� ����������������� ���������� ���������� � ������ "QT += axcontainer"
class ExcelExport
{
public:
    ExcelExport();
    //������� Excel ��� ������ "filename", �������� Excel �������� "parent"
    void Open(QString filename, QObject* parent=0);
    //������ �������� ��� "���� ������� 250�100�100"
    void SetBlokUg(QString value);
    void SetColorBlockUg(QString value);
    //������ �������� ��� "���� ������� ���������� 250�100�100"
    void SetBlokUgPrim(QString value);
    void SetColorBlokUgPrim(QString value);
    //������ �������� ��� "���� ������� 300�100�100"
    void SetBlokRad(QString value);
    void SetColorBlokRad(QString value);
    //������ �������� ��� "���� ������� �������� 150�100�100"
    void SetBlokRadDob(QString value);
    void SetColorBlokRadDob(QString value);
    //������ �������� ��� "������-��������� ������� ������ L=2850��"
    void SetRigel2850(QString value);
    //������ �������� ��� "������-��������� ������� ������ L=4050��"
    void SetRigel4050(QString value);
    //������ �������� ��� "������ ������ ������ 450�450"
    void SetKrishka450(QString value);
    void SetColorKrishka450(QString value);
    //������ �������� ��� "������ ������� ������ 500�180"
    void SetKrishka500(QString value);
    void SetColorKrishka500(QString value);
    //������ ����� ���������� ��������
    void setTray(QString value);
    //������ ���������� �������� ������ ������
    void setPillarBase1(QString value);
    //������ ���������� �������� ������ ���������/��������
    void setPillarBase2(QString value);
    //������ ���������� �������� ������ ���������
    void setPillarBase3(QString value);
    //������ ���������� �������� ������ ������� �������
    void setPillarBase4(QString value);
    //������ ���������� �������� ������ ������� �������
    void setPillarBase5(QString value);
private:
    QAxObject* excel;
    QAxObject* workbooks;
    QAxObject* workbook;
    QAxObject* sheets;
    QAxObject* sheet;
};

#endif // EXCELEXPORT_H
