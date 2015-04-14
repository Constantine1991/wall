#include "activationwindow.h"
#include "ui_activationwindow.h"

ActivationWindow::ActivationWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ActivationWindow)
{
    ui->setupUi(this);
}

ActivationWindow::~ActivationWindow()
{
    delete ui;
}

void ActivationWindow::on_pushButton_3_clicked()
{
    QByteArray open_key;
    QByteArray date;

    open_key.append(QByteArray::fromHex(ui->lineEdit_open_key->text().toLocal8Bit()));

    //qDebug()<<open_key;

    if (open_key.size()==16)
    {
        CryptXor cr;
        if (cr.Decrypt(open_key,"private.key"))
        {
            QSettings set("MaxiProgram","WebSiteDesign");
            set.setValue("setting0",open_key);
            QByteArray tmp;
            tmp.append(QDateTime::currentDateTime().toString());
            date=QCryptographicHash::hash(tmp,QCryptographicHash::Md5);
            set.setValue("setting1",date);

            QFile file("private.key");
            //qDebug()<<"Size file="<<file.size();
            if (file.size()==16)
            {
                if (file.open(QIODevice::Append))
                {
                    file.seek(16);
                    file.write(date);
                    file.close();
                }
            }

            this->parentWidget()->show();
            this->close();
        }else
            QMessageBox::about(this,QString::fromLocal8Bit("Проверка активационного ключа"),
                               QString::fromLocal8Bit("Неверный активационный ключ!"));
    }else
        QMessageBox::about(this,QString::fromLocal8Bit("Проверка активационного ключа"),
                           QString::fromLocal8Bit("Неверный активационный ключ!"));
}

void ActivationWindow::on_pushButton_4_clicked()
{
    QApplication::exit();
}
