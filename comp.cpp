#include "comp.h"

Comp::Comp()
{

}

Comp::~Comp()
{

}

bool Comp::isReady()
{
    if(fold1.empty() || fold2.empty()) return false;
    return true;
}

void Comp::setFold1(const QDir &dir)
{
    fold1.clear();
    setFold(dir, fold1);
}

void Comp::setFold2(const QDir &dir)
{
    fold2.clear();
    setFold(dir, fold2);
}

void Comp::setFold(const QDir &dir, std::vector<QFile*> &fold)
{
    QString path = dir.path();
    QStringList list = dir.entryList(QDir::AllEntries|QDir::NoDotAndDotDot);
    for(auto it : list)
        fold.push_back(new QFile(path + '/' + it));
}

QStringList Comp::compare()
{
    QStringList list;
    //auto start = std::chrono::steady_clock::now(); //для замера времени

    //////////////////////////////////////////////////////////////////////////////
    /// comparing
    //////////////////////////////////////////////////////////////////////////////
        QByteArray buf1;
        QByteArray buf2;
        qint64 file1_size, file2_size;
        int iter;

        for(QFile* file1 : fold1){
            file1_size = file1->size();
            if(!file1->isOpen()) {
                file1->open(QIODevice::ReadOnly);
            }
            for(QFile* file2 : fold2){
                if(file2_size = file2->size(), file1_size == file2_size){
                    if(!file2->isOpen()) {
                        file2->open(QIODevice::ReadOnly);
                    }
                    for(iter = 0; iter < (file2_size/4096)+1; iter++){
                        buf1 = file1->read(4096);
                        buf2 = file2->read(4096);
                        if(buf1 != buf2) goto mark;
                    }
                    list.push_back(file1->fileName() + '\t' + file2->fileName());
                    mark:
                    file2->seek(0);
                    file1->seek(0);
                }
            }
        }
    /////////////////////////////////////////////////////////////////////////////
    /* вторая часть таймера
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    qDebug() << "time elapsed: "<< elapsed.count();
    */
    return list;

}


