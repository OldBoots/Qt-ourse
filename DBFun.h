#ifndef DBFUN_H
#define DBFUN_H

#include <QtSql>


struct project_data_struct
{
    int pID;
    QString pName;
    QString pImage;
    QString pData;
    QString pTask;
    QString pBrigade;
};

struct task_data_struct
{
    int tID;
    QString tName;
    QString tData;
    QString tBrigade;
    QString tProgress;
};

void create_project_tables(QSqlDatabase data_base, int id_table);

void record_task_data(QSqlDatabase data_base, int id_table, QVector <task_data_struct> task_data_vec);
void record_project_data(QSqlDatabase data_base, int id_table, QVector <project_data_struct> project_data_vec);
void add_task_record(QSqlDatabase data_base, int id_table, task_data_struct task_data_vec);
void add_project_record(QSqlDatabase data_base, int id_table, project_data_struct project_data_vec);

void read_task_table(QSqlDatabase data_base, int id_table, QVector <task_data_struct> &task_data_vec);
void read_project_table(QSqlDatabase data_base, int id_table, QVector <project_data_struct> &project_data_vec);

void delete_row(QSqlDatabase data_base, QString name_table, int id_row);
void delete_project(QSqlDatabase data_base, int id_table);

void change_value(QSqlDatabase data_base, QString name_table, QString name_fild, QString value, int id_row);

void show_vec(QVector <task_data_struct> task_data_vec);
void show_vec(QVector <project_data_struct> project_data_vec);
void show_exist_tables(QSqlDatabase data_base);

#endif // DBFUN_H
