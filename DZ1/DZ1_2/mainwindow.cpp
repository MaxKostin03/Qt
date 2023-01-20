#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit_4->setReadOnly(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_commandLinkButton_clicked()
{
    double a = ui->lineEdit_1->text().toInt();
    double b = ui->lineEdit_2->text().toInt();
    double c;
    double corner = ui->lineEdit_3->text().toInt();

    if(a != 0 && b != 0 && corner != 0) {
        c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos((corner /180) * M_PI));
        if(ui->radioButton_1->isChecked()) {
            c = qSqrt(qPow(a, 2) + qPow(b, 2) - 2 * a * b * qCos(corner));
        }
        ui->lineEdit_4->setText(QString("%1").arg(c));
    }else {
        ui->lineEdit_4->setText(QString("incorrect input!"));
    }
}

