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
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->label_7->clear();
        double D, x1, x2;
        double a = ui->lineEdit_1->text().toInt();
        double b = ui->lineEdit_2->text().toInt();
        double c = ui->lineEdit_3->text().toInt();

        if(a == 0)
        {
            x1 = -c/b;
            ui->lineEdit_4->setText(QString("%1").arg(x1));
        }
        else
            {
                D = qPow(b, 2) - 4 * a * c;
                if(D < 0)
                          {
                            ui->label_7->setText(QString("root can't be calculated!"));
                            return;
                          }
        x1 = (-b - qSqrt(D)) / 2 * a;
        if(D == 0) ui ->lineEdit_4->setText(QString("%1").arg(x1));
        else{
                x2 = (-b + qSqrt(D)) / 2 * a;
                ui->lineEdit_4->setText(QString("%1").arg(x1));
                ui->lineEdit_5->setText(QString("%1").arg(x2));
            }
        }
}

