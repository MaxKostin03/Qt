#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->label->setText("Version 1.0.0");

}

Form::~Form()
{
    delete ui;
}
