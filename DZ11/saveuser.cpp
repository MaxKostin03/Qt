#include "saveuser.h"

saveUser::saveUser(QObject *parent)
    : QObject{parent}
{
    oldT = 0;
    newT = 0;
}

saveUser::~saveUser()
{
    delete widget;
}

void saveUser::addTasc(QString name, QString date, QString progress)
{
    tdb.AddRow(name, date, progress);
    newT += 1;
}

int saveUser::getTascsCount()
{
    return tdb.GetCount();
}

void saveUser::viewTascs()
{
    tdb.ViewTascs();
}

int saveUser::getNewTascs()
{
    return newT;
}

