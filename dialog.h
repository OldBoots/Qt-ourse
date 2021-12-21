#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    QVBoxLayout * vbox = new QVBoxLayout;
    QPushButton * ok = new QPushButton("Ok");
    QVector <QCheckBox *> vec_chb;
public:
    QString getString(QStringList t, QStringList nt);
};
#endif // DIALOG_H
