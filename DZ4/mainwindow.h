#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTranslator>
#include <QEvent>
#include <QShortcut>

#include "helpform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_new_pushButton_pressed();
    void on_close_pushButton_pressed();
    void on_open_pushButton_pressed();
    void on_save_pushButton_pressed();
    void on_saveas_pushButton_pressed();
    void on_help_pushButton_pressed();
    void on_pushButton_clicked();
    void on_readOnly_pushButton_2_clicked(bool checked);
    void on_actionEnglish_triggered();
    void on_actionRussian_triggered();

private:

    void FileSave();
    void FileSaveAs();
    void FileOpen();
    void FileNew();
    void ReadOnlyFile();

    void Init();
    void ExtendedFileSave();

    void changeTranslator(QString postfix);
    void changeEvent(QEvent *event);

private:
    Ui::MainWindow *ui;
    QString openedFileName;
    QString filter;
    QTranslator* translator;
    QMenu* fileMenu;
    QMenu* shortcutSubMenu;
    QAction* newAction;
    QAction* openAction;
    QAction* readOnlyAction;
    QAction* saveAction;
    QAction* saveAsAction;
    QAction* closeAction;
    QAction* exitAction;

};
#endif // MAINWINDOW_H
