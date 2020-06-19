#include "comp.h"

Comp::Comp()
{

}

void Comp::setFold1(QDir fold)
{
   fold.setFilter(QDir::Files);
   fold.setSorting(QDir::Name);
   QString path = fold.path();

   QStringList list = fold.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);

   for(auto it : list){
       fold1.push_back(new QFile(path + '/' + it));
   }
}

void Comp::setFold2(QDir fold)
{
    fold.setSorting(QDir::Name);
    QString path = fold.path();

    QStringList list = fold.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);

    for(auto it : list){
        fold2.push_back(new QFile(path + '/' + it));
    }
}

QStringList Comp::compare()
{
    qDebug() << "comp started";
    QStringList list;
    QCryptographicHash hash1(QCryptographicHash::Sha1);
    QCryptographicHash hash2(QCryptographicHash::Sha1);

    qDebug() << "for start";
    for(auto i : fold1){
        hash1.addData(i->readAll());
        QByteArray sig1 = hash1.result();
        for(auto j : fold2){
            hash2.addData(j->readAll());
            QByteArray sig2 = hash2.result();
            if(sig1 == sig2){
                list.push_back(i->fileName() + '\t' + j->fileName());
            }
        }
    }
    qDebug() << "for finish";

    return list;


}

