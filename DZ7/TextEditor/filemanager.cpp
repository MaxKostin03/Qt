#include "filemanager.h"
#include <QDir>

fileManager::fileManager(QWidget *parent)
    : QWidget{parent}, model(nullptr)
{
    setMinimumWidth(100);
    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries);
    model->setRootPath("");
    listView = new QListView(this);
    listView->setModel(model);
    connect(listView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(DoubleClicked(QModelIndex)));
}

void fileManager::DoubleClicked(const QModelIndex &index)
{
    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.fileName() == "..")
    {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
        emit path(fileInfo);
    }
    else if (fileInfo.fileName() == ".")
    {
        listView->setRootIndex(model->index(""));
        emit path(fileInfo);
    }
    else if (fileInfo.isDir())
    {
        listView->setRootIndex(index);
        emit path(fileInfo);
    }
}
