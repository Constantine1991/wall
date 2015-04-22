/*#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}
*/
#include <QApplication>
#include "activationwindow.h"
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow m_f;
    ActivationWindow f(&m_f);

    QByteArray open_key;
    QByteArray date;
    QSettings set("MaxiProgram","WebSiteDesign");
    open_key=set.value("setting0").toByteArray();
    date=set.value("setting1").toByteArray();

    if (!open_key.isEmpty() || !date.isEmpty())
    {
        if (open_key.size()==16)
        {
            CryptXor cr;
            if (cr.Decrypt(open_key,"private.key"))
            {
                QFile file("private.key");
                if (file.open(QIODevice::ReadOnly))
                {
                    file.seek(16);
                    QByteArray date_f=file.read(16);
                    file.close();
                    if (date_f==date)
                    {
                        m_f.showMaximized();
                        return a.exec();
                    }else
                    {
                        QMessageBox::critical(&m_f,QString::fromLocal8Bit("������� ����������� ���������������"),
                                              QString::fromLocal8Bit("����������� ������ ��������!"));
                        return 0;
                    }
                }
            }
        }
    }

    f.show();

    return a.exec();
}
