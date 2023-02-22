#ifndef TABLEDB_H
#define TABLEDB_H

#include <QObject>
#include <QWidget>
#include <QSqlQuery>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>

class tabledb : public QWidget
{
    Q_OBJECT
public:
    explicit tabledb(QWidget *parent = nullptr);
    ~tabledb();
    bool ConnectDB();
    bool CreateTable();
    bool AddRow(QString name,QString date,QString progress);
    void ViewTascs();
    int GetCount();

signals:

private:
    QSqlDatabase db;
    QString currentTableName;
    QSqlQueryModel *model;
    QTableView *view;

};

#endif // TABLEDB_H
