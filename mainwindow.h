#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

#include "comp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_selectFloder1_clicked();

    void on_selectFloder2_clicked();

    void on_compButton_clicked();

private:
    Ui::MainWindow *ui;
    Comp cmp;
};
#endif // MAINWINDOW_H
