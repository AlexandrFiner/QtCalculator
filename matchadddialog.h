#ifndef MATCHADDDIALOG_H
#define MATCHADDDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <team.h>

class QLineEdit;
class QPushButton;

class MatchAddDialog: public QDialog
{
    Q_OBJECT

public:
    MatchAddDialog(QWidget *parent = 0);
    QString getNameOneString();
    QString getNameTwoString();
    int getScoreOne();
    int getScoreTwo();

public slots:
    void findClicked();

private:
    QPushButton *addButton;
    QLineEdit *lineEditOne;
    QLineEdit *lineEditTwo;
    QLineEdit *lineEditScoreOne;
    QLineEdit *lineEditScoreTwo;

    QString teamOneText;
    QString teamTwoText;

    int score_one;
    int score_two;
};

#endif // MATCHADDDIALOG_H
