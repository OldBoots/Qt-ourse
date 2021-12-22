#include "select_window.h"

select_window::select_window(QWidget * parent) : QWidget(parent)
{

    data_base.setDatabaseName("dbProject.sqlite");
    editor = new project_window(data_base);
    connect(this, SIGNAL(signal_set_ABS(int)), editor, SLOT(slot_set_ABS(int)));

    read_project_table(data_base, vec_data);
    for(int i = 0; i < vec_data.size(); i++){
        vec_index << i;
        vec_view_index << i;
    }
    hbox[0].addWidget(create_butt);

    seek_butt->setIcon(QIcon(QPixmap(":/loup.png")));
    hbox[0].addWidget(seek_butt);

    seek_line->setPlaceholderText("Поиск...");
    hbox[0].addWidget(seek_line);

    vbox[0].addWidget(table);
    vbox[0].addLayout(&hbox[0]);

    hbox[1].addLayout(&vbox[0]);

    show_table();

    vbox[1].addWidget(name);
    vbox[1].addWidget(imag);
    vbox[1].addWidget(area);

    hbox[1].addLayout(&vbox[1]);

    setLayout(&hbox[1]);

    //      CONNECT
    connect(table, SIGNAL(cellClicked(int, int)), this, SLOT(slot_show_info(int, int)));
    connect(table, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slot_run_editor(int, int)));
    connect(seek_butt, SIGNAL(clicked()), this, SLOT(slot_seek()));
    connect(editor, SIGNAL(signal_go_back()), this, SLOT(show()));
    connect(create_butt, SIGNAL(clicked()), this, SLOT(slot_new_project()));

}

void select_window::slot_new_project(){
    bool ok;
    project_data_struct trt;
    QString new_name = QInputDialog::getText(this,
                                             QString::fromUtf8("Имя проекта"),
                                             QString::fromUtf8("Имя:"),
                                             QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if (ok && !new_name.isEmpty()){
        trt.pName = new_name;
        add_project_record(data_base, trt);
        vec_data.clear();
        read_project_table(data_base, vec_data);
        int last_id = 0;
        for(int i = 0; i < vec_data.size(); i++){
            last_id = qMax(last_id, vec_data[i].pID);
        }
        create_task_table(data_base, last_id);

//        emit signal_set_ABS(last_id);
//        editor->show();
//        this->close();

        vec_view_index.clear();
        vec_index.clear();
        for(int i = 0; i < vec_data.size(); i++){
            vec_index << i;
            vec_view_index << i;
        }
        vec_view_index = vec_index;
         show_table();
    }
}

void select_window::slot_run_editor(int row, int column){
    qDebug() << "row " << row;
    Q_UNUSED (column);
    emit signal_set_ABS(row);
    editor->show();
    this->close();
}

void select_window::slot_show_info(int row, int column){
    Q_UNUSED (column);
        QFont font;
        font.setPixelSize(14);

        name->setText(vec_data[vec_view_index[row]].pName);
        name->setAlignment(Qt::AlignCenter);
        name->setFont(font);

        imag->setPixmap(QPixmap(vec_data[vec_view_index[row]].pImage).scaled(120, 120));
        imag->setAlignment(Qt::AlignCenter);

        info->setText("Дата:\n"
                      + vec_data[vec_view_index[row]].pDate
                      + "\nБригады:\n"
                      + vec_data[vec_view_index[row]].pBrigade
                      + "\nЗадачи:\n"
                      + vec_data[vec_view_index[row]].pTask);
        info->setAlignment(Qt::AlignCenter);
        info->setFont(font);

        area->setWidget(info);
        area->setAlignment(Qt::AlignCenter);
}

void select_window::sort_table(){

}

void select_window::slot_seek(){
    vec_view_index.clear();
    QString seek_str = seek_line->text();
    if(seek_str != ""){
        for(int i = 0; i < vec_data.size(); i++){
            if(vec_data[i].pName.contains(seek_str, Qt::CaseInsensitive)){
                vec_view_index << vec_index[i];
            }
        }
    }
    show_table();
}

void select_window::show_table(){
    table->clear();
    QTableWidgetItem *item;
    table->setColumnCount(2);
    table->setRowCount(vec_view_index.size());
    table->setShowGrid(false);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->horizontalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->setColumnWidth(0,64);
    for(int i = 0; i < vec_view_index.size(); i++){
        table->setRowHeight(i,64);
        item = new QTableWidgetItem;
        item->setBackground(QBrush(QPixmap(vec_data[vec_view_index[i]].pImage).scaled(64, 64)));
        table->setItem(i, 0, item);
        item = new QTableWidgetItem;
        item->setText(vec_data[vec_view_index[i]].pName);
        table->setItem(i, 1, item);
    }
}
