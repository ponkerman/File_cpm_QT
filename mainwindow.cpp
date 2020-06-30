#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cmp = new Comp();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectFloder1_clicked()
{
    QDir dir(QFileDialog::getExistingDirectory(this, "choose directory"));
    if(dir.isEmpty(QDir::Files)) {
        QMessageBox msg;
        msg.setWindowTitle("ошибка");
        msg.setText("в папке #1 нет файлов");
        msg.exec();
        return;
    }
    ui->fold1Label->setText(dir.path());
    cmp->setFold1(dir);
    if(cmp->isReady())
        ui->compButton->setDisabled(0);
}

void MainWindow::on_selectFloder2_clicked()
{
    QDir dir(QFileDialog::getExistingDirectory(this, "choose directory"));
    if(dir.isEmpty(QDir::Files)) {
        QMessageBox msg;
        msg.setWindowTitle("ошибка");
        msg.setText("в папке #2 нет файлов");
        msg.exec();
        return;
    }
    ui->fold2Label->setText(dir.path());
    cmp->setFold2(dir);
    if(cmp->isReady())
        ui->compButton->setDisabled(0);
}

void MainWindow::on_compButton_clicked()
{
    ui->filesList->clear();
    QStringList list = cmp->compare();

    for(auto it : list)
        ui->filesList->addItem(it);
    ui->compButton->setDisabled(1);
}




