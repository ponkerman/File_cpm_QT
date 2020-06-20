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
       fold1.back()->open(QIODevice::ReadOnly);
   }
}

void Comp::setFold2(QDir fold)
{
    fold.setSorting(QDir::Name);
    QString path = fold.path();

    QStringList list = fold.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);

    for(auto it : list){
        fold2.push_back(new QFile(path + '/' + it));
        fold2.back()->open(QIODevice::ReadOnly);
    }
}

QStringList Comp::compare()
{
    auto start = std::chrono::steady_clock::now();
    qDebug() << "comp started";
    QStringList list;

    qDebug() << "for start";
    QByteArray buf1;
    QByteArray buf2;

    for(auto i : fold1){
        buf1 = i->readAll();
        i->seek(0);
        qDebug() << i->fileName();
        for(auto j : fold2){
            buf2 = j->readAll();
            j->seek(0);
            if(buf1 == buf2){
                list.push_back(i->fileName() + '\t' + j->fileName() + '\t' + buf1 + '\t' + buf2);
            }
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    qDebug() << elapsed.count();
    qDebug() << "for finish";

    return list;


}

