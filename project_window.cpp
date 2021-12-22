#include "project_window.h"


project_window::project_window(QSqlDatabase data_base1, QWidget * parent) : QWidget(parent)
{
    //    abs_index = 0;

    data_base = data_base1;
    read_project_table(data_base, vec_porject_data);
    read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);

    butt_back->setIcon(QIcon(QPixmap(":/arrow.png")));
    butt_back->setMaximumWidth(32);

    hbox[0].addWidget(butt_back);
    hbox[0].addWidget(name_project_line, 1);

    lbl_start->setText("Старт ");
    lbl_start->setMaximumWidth(40);

    hbox[1].addWidget(lbl_start);
    hbox[1].addWidget(start_date_line, 1);

    lbl_end->setText("Конец");
    lbl_end->setMaximumWidth(40);

    hbox[2].addWidget(lbl_end);
    hbox[2].addWidget(end_date_line, 1);

    butt_redact->setText("Изменить");
    butt_report->setText("Отчет");

    hbox[3].addWidget(butt_redact);
    hbox[3].addWidget(butt_report);

    vbox[0].addLayout(&hbox[0], 1);
    vbox[0].addLayout(&hbox[1], 1);
    vbox[0].addLayout(&hbox[2], 1);
    lbl_brig->setText("Бригады:");
    vbox[0].addWidget(lbl_brig, 1, Qt::AlignCenter);
    vbox[0].addWidget(table_brigade);
    lbl_task->setText("Задачи:");
    vbox[0].addWidget(lbl_task, 1, Qt::AlignCenter);
    vbox[0].addWidget(table_task);
    vbox[0].addLayout(&hbox[3]);
    butt_load_pix->setText("Загрузить картинку");
    vbox[0].addWidget(butt_load_pix, 1, Qt::AlignCenter);

    project_image->setPixmap(QPixmap(vec_porject_data[abs_index].pImage));
    area->setWidget(project_image);
    hbox[4].addLayout(&vbox[0], 1);
    hbox[4].addWidget(area);
    qDebug() << "show_info0";
    setLayout(&hbox[4]);

    //    CONNECT
    connect(butt_redact, SIGNAL(clicked()), this, SLOT(slot_change_red_flag()));
    connect(table_brigade, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_change_brig_data(int, int)));
    connect(name_project_line, SIGNAL(editingFinished()), this, SLOT(slot_change_name_project()));
    connect(start_date_line, SIGNAL(editingFinished()), this, SLOT(slot_change_start_data()));
    connect(end_date_line, SIGNAL(editingFinished()), this, SLOT(slot_change_end_data()));
    connect(table_task, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_change_task_data(int, int)));
    connect(butt_load_pix, SIGNAL(clicked()), this, SLOT(slot_change_image()));
    connect(butt_back, SIGNAL(clicked()), this, SLOT(slot_go_back()));
}

void project_window::slot_go_back(){
    this->close();
    emit signal_go_back();
}

void project_window::slot_set_ABS(int index){
    abs_index = index;

    red_falg = 0;
    vec_porject_data.clear();
    vec_task_data.clear();
    read_project_table(data_base, vec_porject_data);
    read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);

    show_info(red_falg);
    qDebug() << "show_info1";

    show_brigade_table(red_falg);
    qDebug() << "show_info2";

    show_task_table(red_falg);
    qDebug() << "show_info3";
}

void project_window::show_info(bool red_falg){
    if(!vec_porject_data[abs_index].pDate.isEmpty()){
        QList <QString> list_date = vec_porject_data[abs_index].pDate.split("-\n");
        start_date_line->setText(list_date[0]);
        end_date_line->setText(list_date[1]);
    }
    name_project_line->setText(vec_porject_data[abs_index].pName);
    name_project_line->setMaximumWidth(250);
    start_date_line->setMaximumWidth(250);
    end_date_line->setMaximumWidth(250);
    name_project_line->setReadOnly(!red_falg);
    start_date_line->setReadOnly(!red_falg);
    end_date_line->setReadOnly(!red_falg);
}

void project_window::show_brigade_table(bool red_falg){
    table_brigade->clear();
    list_brigade = vec_porject_data[abs_index].pBrigade.split("\n");
    QTableWidgetItem *item;
    if(red_falg){
        table_brigade->setRowCount(list_brigade.size() + 1);
        table_brigade->setColumnCount(2);
        table_brigade->setColumnWidth(1,32);
    } else {
        table_brigade->setRowCount(list_brigade.size());
        table_brigade->setColumnCount(1);
    }
    table_brigade->setShowGrid(false);
    table_brigade->setMaximumWidth(350);
    table_brigade->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_brigade->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_brigade->horizontalHeader()->hide();
    table_brigade->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table_brigade->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table_brigade->setColumnWidth(0,235);

    for(int i = 0; i < list_brigade.size(); i++){
        item = new QTableWidgetItem;
        item->setText(list_brigade[i]);
        item->setTextAlignment(Qt::AlignCenter);
        table_brigade->setItem(i, 0, item);
        if(red_falg){
            item = new QTableWidgetItem;
            item->setIcon(QIcon(QPixmap(":/cross.png")));
            table_brigade->setItem(i, 1, item);
        }
    }
    if(red_falg){
        item = new QTableWidgetItem;
        item->setText("Создать строку");
        item->setTextAlignment(Qt::AlignCenter);
        table_brigade->setItem(list_brigade.size(), 0, item);
    }

}

void project_window::show_task_table(bool red_falg){
    table_task->clear();
    QTableWidgetItem *item;
    if(red_falg){
        table_task->setRowCount(vec_task_data.size() + 1);
        table_task->setColumnCount(5);
        table_task->setColumnWidth(4,32);
    } else {
        table_task->setRowCount(vec_task_data.size());
        table_task->setColumnCount(4);
    }
    table_task->setShowGrid(false);
    table_task->setMaximumWidth(350);
    table_task->setSelectionBehavior(QAbstractItemView::SelectRows);
    table_task->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_task->horizontalHeader()->hide();
    table_task->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table_task->setColumnWidth(3,32);
    table_task->setColumnWidth(2,72);
    table_task->setColumnWidth(1,62);
    table_task->setColumnWidth(0,62);

    for(int i = 0; i < vec_task_data.size(); i++){
        table_task->setRowHeight(i,62);
        item = new QTableWidgetItem;
        item->setText(vec_task_data[i].tName);
        table_task->setItem(i, 0, item);
        item = new QTableWidgetItem;
        item->setText(vec_task_data[i].tDate);
        table_task->setItem(i, 1, item);
        item = new QTableWidgetItem;
        item->setText(vec_task_data[i].tBrigade);
        table_task->setItem(i, 2, item);
        item = new QTableWidgetItem;
        item->setText(vec_task_data[i].tProgress + "%");
        table_task->setItem(i, 3, item);
        if(red_falg){
            item = new QTableWidgetItem;
            item->setIcon(QIcon(QPixmap(":/cross.png")));
            table_task->setItem(i, 4, item);
        }
    }
    if(red_falg){
        item = new QTableWidgetItem;
        item->setText("Создать строку");
        item->setTextAlignment(Qt::AlignCenter);
        table_task->setItem(vec_task_data.size(), 2, item);
    }

}

void project_window::slot_change_image(){
    QString path = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
                                                QDir::currentPath(),
                                                "Images (*.png *.xpm *.jpg)");
    if(!path.isEmpty()){
        project_image->setPixmap(QPixmap(path));
        change_value(data_base, "projects", "pImage", path,  vec_porject_data[abs_index].pID);
        vec_porject_data.clear();
        read_project_table(data_base, vec_porject_data);
        show_brigade_table(red_falg);
    }
}

void project_window::slot_change_red_flag(){
    if(red_falg){
        red_falg = false;
        butt_redact->setText("Изменить");
        butt_report->setEnabled(true);
    } else {
        butt_redact->setText("Закончить");
        butt_report->setEnabled(false);
        red_falg = true;
    }
    show_info(red_falg);
    show_brigade_table(red_falg);
    show_task_table(red_falg);
}

void project_window::slot_change_brig_data(int row, int column){
    if(row == list_brigade.size() && red_falg){
        bool ok;
        int num_brig = QInputDialog::getInt(this, QString::fromUtf8("Добавить бригаду"),
                                            QString::fromUtf8("Бригада номер:"), 0, 0, 100, 1, &ok);
        if (ok){
            QString str = vec_porject_data[abs_index].pBrigade + "\nБригада" + QString::number(num_brig) + "";
            change_value(data_base, "projects", "pBrigade", str,  vec_porject_data[abs_index].pID);
            vec_porject_data.clear();
            read_project_table(data_base, vec_porject_data);
            show_brigade_table(red_falg);
        }
    }
    if(column == 1 && red_falg && row != list_brigade.size()){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Удаление"),
                                      QString::fromUtf8("Хотите удалить запись?"),
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes){
            QString str;
            for(int i = 0; i < list_brigade.size(); i++){
                if(i != row){
                    if(i != 0){ str += "\n"; }
                    str += list_brigade[i];
                }
            }
            change_value(data_base, "projects", "pBrigade", str,  vec_porject_data[abs_index].pID);
            vec_porject_data.clear();
            read_project_table(data_base, vec_porject_data);
            show_brigade_table(red_falg);
        }
    }
}

void project_window::slot_change_task_data(int row, int column){
    qDebug() << row << "  " << column;
    if(row == vec_task_data.size() && red_falg){
        task_data_struct form;
        form.tName = "Задача";
        form.tDate = "21.12.21";
        form.tBrigade = "";
        form.tProgress = "0";
        add_task_record(data_base, vec_porject_data[abs_index].pID, form);
        vec_task_data.clear();
        read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);
        show_task_table(red_falg);
    }
    if(red_falg && row != vec_task_data.size() && column == 0){
        bool ok;
        QString new_name = QInputDialog::getText(this,
                                                 QString::fromUtf8("Изменить"),
                                                 QString::fromUtf8("Задача:"),
                                                 QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
        if (ok && !new_name.isEmpty()){
            change_value(data_base, "tasks" + QString::number(vec_porject_data[abs_index].pID), "tName", new_name, vec_task_data[row].tID);
        }
        vec_task_data.clear();
        read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);
        show_task_table(red_falg);
    }
    if(red_falg && row != vec_task_data.size() && column == 1){
        bool ok;
        QString new_date = QInputDialog::getText(this,
                                                 QString::fromUtf8("Изменить дату"),
                                                 QString::fromUtf8("Новая дата:"),
                                                 QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
        if (ok && !new_date.isEmpty()){
            if(new_date.size() == 10){
                bool true_date = false;
                for(int i = 0, count = 0; i < new_date.size(); i++){
                    if(new_date[i].isNumber() || new_date[i] == '.'){
                        if(++count == 10){ true_date = true; }
                    }
                }
                if(true_date){
                    change_value(data_base, "tasks" + QString::number(vec_porject_data[abs_index].pID), "tDate", new_date, vec_task_data[row].tID);
                    vec_task_data.clear();
                    read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);
                }
            }
        }
        show_task_table(red_falg);
    }
    if(red_falg && row != vec_task_data.size() && column == 2){
        QStringList task_list = vec_task_data[row].tBrigade.split("\n");
        QString selected_brig;
        Dialog *myDialog = new Dialog(this);
        selected_brig = myDialog->getString(task_list, list_brigade);
        if(!selected_brig.isEmpty()){
            change_value(data_base, "tasks" + QString::number(vec_porject_data[abs_index].pID), "tBrigade", selected_brig, vec_task_data[row].tID);
            vec_task_data.clear();
            read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);
        }
        show_task_table(red_falg);
    }
    if(red_falg && row != vec_task_data.size() && column == 3){
        bool ok;
        int new_proc = QInputDialog::getInt(this, QString::fromUtf8("Введите процент"),
                                            QString::fromUtf8("Процент:"), 0, 0, 100, 1, &ok);
        if (ok){
            change_value(data_base, "tasks" + QString::number(vec_porject_data[abs_index].pID), "tProgress", QString::number(new_proc), vec_task_data[row].tID);
            vec_task_data.clear();
            read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);
        }
        show_task_table(red_falg);
    }
    if(red_falg && row != vec_task_data.size() && column == 4){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, QString::fromUtf8("Удаление"),
                                      QString::fromUtf8("Хотите удалить запись?"),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes){
            delete_row(data_base, "tasks" + QString::number(vec_porject_data[abs_index].pID), vec_task_data[row].tID);
            vec_task_data.clear();
            read_task_table(data_base, vec_porject_data[abs_index].pID, vec_task_data);
            show_task_table(red_falg);
        }
    }
}

void project_window::slot_change_name_project(){
    QString new_name = name_project_line->text();
    if(red_falg ){
        if(!new_name.isEmpty()){
            change_value(data_base, "projects", "pName", new_name,  vec_porject_data[abs_index].pID);
            vec_porject_data.clear();
            read_project_table(data_base, vec_porject_data);
        }
        show_info(red_falg);
    }
}

void project_window::slot_change_start_data(){
    QString new_date = start_date_line->text();
    if(red_falg ){
        if(!new_date.isEmpty() && new_date.size() == 10){
            bool true_date = false;
            for(int i = 0, count = 0; i < new_date.size(); i++){
                if(new_date[i].isNumber() || new_date[i] == '.'){
                    if(++count == 10){ true_date = true; }
                }
            }
            if(true_date){
                QList <QString> list_date = vec_porject_data[abs_index].pDate.split("-\n");
                change_value(data_base, "projects", "pDate", new_date + "-\n" + list_date[1],  vec_porject_data[abs_index].pID);
                vec_porject_data.clear();
                read_project_table(data_base, vec_porject_data);
            }
        }
        show_info(red_falg);
    }
}

void project_window::slot_change_end_data(){
    QString new_date = end_date_line->text();
    if(red_falg ){
        if(!new_date.isEmpty() && new_date.size() == 10){
            bool true_date = false;
            for(int i = 0, count = 0; i < new_date.size(); i++){
                if(new_date[i].isNumber() || new_date[i] == '.'){
                    if(++count == 10){ true_date = true; }
                }
            }
            if(true_date){
                QList <QString> list_date = vec_porject_data[abs_index].pDate.split("-\n");
                change_value(data_base, "projects", "pDate",  list_date[0] + "-\n" + new_date,  vec_porject_data[abs_index].pID);
                vec_porject_data.clear();
                read_project_table(data_base, vec_porject_data);
            }
        }
        show_info(red_falg);
    }
}
