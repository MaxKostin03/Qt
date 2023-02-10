#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMdiSubWindow>
#include <QTextEdit>
#include <QFont>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_2, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->save, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->help, SIGNAL(triggered()), this, SLOT(help()));
    connect(ui->readOnly,SIGNAL(triggered()), this, SLOT(openOnlyRead()));
    connect(ui->english, SIGNAL(triggered()), this, SLOT(changeLanguageUS()));
    connect(ui->russian, SIGNAL(triggered()), this, SLOT(changeLanguageRU()));

    connect(ui->dark, SIGNAL(triggered()), this, SLOT(on_dark_clicked()));
    connect(ui->light, SIGNAL(triggered()), this, SLOT(on_light_clicked()));
    ui->russian->setEnabled(false);
    ui->light->setEnabled(false);
    connect(ui->widget, SIGNAL(path(QFileInfo)), this, SLOT(changePath(QFileInfo)));
    ui->mdiArea->addSubWindow(new QTextEdit(this));
    //ui->mdiArea->addSubWindow(new QTextEdit(this));
    connect(ui->printDoc, SIGNAL(triggered()), this, SLOT(printD()));

    tcf = new QTextCharFormat;
    connect(ui->copyFT, SIGNAL(triggered()), this, SLOT(copyFText()));
    connect(ui->setFT, SIGNAL(triggered()), this, SLOT(setFText()));
    ui->setFT->setEnabled(false);
    connect(ui->onLeft, SIGNAL(triggered()), this, SLOT(setTextLeft()));
    connect(ui->onCenter, SIGNAL(triggered()), this, SLOT(setTextCenter()));
    connect(ui->onRight, SIGNAL(triggered()), this, SLOT(setTextRight()));
    connect(ui->font, SIGNAL(triggered()), this, SLOT(setFont()));

    //--------8-------
    connect(ui->dateTimeAction, SIGNAL(triggered()), this, SLOT(setDateTime()));
    dt = new QDateTime();

    sc = new searchClass();
    connect(this, SIGNAL(chandgeSearch(QString)), sc, SLOT(searchFile(QString)));
    searchModel = new QStringListModel;
    connect(sc, SIGNAL(searchFinished(QStringList)), this, SLOT(resultSearch(QStringList)));
    ui->searchView->setVisible(false);
    connect(this, SIGNAL(searchInDir(QString)), ui->widget, SLOT(setResultSearch(QString)));
    connect(ui->widget, SIGNAL(toSearch(QModelIndex)), sc, SLOT(changePath(QModelIndex)));
    search = new QThread();
    sc->moveToThread(search);
    search->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);   
    }
    QMainWindow::changeEvent(event);
}

void MainWindow::open() {
    ui->textEdit->setReadOnly(false);
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Открыть файл"), "",
    tr("Текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно открыть файл"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        ui->lineEdit->setText(fileName);
        file.close();
    }
}

void MainWindow::openOnlyRead()
{
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Открыть файл"), "",
    tr("Текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Ошибка"), tr("Невозможно открыть файл"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        ui->textEdit->setReadOnly(true);
        ui->lineEdit->setText(fileName);
        file.close();
    }
}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
    tr("Сохранить файл"), "",
    tr("Текстовые файлы (*.txt);;Файлы C++ (*.cpp *.h)"));
    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox msgBox; msgBox.setText("Невозможно записать файл"); msgBox.exec();
        }
        else
        {
            QTextStream stream(&file);
            stream << ui->textEdit->toPlainText();
            stream.flush();
            ui->lineEdit->setText(fileName);
            file.close();
        }
    }
}

void MainWindow::help()
{
    Form* f = new Form;
    f->show();
}

void MainWindow::changeLanguageUS()
{
    ui->russian->setEnabled(true);
    if (translator.load(":/QtLanguage_en_US.qm"))
    {
        qApp->installTranslator(&translator);
    }
    ui->english->setEnabled(false);
}

void MainWindow::changeLanguageRU()
{
    ui->english->setEnabled(true);
    qApp->removeTranslator(&translator);
    ui->russian->setEnabled(false);
}


void MainWindow::on_dark_clicked()
{
    ui->light->setEnabled(true);
    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    qApp->setPalette(darkPalette);
    ui->dark->setEnabled(false);
}

void MainWindow::on_light_clicked()
{
    ui->light->setEnabled(false);
    qApp->setPalette(style()->standardPalette());
    ui->dark->setEnabled(true);
}

void MainWindow::changePath(QFileInfo fileInfo)
{
    ui->lineEdit->setText(fileInfo.absoluteFilePath());
}

void MainWindow::printD()
{
    QPrinter printer;
    QPrintDialog dlg(&printer, this);
    if (dlg.exec() != QDialog::Accepted) return;
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->print(&printer);
}

void MainWindow::copyFText()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    *tcf = edit->textCursor().charFormat();
    ui->setFT->setEnabled(true);
}

void MainWindow::setFText()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->textCursor().setCharFormat(*tcf);
}

void MainWindow::setTextLeft()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->setAlignment(Qt::AlignLeft);
}

void MainWindow::setTextCenter()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->setAlignment(Qt::AlignCenter);
}

void MainWindow::setTextRight()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->setAlignment(Qt::AlignRight);
}

void MainWindow::setFont()
{
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    QFont font = edit->textCursor().charFormat().font();
    QFontDialog fntDlg(font, this);
    bool ok = true;
    font = fntDlg.getFont(&ok, this);
    if (ok)
    {
        QTextCharFormat fmt;
        fmt.setFont(font);
        edit->textCursor().setCharFormat(fmt);
    }
}

//-------8---------
void MainWindow::setDateTime()
{
    *dt = QDateTime::currentDateTime();
    QMdiSubWindow* subWindow = ui->mdiArea->activeSubWindow();
    QWidget* widg = subWindow->widget();
    QTextEdit* edit = (QTextEdit*)widg;
    edit->textCursor().insertText(dt->toString("hh:mm:ss dd.MM.yyyy"));
}

void MainWindow::on_lineEdit_2_textEdited(const QString &arg1)
{
    if (ui->lineEdit_2->text() != "")
    {

        emit chandgeSearch(arg1);
    }
    else
        ui->searchView->setVisible(false);
}

void MainWindow::resultSearch(QStringList searchList)
{
    ui->searchView->setVisible(true);
    searchModel->setStringList(searchList);
    ui->searchView->setModel(searchModel);
}


void MainWindow::on_searchView_doubleClicked(const QModelIndex &index)
{
    qDebug() << index;
    QVariant var = index.data(Qt::DisplayRole);
    qDebug() << var.toString();
    QString path = var.toString();
    path = path.sliced(0, path.lastIndexOf("/") + 1);
    qDebug() << path;
    emit searchInDir(path);
}

