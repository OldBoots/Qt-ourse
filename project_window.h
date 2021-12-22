#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlDatabase>
#include <QLabel>
#include <QScrollArea>
#include <QInputDialog>
#include <QMessageBox>
#include <QFileDialog>

#include "DBFun.h"
#include "dialog.h"
//#include "select_window.h"

class project_window : public QWidget
{
    Q_OBJECT
public:
    project_window(QSqlDatabase data_base1, QWidget *parent = 0);
private:
    int abs_index = 0;
    bool red_falg;
    QList <QString> list_brigade;
    QSqlDatabase data_base;
    QTableWidget *table_brigade = new QTableWidget;
    QTableWidget *table_task = new QTableWidget;
    QVBoxLayout *vbox = new QVBoxLayout[2];
    QHBoxLayout *hbox = new QHBoxLayout[5];
    QScrollArea *area = new QScrollArea;
    QPushButton *butt_back = new QPushButton;
    QPushButton *butt_report = new QPushButton;
    QPushButton *butt_redact = new QPushButton;
    QPushButton *butt_load_pix = new QPushButton;
    QLabel *project_image = new QLabel;
    QLabel *lbl_start = new QLabel;
    QLabel *lbl_end = new QLabel;
    QLabel *lbl_task = new QLabel;
    QLabel *lbl_brig = new QLabel;
    QLineEdit *name_project_line = new QLineEdit;
    QLineEdit *start_date_line = new QLineEdit;
    QLineEdit *end_date_line = new QLineEdit;
    QVector <project_data_struct> vec_porject_data;
    QVector <task_data_struct> vec_task_data;
private:
    void show_brigade_table(bool red_falg);
    void show_task_table(bool red_falg);
    void show_info(bool red_falg = false);
private slots:
    void slot_change_image();
    void slot_change_red_flag();
    void slot_change_brig_data(int row, int column);
    void slot_change_task_data(int row, int column);
    void slot_change_name_project();
    void slot_change_start_data();
    void slot_change_end_data();
    void slot_go_back();
    void slot_set_ABS(int index);
signals:
    void signal_go_back();
};

#endif // PROJECT_WINDOW_H
