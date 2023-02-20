#include "saveuser.h"
#include <QTextStream>
#include <QDebug>

saveUser::saveUser(QObject *parent)
    : QObject{parent}
{
    oldT = 0;
    newT = 0;
    this->loadSave();
    listData = dataLoad.split("\n");
    listData.removeAll(QString(""));
    oldT = listData.size();
    flagChange = false;
}
saveUser::~saveUser()
{
    if (flagChange)
        this->save();
    if (saveFile) saveFile->close();
}

void saveUser::loadSave()
{
    saveFile = new QFile("./save.txt", this);
    if (!saveFile) return;
    if (!saveFile->open(QIODevice::ReadWrite))
    {
        emit initEnd(false);
        return;
    }
    QTextStream stream(saveFile);
    dataLoad = stream.readAll();
    emit initEnd(true);
}

void saveUser::save()
{
    QTextStream stream(saveFile);
    stream << newData;
    saveFile->close();
}

void saveUser::setTask(QString Task)
{
    flagChange = true;
    newData += Task + "\n";
    dataLoad += Task + "\n";
    listData= dataLoad.split("\n");
    listData.removeAll(QString(""));
    newT += 1;
    emit modelChanged();
}
