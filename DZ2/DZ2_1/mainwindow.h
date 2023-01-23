#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <optional>

#include "special_symbols.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();

    void on_lineEdit_textEdited(const QString &line);

private:
    Ui::MainWindow *ui;
    SpecialSymbols Special;
};
#endif // MAINWINDOW_H
