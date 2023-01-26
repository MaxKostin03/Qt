#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName();
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly)) return;
    QTextStream stream(&file);
    QString str = stream.readAll();
    ui->plainTextEdit->setPlainText(str);
}

void MainWindow::on_WeatherButton_clicked()
{
    QString str = ui->plainTextEdit->toPlainText();
    QRegExp regTemp("(temp\":\")([+-][0-9]{1,2})");     //Выражение для поиска температуры
    regTemp.indexIn(str);
    QRegExp regDescr("(description\":\")(.+)(\",\"descriptionShort)");  //Выражение для поиска описания погоды
    regDescr.indexIn(str);
    qDebug() << regTemp.cap(2);

    qDebug() << regDescr.cap(2);

    ui->plainTextEdit_2->appendPlainText(QString("Температура воздуха %1, \n%2\n").arg(regTemp.cap(2), regDescr.cap(2)));
}

void MainWindow::on_RateButton_clicked()
{
    QString str = ui->plainTextEdit->toPlainText();
    QRegExp regD("(type\":\"USD\",\"rate\":)([0-9]{2}[.][0-9]{2})");
    regD.indexIn(str);
    QRegExp regE("(EUR\",\"rate\":)([0-9]{2}[.][0-9]{2})");
    regE.indexIn(str);
    ui->plainTextEdit_2->appendPlainText(QString("Курс доллара: %1\nКурс евро: %2\n").arg(regD.cap(2), regE.cap(2)));
}

void MainWindow::on_pushButton_2_clicked()
{
    close();
}

