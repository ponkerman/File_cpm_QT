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
    for(auto it : fold1)
        delete it;
    fold1.clear();

    setFold(dir, fold1);
}

void Comp::setFold2(const QDir &dir)
{
    for(auto it : fold2)
        delete it;
    fold2.clear();

    setFold(dir, fold2);
}

void Comp::setFold(const QDir &dir, std::vector<QFile*> &fold)
{
    QString path = dir.path();
    QStringList list = dir.entryList(QDir::AllEntries|
                                     QDir::NoDotAndDotDot,
                                     QDir::SortFlag::Size);
    for(auto it : list)
        fold.push_back(new QFile(path + '/' + it));
}

void Comp::compare()
{
    //auto start = std::chrono::steady_clock::now(); //для замера времени
    //////////////////////////////////////////////////////////////////////////////
    /// comparing
    //////////////////////////////////////////////////////////////////////////////
        QByteArray buf1;
        QByteArray buf2;
        bool flag;
        qint64 file1_size, file2_size;
        std::vector<QFile*>::iterator it;

        for(std::vector<QFile*>::iterator file1 = fold1.begin(); file1 != fold1.end(); file1++){
            file1_size = (*file1)->size();
            if(!(*file1)->isOpen()) {
                (*file1)->open(QIODevice::ReadOnly);
            }
            flag = false;
            it = fold2.begin();
            for(std::vector<QFile*>::iterator file2 = it; file2 != fold2.end(); file2++){
                if(file2_size = (*file2)->size(), file1_size == file2_size){
                    if(!(*file2)->isOpen()) {
                        (*file2)->open(QIODevice::ReadOnly);
                    }
                    for(int i = 0; i < (file2_size/4096)+1; i++){
                        buf1 = (*file1)->read(4096);
                        buf2 = (*file2)->read(4096);
                        if(buf1 != buf2) goto mark;
                    }
                    emit send(QString((*file1)->fileName() + '\t' + (*file2)->fileName()));
                    mark:
                    (*file2)->seek(0);
                    (*file1)->seek(0);
                    flag = true;
                } else if (flag) {
                    if((file1 != fold1.begin()) && ((*file1)->size() != (*prev(file1))->size()))
                        it = file2;
                    break;
                }
            }
        }
    /////////////////////////////////////////////////////////////////////////////
    /* вторая часть таймера
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    qDebug() << "time elapsed: "<< elapsed.count();
    */
}


