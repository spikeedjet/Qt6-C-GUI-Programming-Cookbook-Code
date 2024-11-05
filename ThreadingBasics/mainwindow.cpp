#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <qthread.h>

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

void MainWindow::mySlot()
{
    qDebug() << "Done!" << QThread::currentThreadId();
}
