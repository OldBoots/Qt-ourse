#include "DBFun.h"

void create_table(QSqlDatabase data_base, int table_id, bool project_table_flag){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QString sql;
    if (project_table_flag){
        sql = "CREATE TABLE projects"
                + QString::number(table_id)
                + " ("
                  "pName         TEXT, "
                  "pImage        TEXT, "
                  "pDate         TEXT, "
                  "pTask         TEXT, "
                  "pBrigade      TEXT)";
    } else {
        sql = "CREATE TABLE tasks"
                + QString::number(table_id)
                + " ("
                  "tName         TEXT, "
                  "tData         TEXT, "
                  "tBrigade      TEXT, "
                  "tProgress     TEXT)";
    }
    QSqlQuery query(data_base);
    if(!query.exec(sql)){ cntrl = false;  error_log += "open ";}
    data_base.close();
    if(cntrl){ qDebug() << "Сreating a table\t\tOK"; }
    else { qDebug() << "Сreating a table\t\tNOT OK"; }
}

void record_data(QSqlDatabase data_base, int table_id, QVector <task_data_struct> task_data_vec){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open "; }
    QString sql = "INSERT INTO tasks" + QString::number(table_id) + " (tName, tData, tBrigade, tProgress) VALUES (:tName, :tData, :tBrigade, :tProgress)";
    QSqlQuery query(data_base);
    if (!query.prepare(sql)){ cntrl = false; error_log += "prepare ";}
    for(int i = 0; i < task_data_vec.size(); i++){
        qDebug() << task_data_vec[i].tName << task_data_vec[i].tData << task_data_vec[i].tBrigade << task_data_vec[i].tProgress;
        query.bindValue(":tName", task_data_vec[i].tName);
        query.bindValue(":tData", task_data_vec[i].tData);
        query.bindValue(":tBrigade", task_data_vec[i].tBrigade);
        query.bindValue(":tProgress", task_data_vec[i].tProgress);
        if (!query.exec()){ cntrl = false; error_log += "exec ";}
    }

    data_base.close();
    if(cntrl){ qDebug() << "Adding tasks\t\tOK"; }
    else { qDebug() << "Adding tasks\t\tNOT OK" << Qt::endl << error_log; }
}

void record_data(QSqlDatabase data_base, int table_id, QVector <project_data_struct> project_data_vec){
    QSqlQuery query(data_base);
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open "; }
    QString sql;
    sql = "INSERT INTO projects" + QString::number(table_id) + " ("
            + "pName         TEXT, "
              "pImage        TEXT, "
              "pDate         TEXT, "
              "pTask         TEXT, "
              "pBrigade      TEXT)"
              "VALUES (:pName, :pImage, :pData, :pTask, :pBrigade)";
    if(!query.prepare(sql)){ cntrl = false; error_log += "prepare ";};
    for(int i = 0; i < project_data_vec.size(); i++){
        query.bindValue(":pName", project_data_vec[i].pName);
        query.bindValue(":pImage", project_data_vec[i].pImage);
        query.bindValue(":pData", project_data_vec[i].pData);
        query.bindValue(":pTask", project_data_vec[i].pTask);
        query.bindValue(":pBrigade", project_data_vec[i].pBrigade);
    }
    if (!query.exec()){ cntrl = false; error_log += "exec ";}
    data_base.close();
    if(cntrl){ qDebug() << "Adding project\t\tOK"; }
    else { qDebug() << "Adding project\t\tNOT OK" << Qt::endl << error_log; }
}

void read_data(QSqlDatabase data_base, int table_id, QVector <task_data_struct> &task_data_vec){
    QSqlQuery query(data_base);
    task_data_struct form;
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QString sql = "SELECT tName, tData, tBrigade, tProgress FROM tasks" + QString::number(table_id);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec ";}
    while(query.next()){
        form.tName = query.value(0).toString();
        form.tData = query.value(1).toString();
        form.tBrigade = query.value(2).toString();
        form.tProgress = query.value(3).toString();
        task_data_vec.push_back(form);
    }
    data_base.close();
    if(cntrl){ qDebug() << "Reading tasks\t\tOK"; }
    else { qDebug() << "Reading tasks\t\tNOT OK" << Qt::endl << error_log; }
}
void read_data(QSqlDatabase data_base, int table_id, QVector <project_data_struct> &project_data_vec){
    QSqlQuery query(data_base);
    project_data_struct form;
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QString sql = "SELECT pName, pImage, pData, pTask, pBrigade FROM projects" + QString::number(table_id);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec ";}
    while(query.next()){
        form.pName = query.value(0).toString();
        form.pImage = query.value(1).toString();
        form.pData = query.value(2).toString();
        form.pTask = query.value(3).toString();
        form.pBrigade = query.value(4).toString();
        project_data_vec.push_back(form);
    }
    data_base.close();
    if(cntrl){ qDebug() << "Reading projects\t\tOK"; }
    else { qDebug() << "Reading projects\t\tNOT OK" << Qt::endl << error_log; }
}

void delete_data(QSqlDatabase data_base, int table_id, QString fild, bool project_table_flag){
    QSqlQuery query(data_base);
    project_data_struct form;
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QString sql;
    qDebug() << data_base.tables();
    if(project_table_flag){
        sql = "DELETE FROM projects" + QString::number(table_id) + " WHERE pBregade = \'" + fild + "\'";
    } else {
        sql = "DELETE FROM tasks" + QString::number(table_id) + " WHERE tName = \'" + fild + "\'";
    }
    if (!query.exec(sql)){ cntrl = false; error_log += "exec ";}
    data_base.close();
    if(cntrl){ qDebug() << "Deleting projects\t\tOK"; }
    else { qDebug() << "Deleting projects\t\tNOT OK" << Qt::endl << error_log; }
}
