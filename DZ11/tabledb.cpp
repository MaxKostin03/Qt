#include "tabledb.h"

tabledb::tabledb(QWidget *parent)
    : QWidget{parent}
{
    this->ConnectDB();
    currentTableName = "mytascs";
    if(this->GetCount() == 0)
    {
        this->CreateTable();
    }
    model = new QSqlQueryModel(this);
    view = new QTableView(this);
}

tabledb::~tabledb()
{
    delete model;
    delete view;
}

bool tabledb::ConnectDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./tascs.db");
    if(!db.open())
    {
        qDebug() << "Can not open database";
        return false;
    }
    return true;
}

bool tabledb::CreateTable()
{
    QSqlQuery query;
    QString command =   "CREATE TABLE mytascs ("
                        "id INTEGER PRIMARY KEY NOT NULL,"
                        "name VARCHAR(20),"
                        "date VARCHAR(10),"
                        "progress VARCHAR(2) );";
    if(!query.exec(command))
    {
        qDebug() << "Unable to create a table";
        return false;
    }
    //currentTableName = "mytascs";
    return true;
}

bool tabledb::AddRow(QString name, QString date, QString progress)
{
    QSqlQuery query;
    QString str =   "INSERT INTO mytascs (name, date, progress)"
                        "VALUES('%1', '%2', '%3');";
    QString command = str.arg(name).arg(date).arg(progress);
    if(!query.exec(command))
    {
        qDebug() << "Unable to make insert operation";
        return false;
    }
    return true;
}

void tabledb::ViewTascs()
{
    model->setQuery("SELECT * FROM mytascs;");
    view->setMinimumWidth(450);
    view->setMinimumHeight(300);
    view->setModel(model);
    this->show();
}

int tabledb::GetCount()
{
    QSqlQuery query;
    QString command = "SELECT COUNT (*) FROM mytascs;";
    query.exec(command);
    query.first();
    return query.value(0).toInt();;

}





