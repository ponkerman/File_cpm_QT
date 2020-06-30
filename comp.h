#ifndef COMP_H
#define COMP_H

#include <QFile>
//#include <QString>
#include <QDir>
//#include <QFileInfoList>
//#include <QFileInfo>
#include <io.h>
#include <QDebug>

class Comp
{
private:
    std::vector<QFile *> fold1;
    std::vector<QFile *> fold2;
    void setFold(const QDir&, std::vector<QFile*> &);
public:
    Comp();
    ~Comp();
    bool isReady();
    void setFold1(const QDir&);
    void setFold2(const QDir&);

    QStringList compare();
};

#endif // COMP_H
