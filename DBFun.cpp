#include "DBFun.h"

void create_table(QSqlDatabase data_base, int id, bool table){
    QSqlQuery query;
    //QSqlDatabase pdb = QSqlDatabase::addDatabase("QSQLITE", "pdb.sqlite");
    if (!data_base.open()){
        qDebug() << data_base.lastError();
    }
    QString sql;
    if (table){
        sql = "CREATE TABLE project_"
                + QString::number(id)
                + "pName TEXT NOT NULL"
                  "pImage TEXT NOT NULL"
                  "pDate TEXT NOT NULL"
                  "pTask TEXT NOT NULL"
                  "pBrigade TEXT NOT NULL";
    } else {
        sql = "CREATE TABLE tasks_"
                + QString::number(id)
                + "tName TEXT NOT NULL"
                  "tDate TEXT NOT NULL"
                  "tBrigade TEXT NOT NULL"
                  "tProgress TEXT NOT NULL"
                  ;
    }
    if(!query.exec(sql)){
        qDebug() << data_base.lastError();
    }
    data_base.close();
}
