#include "DBFun.h"

void create_project_tables(QSqlDatabase data_base, int id_table){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QString sql;
    QSqlQuery query(data_base);
    sql = "CREATE TABLE projects"
            + QString::number(id_table)
            + " ("
              "ID           INTEGER PRIMARY KEY AUTOINCREMENT, "
              "pName         TEXT, "
              "pImage        TEXT, "
              "pDate         TEXT, "
              "pTask         TEXT, "
              "pBrigade      TEXT)";
    if(!query.exec(sql)){ cntrl = false;  error_log += "exec_p ";}
    sql = "CREATE TABLE tasks"
            + QString::number(id_table)
            + " ("
              "ID           INTEGER PRIMARY KEY AUTOINCREMENT, "
              "tName         TEXT, "
              "tData         TEXT, "
              "tBrigade      TEXT, "
              "tProgress     TEXT)";
    if(!query.exec(sql)){ cntrl = false;  error_log += "exec_t ";}
    data_base.close();
    if(cntrl){ qDebug() << "Сreating a table\t\tOK"; }
    else { qDebug() << "Сreating a table\t\tNOT OK"; }
}

// RECORD DATA //

void record_task_data(QSqlDatabase data_base, int id_table, QVector <task_data_struct> task_data_vec){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open "; }
    QSqlQuery query(data_base);
    QString sql = "INSERT INTO tasks" + QString::number(id_table) + " (tName, tData, tBrigade, tProgress) VALUES (:tName, :tData, :tBrigade, :tProgress)";
    if (!query.prepare(sql)){ cntrl = false; error_log += "prepare ";}
    for(int i = 0; i < task_data_vec.size(); i++){
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

void record_project_data(QSqlDatabase data_base, int id_table, QVector <project_data_struct> project_data_vec){
    QSqlQuery query(data_base);
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open "; }
    QString sql;
    sql = "INSERT INTO projects" + QString::number(id_table) + " ("
                                                               "pName, "
                                                               "pImage, "
                                                               "pDate, "
                                                               "pTask, "
                                                               "pBrigade) "
                                                               "VALUES (:pName, :pImage, :pData, :pTask, :pBrigade)";
    if(!query.prepare(sql)){ cntrl = false; error_log += "prepare ";};
    for(int i = 0; i < project_data_vec.size(); i++){
        query.bindValue(":pName", project_data_vec[i].pName);
        query.bindValue(":pImage", project_data_vec[i].pImage);
        query.bindValue(":pData", project_data_vec[i].pData);
        query.bindValue(":pTask", project_data_vec[i].pTask);
        query.bindValue(":pBrigade", project_data_vec[i].pBrigade);
        if (!query.exec()){ cntrl = false; error_log += "exec ";}
    }
    data_base.close();
    if(cntrl){ qDebug() << "Adding project\t\tOK"; }
    else { qDebug() << "Adding project\t\tNOT OK" << Qt::endl << error_log; }
}

void add_task_record(QSqlDatabase data_base, int id_table, task_data_struct task_data_vec){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open "; }
    QSqlQuery query(data_base);
    QString sql = "INSERT INTO tasks" + QString::number(id_table) + " (tName, tData, tBrigade, tProgress) VALUES (:tName, :tData, :tBrigade, :tProgress)";
    if (!query.prepare(sql)){ cntrl = false; error_log += "prepare ";}
    query.bindValue(":tName", task_data_vec.tName);
    query.bindValue(":tData", task_data_vec.tData);
    query.bindValue(":tBrigade", task_data_vec.tBrigade);
    query.bindValue(":tProgress", task_data_vec.tProgress);
    if (!query.exec()){ cntrl = false; error_log += "exec ";}
    data_base.close();
    if(cntrl){ qDebug() << "Adding tasks\t\tOK"; }
    else { qDebug() << "Adding tasks\t\tNOT OK" << Qt::endl << error_log; }
}

void add_project_record(QSqlDatabase data_base, int id_table, project_data_struct project_data_vec){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open "; }
    QSqlQuery query(data_base);
    QString sql;
    sql = "INSERT INTO projects" + QString::number(id_table) + " ("
                                                               "pName, "
                                                               "pImage, "
                                                               "pDate, "
                                                               "pTask, "
                                                               "pBrigade) "
                                                               "VALUES (:pName, :pImage, :pData, :pTask, :pBrigade)";
    if(!query.prepare(sql)){ cntrl = false; error_log += "prepare "; }
    query.bindValue(":pName", project_data_vec.pName);
    query.bindValue(":pImage", project_data_vec.pImage);
    query.bindValue(":pData", project_data_vec.pData);
    query.bindValue(":pTask", project_data_vec.pTask);
    query.bindValue(":pBrigade", project_data_vec.pBrigade);
    if (!query.exec()){ cntrl = false; error_log += "exec ";}
    data_base.close();
    if(cntrl){ qDebug() << "Adding project\t\tOK"; }
    else { qDebug() << "Adding project\t\tNOT OK" << Qt::endl << error_log; }
}

// READ DATA //

void read_task_table(QSqlDatabase data_base, int id_table, QVector <task_data_struct> &task_data_vec){
    if(!task_data_vec.isEmpty()){ task_data_vec.clear(); }
    task_data_struct form;
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QSqlQuery query(data_base);
    QString sql = "SELECT ID, tName, tData, tBrigade, tProgress FROM tasks" + QString::number(id_table);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec ";}
    while(query.next()){
        form.tID = query.value(0).toInt();
        form.tName = query.value(1).toString();
        form.tData = query.value(2).toString();
        form.tBrigade = query.value(3).toString();
        form.tProgress = query.value(4).toString();
        task_data_vec.push_back(form);
    }
    data_base.close();
    if(cntrl){ qDebug() << "Reading tasks\t\tOK"; }
    else { qDebug() << "Reading tasks\t\tNOT OK" << Qt::endl << error_log; }
}
void read_project_table(QSqlDatabase data_base, int id_table, QVector <project_data_struct> &project_data_vec){
    if(!project_data_vec.isEmpty()){ project_data_vec.clear(); }
    project_data_struct form;
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QSqlQuery query(data_base);
    QString sql = "SELECT ID, pName, pImage, pDate, pTask, pBrigade FROM projects" + QString::number(id_table);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec ";}
    while(query.next()){
        form.pID = query.value(0).toInt();
        form.pName = query.value(1).toString();
        form.pImage = query.value(2).toString();
        form.pData = query.value(3).toString();
        form.pTask = query.value(4).toString();
        form.pBrigade = query.value(5).toString();
        project_data_vec.push_back(form);
    }
    data_base.close();
    if(cntrl){ qDebug() << "Reading projects\t\tOK"; }
    else { qDebug() << "Reading projects\t\tNOT OK" << Qt::endl << error_log; }
}


// DELETE DATA //

void delete_row(QSqlDatabase data_base, QString name_table, int id_row){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QSqlQuery query(data_base);
    QString sql = "DELETE FROM " + name_table + " WHERE ID = " + QString::number(id_row);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec ";}
    data_base.close();
    if(cntrl){ qDebug() << "Deleting row\t\tOK"; }
    else { qDebug() << "Deleting row\t\tNOT OK" << Qt::endl << error_log; }
}

void delete_project(QSqlDatabase data_base, int id_table){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QSqlQuery query(data_base);
    QString sql = "DROP TABLE tasks" + QString::number(id_table);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec_t ";}
    sql = "DROP TABLE projects" + QString::number(id_table);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec_p ";}
    data_base.close();
    if(cntrl){ qDebug() << "Deleting table\t\tOK"; }
    else { qDebug() << "Deleting table\t\tNOT OK" << Qt::endl << error_log; }
}

                    // UP DATE //

void change_value(QSqlDatabase data_base, QString name_table, QString name_fild, QString value,  int id_row){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    QSqlQuery query(data_base);
    QString sql = "UPDATE " + name_table +" SET " + name_fild + " = \'" + value + "\' WHERE id = " + QString::number(id_row);
//    QString sql = "UPDATE tasks0 SET tName = '70000' WHERE id = 1"; // + QString::number(id_row);
    if (!query.exec(sql)){ cntrl = false; error_log += "exec_t ";}
    data_base.close();
    if(cntrl){ qDebug() << "Update record\t\tOK"; }
    else { qDebug() << "Update record\t\tNOT OK" << Qt::endl << error_log; }
}
                    // SHOW DATA //
void show_vec(QVector <task_data_struct> task_data_vec){
    bool cntrl = true; QString error_log;
    if (task_data_vec.isEmpty()){ cntrl = false; error_log += "vector_empty ";}
    for(int i = 0; i < task_data_vec.size(); i++){
        qDebug() << task_data_vec[i].tID << task_data_vec[i].tName << task_data_vec[i].tData << task_data_vec[i].tBrigade << task_data_vec[i].tProgress;
    }
    if(!cntrl) { qDebug() << "Show tasks vector\t\tNOT OK" << Qt::endl << error_log; }
}
void show_vec(QVector <project_data_struct> project_data_vec){
    bool cntrl = true; QString error_log;
    if (project_data_vec.isEmpty()){ cntrl = false; error_log += "vector_empty ";}
    for(int i = 0; i < project_data_vec.size(); i++){
        qDebug() << project_data_vec[i].pID << project_data_vec[i].pName << project_data_vec[i].pImage << project_data_vec[i].pData << project_data_vec[i].pTask << project_data_vec[i].pBrigade;
    }
    if(!cntrl) { qDebug() << "Show projects vector\t\tNOT OK" << Qt::endl << error_log; }
}
void show_exist_tables(QSqlDatabase data_base){
    bool cntrl = true; QString error_log;
    if (!data_base.open()){ cntrl = false; error_log += "open ";}
    qDebug() << data_base.tables();
    data_base.close();
    if(cntrl){ qDebug() << "Show table names\t\tOK"; }
    else { qDebug() << "Show table names\t\tNOT OK" << Qt::endl << error_log; }
}
