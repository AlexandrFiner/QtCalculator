#include <QtGui>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include "teamdialog.h"

TeamDialog::TeamDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setObjectName("MainWidget");
    setWindowFlag(Qt::WindowStaysOnTopHint);    // Чтоб всегда было выше

    QLabel *addLabel = new QLabel(tr("Введите название команды:"));
    lineEdit = new QLineEdit;
    lineEdit->setAttribute(Qt::WA_MacShowFocusRect, 0); // Убрать обводку

    addButton = new QPushButton(tr("&Добавить"));
    teamText = "";

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(addLabel, 1, 1);
    layout->addWidget(lineEdit, 2, 1);
    layout->addWidget(addButton, 3, 1);

    setLayout(layout);
    setWindowTitle(tr("Добавить команду"));
    connect(addButton, SIGNAL(clicked()), this, SLOT(findClicked()));
}

void TeamDialog::findClicked() {
    QString text = lineEdit->text();
    text = text.trimmed();
    if(text.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"), tr("Вы не ввели название."));
        return;
    }

    teamText = text;
    lineEdit->clear();
    hide();
    accept();
}

QString TeamDialog::getNameString() {
    return teamText;
}
