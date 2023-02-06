#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QTreeView>
#include <QComboBox>
#include <QPushButton>
#include <QStandardItemModel>
#include <QApplication>

#include <QFileSystemModel>
#include <QListView>

class fileManager : public QWidget
{
    Q_OBJECT
public:
    explicit fileManager(QWidget *parent = nullptr);

private slots:
    void DoubleClicked(const QModelIndex &index);

signals:
    void path(QFileInfo);

private:
    QFileSystemModel *model;
    QListView* listView;
};

#endif // FILEMANAGER_H
