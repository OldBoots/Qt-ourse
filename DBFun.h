#ifndef DBFUN_H
#define DBFUN_H

#include <QtSql>


struct project_data_struct
{
    QString pName;
    QString pImage;
    QString pData;
    QString pTask;
    QString pBrigade;
};

struct task_data_struct
{
    QString tName;
    QString tData;
    QString tBrigade;
    QString tProgress;
};

void create_table(QSqlDatabase data_base, int table_id, bool project_table_flag);
void record_data(QSqlDatabase data_base, int table_id, QVector <task_data_struct> task_data_vec);
void record_data(QSqlDatabase data_base, int table_id, QVector <project_data_struct> project_data_vec);
void read_data(QSqlDatabase data_base, int table_id, QVector <task_data_struct> &task_data_vec);
void read_data(QSqlDatabase data_base, int table_id, QVector <project_data_struct> &project_data_vec);
void delete_data(QSqlDatabase data_base, int table_id, QString fild, bool project_table_flag);
void delete_table(QSqlDatabase data_base, int table_id, QString table_name);


#endif // DBFUN_H
