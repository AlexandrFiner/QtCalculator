#include <QtGui>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "matchadddialog.h"

MatchAddDialog::MatchAddDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setObjectName("MainWidget");
    setWindowFlag(Qt::WindowStaysOnTopHint);    // Чтоб всегда было выше

    lineEditOne = new QLineEdit;
    lineEditOne->setPlaceholderText(tr("Название первой команды"));
    lineEditOne->setAttribute(Qt::WA_MacShowFocusRect, 0);

    lineEditTwo = new QLineEdit;
    lineEditTwo->setPlaceholderText(tr("Название второй команды"));
    lineEditTwo->setAttribute(Qt::WA_MacShowFocusRect, 0);

    lineEditScoreOne = new QLineEdit;
    lineEditScoreOne->setPlaceholderText(tr("Количество забитых голов"));
    lineEditScoreOne->setValidator(new QIntValidator(0, 999, this));
    lineEditScoreOne->setAttribute(Qt::WA_MacShowFocusRect, 0);

    lineEditScoreTwo = new QLineEdit;
    lineEditScoreTwo->setPlaceholderText(tr("Количество забитых голов"));
    lineEditScoreTwo->setValidator(new QIntValidator(0, 999, this));
    lineEditScoreTwo->setAttribute(Qt::WA_MacShowFocusRect, 0);

    addButton = new QPushButton(tr("&Создать матч"));
    teamOneText = "";
    teamTwoText = "";
    score_one = 0;
    score_two = 0;

    QVBoxLayout *layoutOne = new QVBoxLayout;
    layoutOne->addWidget(new QLabel(tr("Введите название первой команды:")));
    layoutOne->addWidget(lineEditOne);
    layoutOne->addWidget(new QLabel(tr("Забито голов:")));
    layoutOne->addWidget(lineEditScoreOne);

    QVBoxLayout *layoutTwo = new QVBoxLayout;
    layoutTwo->addWidget(new QLabel(tr("Введите название второй команды:")));
    layoutTwo->addWidget(lineEditTwo);
    layoutTwo->addWidget(new QLabel(tr("Забито голов:")));
    layoutTwo->addWidget(lineEditScoreTwo);

    QVBoxLayout *layoutBtn = new QVBoxLayout;
    layoutBtn->addWidget(addButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(layoutOne, 1, 1);
    mainLayout->addLayout(layoutTwo, 1, 2);
    mainLayout->addLayout(layoutBtn, 1, 3);
    setLayout(mainLayout);

    setWindowTitle(tr("Добавить матч"));
    connect(addButton, SIGNAL(clicked()), this, SLOT(findClicked()));
}

void MatchAddDialog::findClicked() {

    QString textOne = lineEditOne->text();
    textOne = textOne.trimmed();
    if(textOne.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"), tr("Вы не ввели название первой команды."));
        return;
    }

    QString textTwo = lineEditTwo->text();
    textTwo = textTwo.trimmed();
    if(textTwo.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"), tr("Вы не ввели название второй команды."));
        return;
    }

    int scoreOne = lineEditScoreOne->text().toInt();
    if(scoreOne < 0) {
        QMessageBox::information(this, tr("Empty Field"), tr("Вы ввели количество голов меньшее 0"));
        return;
    }

    int scoreTwo = lineEditScoreTwo->text().toInt();
    if(scoreTwo < 0) {
        QMessageBox::information(this, tr("Empty Field"), tr("Вы ввели количество голов меньшее 0"));
        return;
    }

    score_one = scoreOne;
    score_two = scoreTwo;
    teamOneText = textOne;
    teamTwoText = textTwo;
    lineEditOne->clear();
    lineEditTwo->clear();
    lineEditScoreOne->clear();
    lineEditScoreTwo->clear();
    hide();
    accept();
}

QString MatchAddDialog::getNameOneString() {
    return teamOneText;
}

QString MatchAddDialog::getNameTwoString() {
    return teamTwoText;
}

int MatchAddDialog::getScoreOne() {
    return score_one;
}

int MatchAddDialog::getScoreTwo() {
    return score_two;
}
