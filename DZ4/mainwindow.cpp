#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpform.h"
#include "srv.h"

#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDataStream>
#include <QTranslator>
#include <QLibraryInfo>
#include <QEvent>
#include <QClipboard>
#include <QShortcut>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    openedFileName("")
{
    ui->setupUi(this);
    Init();
}

MainWindow::~MainWindow(){

    delete ui;
}

void MainWindow::Init(){

    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(true);

    QAction *exitAction = new QAction(tr("Exit"));
    exitAction->setShortcut(tr("CTRL+Q"));
    connect(exitAction, SIGNAL(triggered()),this, SLOT(close()));

}

void MainWindow::changeTranslator(QString postfix)
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    translator->load(QApplication::applicationName() + "_" + postfix);
    QApplication::installTranslator(translator);
}

void MainWindow::changeEvent(QEvent *event)
{
    setWindowTitle(tr("Editor"));

    if(event->type() == QEvent::LanguageChange){
        ui->menu->setTitle(tr("Editor"));
        ui->actionEnglish->setText(tr("English"));
        ui->new_pushButton->setText(tr("New"));
        ui->open_pushButton->setText(tr("Open"));
        ui->readOnly_pushButton_2->setText(tr("Read only"));
        ui->close_pushButton->setText(tr("Close"));
        ui->save_pushButton->setText(tr("Save"));
        ui->saveas_pushButton->setText(tr("Save as"));
        ui->pushButton->setText(tr("Exit"));
        ui->help_pushButton->setText(tr("Help"));
        ui->actionRussian->setText(tr("Russian"));

    }else
    {
        QMainWindow::changeEvent(event);
    }
}

void MainWindow::ExtendedFileSave(){

    if(!ui->textEdit->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton reply;
        QString type = openedFileName.isEmpty() ? " as" : "";
        reply = QMessageBox::question(this, "Save file" + type, "Do you want to save file" + type + "?", QMessageBox::Yes | QMessageBox::No);
        if (QMessageBox::Yes == reply)
        {
            if (!openedFileName.isEmpty())
            {
                FileSave();
            }
            else
            {
                FileSaveAs();
            }
        }
    }
}

void MainWindow::FileSave(){

    QString s = QFileDialog::getSaveFileName(this, "Save File", openedFileName, filter);
    if (s.length() > 0)
    {
        QString ext = QString(&(s.data()[s.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(s);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                file.close();
                openedFileName = s;
            }
        }
    }
}

void MainWindow::FileSaveAs(){

    QString s = QFileDialog::getSaveFileName(this, "Save File As", QDir::current().path(), filter);
    if (s.length() > 0)
    {
        QString ext = QString(&(s.data()[s.length() - 4]));
        if (ext == ".txt")
        {
            QFile file(s);
            if (file.open(QFile::WriteOnly))
            {
                QTextStream stream(&file);
                stream << ui->textEdit->toPlainText();
                file.close();
                openedFileName = s;
            }
        }
    }
}

void MainWindow::FileOpen(){

    QString s = QFileDialog::getOpenFileName(this, "Open File", QDir::current().path(), filter);
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::ReadOnly | QFile::ExistingOnly))
        {
            if (index != -1 && s.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                openedFileName = s;
                file.close();
            }
        }
    }
}

void MainWindow::on_new_pushButton_pressed(){

    ExtendedFileSave();
    ui->textEdit->setReadOnly(false);
    ui->textEdit->setDisabled(false);
    ui->textEdit->clear();
    openedFileName = "";
}

void MainWindow::on_close_pushButton_pressed(){

    ExtendedFileSave();
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setDisabled(true);
    ui->textEdit->clear();
    openedFileName = "";

}

void MainWindow::on_open_pushButton_pressed(){

    ExtendedFileSave();
    FileOpen();

    ui->textEdit->setReadOnly(false);
    ui->textEdit->setDisabled(false);
}

void MainWindow::on_save_pushButton_pressed(){

    FileSave();

}

void MainWindow::on_saveas_pushButton_pressed(){
    FileSaveAs();

}

void MainWindow::on_help_pushButton_pressed(){
    HelpForm* help = new HelpForm(this);
    if(help){

        help->show();
    }
}

void MainWindow::on_pushButton_clicked(){
    close();

}

void MainWindow::on_readOnly_pushButton_2_clicked(bool checked)
{
    QString s = QFileDialog::getOpenFileName(this, "Open File", QDir::current().path(), filter);
    QFile file(":/.txt");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Внимание!", "Режим только для чтения!");
    }
    if (s.length() > 0)
    {
        int index = s.indexOf(".txt");
        QFile file(s);
        if (file.open(QFile::ReadOnly))
        {
            if (index != -1 && s.length() - 4 == index)
            {
                QTextStream stream(&file);
                ui->textEdit->setText(stream.readAll());
                openedFileName = s;
                file.close();
            }
        }
    }
}

void MainWindow::on_actionEnglish_triggered()
{
    changeTranslator("en");
}

void MainWindow::on_actionRussian_triggered()
{
    changeTranslator("ru");
}
