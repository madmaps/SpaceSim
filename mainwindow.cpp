#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),updateThread(new BackgroundThread)
{
    ui->setupUi(this);
    //connect(updateThread,SIGNAL(sendUpdate()),ui->canvas,SLOT(updateData()));
    connect(updateThread,SIGNAL(updateData()),ui->canvas,SLOT(updateData()));
    connect(ui->canvas,SIGNAL(doneUpdating()),updateThread,SLOT(setUpdate()));
    updateThread->start();
}

MainWindow::~MainWindow()
{
    updateThread->stop();
    delete updateThread;
    updateThread=0;
    delete ui;
}
