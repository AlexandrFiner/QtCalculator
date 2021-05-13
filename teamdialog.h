#ifndef TEAMDIALOG_H
#define TEAMDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <team.h>

class QLineEdit;
class QPushButton;

class TeamDialog: public QDialog
{
    Q_OBJECT

public:
    TeamDialog(QWidget *parent = 0);
    QString getNameString();

public slots:
    void findClicked();

private:
    QPushButton *addButton;
    QLineEdit *lineEdit;
    QString teamText;
};

#endif // TEAMDIALOG_H
