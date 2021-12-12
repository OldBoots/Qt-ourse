#include "mainwindow.h"
#include "DBFun.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
//    QVector <task_data_struct> t_vec;
//    task_data_struct t_form;
//    for (int i = 0; i < 4; i++){
//        t_form.tName = "Vova" + QString::number(i);
//        t_form.tBrigade = "Dima Dfgre" + QString::number(i);
//        t_form.tData = "Gopa" + QString::number(i);
//        t_form.tProgress = "ghfd" + QString::number(i);
//        t_vec.push_back(t_form);
//    }
//    QVector <project_data_struct> p_vec;
//    project_data_struct p_form;
//    for (int i = 0; i < 4; i++){
//        p_form.pName = "Gig" + QString::number(i);
//        p_form.pImage = "ggg" + QString::number(i);
//        p_form.pData = "Fit" + QString::number(i);
//        p_form.pBrigade = "Breh\ntttrt" + QString::number(i);
//        p_form.pTask = "Gog" + QString::number(i);
//        p_vec.push_back(p_form);
//    }
    QSqlDatabase data_base = QSqlDatabase::addDatabase("QSQLITE");
    data_base.setDatabaseName("dbProject.sqlite");
//    create_project_tables(data_base, 0);
//    create_project_tables(data_base, 1);
//    create_project_tables(data_base, 2);
//    record_task_data(data_base, 0, t_vec);
//    record_project_data(data_base, 0, p_vec);
//    show_exist_tables(data_base);
//    QVector <task_data_struct> tt_vec;
//    QVector <project_data_struct> pp_vec;
//    read_task_table(data_base, 0, tt_vec);
//    read_project_table(data_base, 0, pp_vec);
//    show_vec(tt_vec);
//    show_vec(pp_vec);
//    delete_row(data_base, "tasks0", 2);
//    change_value(data_base, "tasks0", "tName", "OOOOOOOO", 1);
//    delete_project(data_base, 0);
//    read_task_table(data_base, 0, tt_vec);
//    read_project_table(data_base, 0, pp_vec);
//    show_vec(tt_vec);
//    show_vec(pp_vec);
    return a.exec();
}
