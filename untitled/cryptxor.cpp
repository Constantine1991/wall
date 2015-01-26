#include "cryptxor.h"

CryptXor::CryptXor()
{
}

QByteArray CryptXor::Crypt(QByteArray open_key, QString filename)
{
    QByteArray data;
    data.append("IMaxiprogramTest");
    QByteArray private_key;
    for (int i=0;i<16;i++)
    {
        private_key.append(data.at(i)^open_key.at(i));
    }


    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(private_key);
            file.close();
        }else
            QMessageBox::critical(0,QString::fromLocal8Bit("Формирование личного ключа"),
                                  QString::fromLocal8Bit("Не удается открыть файл!"));
    }

    return private_key;
}

bool CryptXor::Decrypt(QByteArray open_key, QString filename)
{
    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly))
        {
            QByteArray private_key;
            private_key=file.read(16);
            file.close();
            QByteArray result;
            for (int i=0;i<16;i++)
            {
                result.append(private_key.at(i)^open_key.at(i));
            }
            //QMessageBox::about(0,"result",result);
            if (result=="IMaxiprogramTest")
                return true;
            else
                return false;
        }else
            QMessageBox::critical(0,QString::fromLocal8Bit("Проверка личного ключа"),
                                  QString::fromLocal8Bit("Не удается открыть файл!"));
    }

    return false;
}
