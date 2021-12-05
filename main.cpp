#include "mainwindow.h"
#include "DBFun.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //    MainWindow w;
    //    w.show();
    QVector <task_data_struct> struct_vec;
//    task_data_struct form;
//    for (int i = 0; i < 2; i++){
//        form.tName = "Vova" + QString::number(i);
//        form.tBrigade = "Dima" + QString::number(i);
//        form.tData = "Gopa" + QString::number(i);
//        form.tProgress = "ghfd" + QString::number(i);
//        struct_vec.push_back(form);
//    }
    QSqlDatabase data_base = QSqlDatabase::addDatabase("QSQLITE");
    data_base.setDatabaseName("pdb.sqlite");
//    create_table(data_base, 0, 0);
//    record_data(data_base, 0, struct_vec);
//    struct_vec.clear();
//        read_data(data_base, 0, struct_vec);
//        for(int i = 0; i < struct_vec.size(); i++){
//            qDebug() << struct_vec[i].tName << struct_vec[i].tData << struct_vec[i].tBrigade << struct_vec[i].tProgress;
//        }
    return a.exec();
}
