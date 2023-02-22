#ifndef SAVEUSER_H
#define SAVEUSER_H

#include <QApplication>
#include <QObject>
#include <QApplication>
#include "tabledb.h"

class saveUser : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int oldT MEMBER oldT)
public:
    explicit saveUser(QObject *parent = nullptr);
    virtual ~saveUser();
    Q_INVOKABLE void addTasc(QString, QString, QString);
    Q_INVOKABLE int getTascsCount();
    Q_INVOKABLE void viewTascs();
    Q_INVOKABLE int getNewTascs();

private:
    QWidget *widget;
    bool flagChange;
    int oldT;
    int newT;
    tabledb tdb;
};

#endif // SAVEUSER_H
