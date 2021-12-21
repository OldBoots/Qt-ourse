#include "mainwindow.h"
#include "DBFun.h"
#include "select_window.h"
#include "project_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//        project_window win;
        select_window win;
        win.show();
    //    MainWindow w;
    //    w.show();
//    QVector <task_data_struct> t_vec;
//    task_data_struct t_form;
//    for (int i = 0; i < 4; i++){
//        t_form.tName = "Задача" + QString::number(i);
//        t_form.tBrigade = "Бригада1\nБригада2\nБригада2\n";
//        t_form.tDate = "12.12.12" + QString::number(i);
//        t_form.tProgress = QString::number(i * 10);
//        t_vec.push_back(t_form);
//    }
//    QVector <project_data_struct> p_vec;
//    project_data_struct p_form;
//    for (int i = 0; i < 3; i++){
//        p_form.pName = "Проект" + QString::number(i);
//        p_form.pImage = "C:\\Study2021\\Visual\\ProjectsImage\\" + QString::number(i) + ".jpg";
//        p_form.pDate = "10.10.12-\n12.21.32";
//        p_form.pBrigade = "Бригада1\nБригада2\nБригада3\nБригада4";
//        p_form.pTask = "Задача1\nЗадача2\nЗадача3\nЗадача4";
//        p_vec.push_back(p_form);
//    }
//    QSqlDatabase data_base = QSqlDatabase::addDatabase("QSQLITE");
//    data_base.setDatabaseName("dbProject.sqlite");
//    create_project_table(data_base);
//    create_task_table(data_base, 0);
//    create_task_table(data_base, 1);
//    create_task_table(data_base, 2);
//    create_task_table(data_base, 3);
//    record_task_data(data_base, 0, t_vec);
//    record_task_data(data_base, 1, t_vec);
//    record_task_data(data_base, 2, t_vec);
//    record_task_data(data_base, 3, t_vec);
//    record_project_data(data_base, p_vec);
//    show_exist_tables(data_base);
//    QVector <task_data_struct> tt_vec;
//    QVector <project_data_struct> pp_vec;
//    read_task_table(data_base, 0, tt_vec);
//    read_project_table(data_base, pp_vec);
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
