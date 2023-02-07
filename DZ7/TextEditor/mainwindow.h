#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QKeyEvent>
#include <QEvent>
#include <QSharedPointer>
#include <QMdiArea>
#include <QPrinter>
#include <QPrintDialog>

#include "form.h"
#include "filemanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    virtual void changeEvent(QEvent* event) override;

private slots:
    void open();
    void openOnlyRead();
    void save();
    void help();
    void changeLanguageUS();
    void changeLanguageRU();
    void on_dark_clicked();
    void on_light_clicked();
    void changePath(QFileInfo fileInfo);
    void printD();

    void copyFText();
    void setFText();
    void setTextLeft();
    void setTextCenter();
    void setTextRight();
    void setFont();

private:
    Ui::MainWindow *ui;
    QTranslator translator;
    fileManager* f;
    QShortcut* openKey;
    QShortcut* saveKey;
    QShortcut* helpKey;
    QShortcut* quitKey;
    QMdiArea* area;
    QTextCharFormat* tcf;
};
#endif // MAINWINDOW_H
