#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectFloder1_clicked()
{
    //TODO: remove defauld dir
    QDir dir(QFileDialog::getExistingDirectory(this, "choose directory", "F:/Projects/Open_media_TZ/test"));
    ui->fold1Label->setText(dir.path());
    cmp.setFold1(dir);
}

void MainWindow::on_selectFloder2_clicked()
{
    //TODO: remove defauld dir
    QDir dir(QFileDialog::getExistingDirectory(this, "choose directory", "F:/Projects/Open_media_TZ/test"));
    ui->fold2Label->setText(dir.path());
    cmp.setFold2(dir);
}

void MainWindow::on_compButton_clicked()
{
    qDebug() << "but pressed";
    QStringList list = cmp.compare();
    qDebug() << "comp finished";
    list.push_back("end.");
    for(auto it : list)
        ui->filesList->addItem(it);
}
