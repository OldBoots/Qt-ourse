#ifndef SELECT_WINDOW_H
#define SELECT_WINDOW_H

#include <QWidget>
#include <QObject>
#include <QTreeView>
#include <QTableWidget>
#include <QLayout>
#include <QLabel>
#include <QWidget>
#include <QScrollArea>
#include <QIcon>
#include <QLineEdit>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QDate>

#include "project_window.h"
//#include <QTextEdit>

#include "DBFun.h"

class select_window : public QWidget
{
    Q_OBJECT
public:
    select_window(QWidget *parent = 0);
private:
    QSqlDatabase data_base = QSqlDatabase::addDatabase("QSQLITE");
    project_window *editor;
    QVector <int> vec_index;
    QVector <int> vec_view_index;
    QVector <project_data_struct> vec_data;
    QVBoxLayout *vbox = new QVBoxLayout[2];
    QHBoxLayout *hbox = new QHBoxLayout[2];
    QScrollArea *area = new QScrollArea;
    QLineEdit *seek_line = new QLineEdit;
    QPushButton *seek_butt = new QPushButton;
    QPushButton *create_butt = new QPushButton("Создать");
    QTableWidget *table = new QTableWidget;
    QLabel *name = new QLabel;
    QLabel *info = new QLabel;
    QLabel *imag = new QLabel;
private:
    void sort_table();
    void show_table();
private slots:
    void slot_seek();
    void slot_show_info(int row, int column);
    void slot_run_editor(int row, int column);
    void slot_new_project();
signals:
    void signal_set_ABS(int row);
};
#endif // SELECT_WINDOW_H
