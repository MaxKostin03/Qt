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
#include <QDateTime>
#include <QTimer>

#include "form.h"
#include "filemanager.h"
#include "searchclass.h"

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

signals:
    void chandgeSearch(QString arg1);
    void searchInDir(QString strPant);

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
    //--------8--------
    void setDateTime();

    void on_lineEdit_2_textEdited(const QString &arg1);
    void resultSearch(QStringList);
    void on_searchView_doubleClicked(const QModelIndex &index);

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
    //--------8--------
    QDateTime* dt;
    QStringListModel* searchModel;
    searchClass* sc;
    QThread* search;
};
#endif // MAINWINDOW_H
