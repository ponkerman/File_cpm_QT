#ifndef COMP_H
#define COMP_H

#include <QFile>
//#include <QString>
#include <QDir>
//#include <QFileInfoList>
//#include <QFileInfo>
#include <io.h>
#include <QDebug>
#include <QObject>

class Comp : public QObject
{
    Q_OBJECT
public slots:
    void compare();
signals:
    void send(const QString& str);
private:
    std::vector<QFile *> fold1;
    std::vector<QFile *> fold2;
    void setFold(const QDir&, std::vector<QFile*> &);
public:
    Comp();
    ~Comp();
    void setFold1(const QDir&);
    void setFold2(const QDir&);
    bool isReady();
};

#endif // COMP_H
