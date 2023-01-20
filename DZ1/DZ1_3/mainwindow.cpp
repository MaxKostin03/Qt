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

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->plainTextEdit->toPlainText();
    ui->plainTextEdit_2->insertPlainText(text);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->plainTextEdit->clear();
    QString text = ui->plainTextEdit_2->toPlainText();
    ui->plainTextEdit->insertPlainText(text);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->plainTextEdit->appendHtml("<font color='red'>Hello</font>");
}

