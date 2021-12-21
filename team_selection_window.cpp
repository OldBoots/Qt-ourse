#include "team_selection_window.h"
#include <QDebug>

team_selection_window::team_selection_window(QStringList list_task, QStringList list_project, QWidget *parent) : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
setAttribute(Qt::WA_QuitOnClose);
    QButtonGroup * hhh = new QButtonGroup;
    hhh->setExclusive(0);
    booling hg;
    bool true_flag = false;
    qDebug() << "test";
    for(int i = 0; i < list_project.size(); i++){
        qDebug() << "test" << i;
        rbutt[i]->setText(list_project[i]);
        for(int j = 0; j < list_task.size(); j++){
            if(list_project[i] == list_task[j]){
                true_flag = true;
            }
        }
        if(true_flag){
            rbutt[i]->setChecked(true);
        }
        hhh->addButton(rbutt[i]);
        vbox->addWidget(rbutt[i]);
        true_flag = false;
    }
n = list_project.size();
    vbox->addWidget(ok);
    setLayout(vbox);

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
}


