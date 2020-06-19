#ifndef COMP_H
#define COMP_H

#include <QFile>
#include <QString>
#include <QDir>
#include <QFileInfoList>
#include <QFileInfo>
#include <QCryptographicHash>

#include <QDebug>

class Comp
{
private:
    std::vector<QFile *> fold1;
    std::vector<QFile *> fold2;
public:
    Comp();
    void setFold1(QDir);
    void setFold2(QDir);
    QStringList compare();
};

#endif // COMP_H
