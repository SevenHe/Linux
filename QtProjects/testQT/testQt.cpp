#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setText("Have been Pushed!");
}

MainWindow::~MainWindow()
{
    delete ui;
}
