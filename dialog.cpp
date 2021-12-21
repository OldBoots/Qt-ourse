#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
//    setAttribute(Qt::WA_DeleteOnClose);
//    setAttribute(Qt::WA_QuitOnClose);
}

QString Dialog::getString(QStringList list_task_brig, QStringList list_brig){
    QString str;
    bool dof;
    bool first = false;
    QCheckBox * chbox;
    for(int i = 0; i < list_brig.size(); i++){
        dof = 0;
        chbox = new QCheckBox;
        chbox->setText(list_brig[i]);
        for(int j = 0; j < list_task_brig.size(); j++){
            if(list_brig[i] == list_task_brig[j]){
                dof = 1;
            }
        }
        chbox->setChecked(dof);
        vec_chb << chbox;
        vbox->addWidget(vec_chb[i]);
    }
    vbox->addWidget(ok);
    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    setLayout(vbox);
    this->exec();
    for(int i = 0; i < list_brig.size(); i++){
        if (vec_chb[i]->isChecked()){
            if (first){
                str += "\n";
            }
            first = true;
            str += vec_chb[i]->text();
        }
    }
    qDebug() << str;
    return str;
}

Dialog::~Dialog()
{
}

