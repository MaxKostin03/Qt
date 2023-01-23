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

void MainWindow::on_pushButton_pressed()
{
    ui->lineEdit->clear();
}

void MainWindow::on_lineEdit_textEdited(const QString &line)
{
    auto spec = Special.GetSpec(line.toUpper());
        if(spec.has_value())
        {
            ui->lineEdit->setText(Special.Special(line, spec.value()));
        }
}
