#ifndef CRYPTXOR_H
#define CRYPTXOR_H

#include <QByteArray>
#include <Qt/qmessagebox.h>
#include <QFile>

class CryptXor{
public:
    CryptXor();
    QByteArray Crypt(QByteArray open_key, QString filename);
    bool Decrypt(QByteArray open_key, QString filename);
};
                                                                                                                                                                                                                                                                                                                                      #endif //CRYPTXOR_H
