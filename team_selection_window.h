#ifndef TEAM_SELECTION_WINDOW_H
#define TEAM_SELECTION_WINDOW_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QRadioButton>
#include <QStringList>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>

struct booling{
    bool boo;
    QString str;
};

class team_selection_window : public QDialog
{
    Q_OBJECT
public:
    team_selection_window(QStringList list_task, QStringList list_project, QWidget *parent = 0);
    void getBrig(QString &selected_teams);
private:
    int n;
    QRadioButton *rbutt[30];
    QVector <booling> vec_strct;
    QVBoxLayout *vbox = new QVBoxLayout;
    QPushButton *ok = new QPushButton("Ok");

private:

};

#endif // TEAM_SELECTION_WINDOW_H
