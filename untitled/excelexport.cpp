#include "excelexport.h"

ExcelExport::ExcelExport()
{
}

void ExcelExport::Open(QString filename, QObject* parent)
{
    excel=new QAxObject("Excel.Application",parent);
    excel->dynamicCall("SetVisible(bool)",true);
    workbooks=excel->querySubObject("Workbooks");
    workbook=workbooks->querySubObject("Open(const QString&)",filename);
    sheets=workbook->querySubObject("Sheets");
    sheet=sheets->querySubObject("Item(const QVariant&)",QVariant("1"));
    sheet->dynamicCall( "Select()" );
}

void ExcelExport::SetBlokUg(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D12")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetColorBlockUg(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("E12")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetBlokUgPrim(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D13")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetColorBlokUgPrim(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("E13")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetBlokRad(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D14")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetColorBlokRad(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("E14")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetBlokRadDob(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D15")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetColorBlokRadDob(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("E15")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetRigel2850(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D16")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetRigel4050(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D17")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetKrishka450(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D23")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetColorKrishka450(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("E23")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetKrishka500(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D24")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::SetColorKrishka500(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("E24")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::setTray(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D27")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::setPillarBase1(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D18")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::setPillarBase2(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D19")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::setPillarBase3(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D20")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::setPillarBase4(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D21")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}

void ExcelExport::setPillarBase5(QString value)
{
    if (!sheet->isNull())
    {
        QAxObject* range=sheet->querySubObject("Range(const QVariant&)",QVariant(QString("D22")));
        range->dynamicCall("SetValue(const QVariant&)",QVariant(value));
    }
}
