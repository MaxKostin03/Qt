#include "helpform.h"
#include "ui_helpform.h"

#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QTextStream>

HelpForm::HelpForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HelpForm)
{
    ui->setupUi(this);
    Init();
}

HelpForm::~HelpForm(){
    delete ui;
}

void HelpForm::Init(){
    this->setWindowFlags(Qt::Dialog);

    QFile file(":/txt/help.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Ошибка!", "Файл не открывается");
    }

    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setPlainText(text);

    file.close();

}

void HelpForm::on_pushButton_clicked(){
    close();
}
