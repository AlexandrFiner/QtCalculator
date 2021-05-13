#include <QtGui>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QHeaderView>
#include <QMenuBar>
#include "menu.h"

const int WIN_SCORE = 3;
const int DRAW_SCORE = 1;
const int LOSE_SCORE = 0;


struct less_than_key
{
    inline bool operator() (Team&struct1, Team&struct2)
    {
        return (struct1.get_score() > struct2.get_score());
    }
};

MainMenu::MainMenu(QWidget *parent): QWidget(parent)
{
    isSaved = true;
    this->resize(889, 500);
    this->setObjectName("MainWidget");
    addButtonTeam = new QPushButton(tr("&Добавить команду"));
    addButtonMatch = new QPushButton(tr("&Добавить матч"));
    exportButton = new QPushButton(tr("&Экспортировать"));
    saveButton = new QPushButton(tr("&Сохранить"));
    loadButton = new QPushButton(tr("&Открыть файл"));
    undoButton = new QPushButton(tr("&Отмена"));

    dialogAddTeam = new TeamDialog;
    dialogAddMatch = new MatchAddDialog;

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(8);
    tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Команда"));
    tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Набрано очков"));
    tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Побед"));
    tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Поражений"));
    tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Ничей"));
    tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("Забито"));
    tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("Пропущено"));
    tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("Действия"));
    tableWidget->setVisible(true);
    tableWidget->setEditTriggers(0);
    tableWidget->horizontalHeader()->setSectionsClickable(true);
    tableWidget->setSortingEnabled(true);
    tableWidget->sortByColumn(1, Qt::DescendingOrder);

    tableWidgetMatches = new QTableWidget(this);
    tableWidgetMatches->setColumnCount(5);
    tableWidgetMatches->setHorizontalHeaderItem(0, new QTableWidgetItem("Команда"));
    tableWidgetMatches->setHorizontalHeaderItem(1, new QTableWidgetItem("Забито"));
    tableWidgetMatches->setHorizontalHeaderItem(2, new QTableWidgetItem("Команда"));
    tableWidgetMatches->setHorizontalHeaderItem(3, new QTableWidgetItem("Забито"));
    tableWidgetMatches->setHorizontalHeaderItem(4, new QTableWidgetItem("Действия"));
    tableWidgetMatches->setVisible(false);
    tableWidgetMatches->setEditTriggers(0);

    QTabBar *bar = new QTabBar(this);
    bar->addTab("Команды");
    bar->addTab("Матчи");

    /* Это первый запуск */
    undoButton->setDisabled(true);

    // Поработаем
    connect(addButtonTeam, SIGNAL(clicked()), this, SLOT(showAddTeam()));
    connect(addButtonMatch, SIGNAL(clicked()), this, SLOT(showAddMatch()));
    connect(exportButton, SIGNAL(clicked()), this, SLOT(showExportFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(showSaveFile()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(showLoadFile()));
    connect(undoButton, SIGNAL(clicked()), this, SLOT(undo()));
    connect(bar, &QTabBar::currentChanged, [=] (int index) {
        switch (index) {
            case 0: {
                tableWidget->setVisible(true);
                tableWidgetMatches->setVisible(false);
                break;
            }
            case 1: {
                tableWidget->setVisible(false);
                tableWidgetMatches->setVisible(true);
                break;
            }
        }
    });

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(addButtonTeam);
    buttonLayout->addWidget(addButtonMatch);
    buttonLayout->addStretch();
    buttonLayout->addWidget(exportButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(loadButton);
    buttonLayout->addWidget(undoButton);

    QVBoxLayout *tableLayout = new QVBoxLayout;
    tableLayout->addWidget(bar);
    tableLayout->addWidget(tableWidget);
    tableLayout->addWidget(tableWidgetMatches);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addLayout(buttonLayout, 1, 1);
    mainLayout->addLayout(tableLayout, 1, 2);
    setLayout(mainLayout);
    setWindowTitle(tr("Калькулятор турнирной таблицы"));
}

/*
 * Функции
*/
void MainMenu::updateWidgetTeams() {
    tableWidget->setRowCount(0);
    int row = 0;


    // Изменить название

    // qSort(teams.begin(), teams.end(), sort_team);
    tableWidget->setSortingEnabled(false);
    for(auto team:teams) {
        tableWidget->insertRow(row);


        tableWidget->setItem(row, 0, new QTableWidgetItem(tr("%1").arg(team.get_name())));            // Название
        tableWidget->setItem(row, 1, new QTableWidgetItem(tr("%1").arg(team.get_score())));           // Очкрв
        tableWidget->setItem(row, 2, new QTableWidgetItem(tr("%1").arg(team.get_count_wins())));      // Побед
        tableWidget->setItem(row, 3, new QTableWidgetItem(tr("%1").arg(team.get_count_lose())));      // Поражений
        tableWidget->setItem(row, 4, new QTableWidgetItem(tr("%1").arg(team.get_count_draw())));      // Ничей
        tableWidget->setItem(row, 5, new QTableWidgetItem(tr("%1").arg(team.get_goals_scored())));    // Забито
        tableWidget->setItem(row, 6, new QTableWidgetItem(tr("%1").arg(team.get_goals_conceded())));  // Пропущно

        // Кнопка
        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("Delete");
        connect(btn_edit, &QPushButton::clicked, [=]() {
            // Лень делать функцию, так тоже норм
            int pos = row;
            Team team;
            team = teams[row];

            undoButton->setDisabled(false);
            undoTeams = teams;
            undoMatches = matches;

            QMessageBox::information(this, tr("Success"), tr("\"%1\" удалена из списка команд.").arg(team.get_name()));
            for(auto i = matches.begin(); i < matches.end();) {
                if(i->get_first_team() == team.get_name()) {
                    int teamId = teamExists(i->get_second_team());
                    Team team;
                    team = teams[teamId];
                    switch (i->get_win_team()) {
                        case 0: {
                            // Ничья
                            team.set_count_draw(team.get_count_draw()-1);
                            team.set_score(team.get_score()-DRAW_SCORE);
                            break;
                        }
                        case 1: {
                            // Вторая тима проиграла
                            team.set_count_lose(team.get_count_lose()-1);
                            team.set_score(team.get_score()-LOSE_SCORE);
                            break;
                        }
                        case 2: {
                            // Первая команда проиграла
                            team.set_count_wins(team.get_count_wins()-1);
                            team.set_score(team.get_score()-WIN_SCORE);
                            break;
                        }
                    }
                    team.set_goals_conceded(team.get_goals_conceded()-i->get_score_team_one());
                    team.set_goals_scored(team.get_goals_scored()-i->get_score_team_two());
                    teams[teamId] = team;
                    i = matches.erase(i);
                    continue;
                } else if(i->get_second_team() == team.get_name()) {
                    int teamId = teamExists(i->get_first_team());
                    Team team;
                    team = teams[teamId];
                    switch (i->get_win_team()) {
                        case 0: {
                            // Ничья
                            team.set_count_draw(team.get_count_draw()-1);
                            team.set_score(team.get_score()-DRAW_SCORE);
                            break;
                        }
                        case 1: {
                            // Первая команда выиграла
                            team.set_count_wins(team.get_count_wins()-1);
                            team.set_score(team.get_score()-WIN_SCORE);
                            break;
                        }
                        case 2: {
                            // Вторая тима выиграла
                            team.set_count_lose(team.get_count_lose()-1);
                            team.set_score(team.get_score()-LOSE_SCORE);
                            break;
                        }
                    }
                    team.set_goals_conceded(team.get_goals_conceded()-i->get_score_team_two());
                    team.set_goals_scored(team.get_goals_scored()-i->get_score_team_one());
                    teams[teamId] = team;
                    i = matches.erase(i);
                    continue;
                } else {
                    i++;
                }
            }
            teams.erase(teams.begin() + pos);
            updateWidgetTeams();
            updateWidgetMatches();
        });
        tableWidget->setCellWidget(row, 7, btn_edit);

        row++;
    }
    tableWidget->setSortingEnabled(true);
    tableWidget->sortByColumn(1, Qt::DescendingOrder);
}

void MainMenu::updateWidgetMatches() {
    tableWidgetMatches->setRowCount(0);

    QIcon icon(":/files/winer.png");
    int row = 0;
    for(auto match:matches) {
        tableWidgetMatches->insertRow(row);

        if(match.get_win_team() == 1) {
            tableWidgetMatches->setItem(row, 0, new QTableWidgetItem(icon, tr("%1").arg(match.get_first_team())));
            tableWidgetMatches->setItem(row, 2, new QTableWidgetItem(tr("%1").arg(match.get_second_team())));
        } else if(match.get_win_team() == 2) {
            tableWidgetMatches->setItem(row, 0, new QTableWidgetItem(tr("%1").arg(match.get_first_team())));
            tableWidgetMatches->setItem(row, 2, new QTableWidgetItem(icon, tr("%1").arg(match.get_second_team())));
        } else {
            tableWidgetMatches->setItem(row, 0, new QTableWidgetItem(tr("%1").arg(match.get_first_team())));
            tableWidgetMatches->setItem(row, 2, new QTableWidgetItem(tr("%1").arg(match.get_second_team())));
        }
        tableWidgetMatches->setItem(row, 1, new QTableWidgetItem(tr("%1").arg(match.get_score_team_one())));      // Забито
        tableWidgetMatches->setItem(row, 3, new QTableWidgetItem(tr("%1").arg(match.get_score_team_two())));      // Забито


        QPushButton* btn_edit = new QPushButton();
        btn_edit->setText("Delete");
        connect(btn_edit, &QPushButton::clicked, [=]() {
            // Лень делать функцию, так тоже норм
            int pos = row;
            Match match;
            match = matches[row];

            undoButton->setDisabled(false);
            undoTeams = teams;
            undoMatches = matches;

            QMessageBox::information(this, tr("Success"), tr("Матч \"%1\" vs \"%2\" удален.").arg(match.get_first_team()).arg(match.get_second_team()));

            /// TODO:: Удаление
            Team teamOne;
            Team teamTwo;
            int teamIdOne; // = teamExists(key_first);
            int teamIdTwo; // = teamExists(key_second);
            teamIdOne = teamExists(match.get_first_team());
            teamIdTwo = teamExists(match.get_second_team());

            teamOne = teams[teamIdOne];
            teamTwo = teams[teamIdTwo];

            switch (match.get_win_team()) {
                case 0: {
                    // Ничья
                    teamOne.set_count_draw(teamOne.get_count_draw()-1);
                    teamTwo.set_count_draw(teamTwo.get_count_draw()-1);

                    teamOne.set_score(teamOne.get_score()-DRAW_SCORE);
                    teamTwo.set_score(teamTwo.get_score()-DRAW_SCORE);
                    break;
                }
                case 1: {
                    // Первая команда выиграла
                    teamOne.set_count_wins(teamOne.get_count_wins()-1);
                    teamTwo.set_count_lose(teamTwo.get_count_lose()-1);

                    teamOne.set_score(teamOne.get_score()-WIN_SCORE);
                    teamTwo.set_score(teamTwo.get_score()-LOSE_SCORE);
                    break;
                }
                case 2: {
                    teamOne.set_count_lose(teamOne.get_count_lose()-1);
                    teamTwo.set_count_wins(teamTwo.get_count_wins()-1);

                    teamOne.set_score(teamOne.get_score()-LOSE_SCORE);
                    teamTwo.set_score(teamTwo.get_score()-WIN_SCORE);
                    break;
                }
            }
            teamOne.set_goals_conceded(teamOne.get_goals_conceded()-match.get_score_team_two());
            teamTwo.set_goals_conceded(teamTwo.get_goals_conceded()-match.get_score_team_one());
            teamOne.set_goals_scored(teamOne.get_goals_scored()-match.get_score_team_one());
            teamTwo.set_goals_scored(teamTwo.get_goals_scored()-match.get_score_team_two());

            teams[teamIdOne] = teamOne;
            teams[teamIdTwo] = teamTwo;

            matches.erase(matches.begin() + pos);
            updateWidgetTeams();
            updateWidgetMatches();
        });
        tableWidgetMatches->setCellWidget(row, 4, btn_edit);

        row++;
    }
}

// Функция для показа добавления команды
void MainMenu::showAddTeam() {
    dialogAddTeam->show();
    this->setDisabled(true);
    if(dialogAddTeam->exec()) {
        this->setDisabled(false);
        QString teamName = dialogAddTeam->getNameString();
        teamName = teamName.trimmed();
        if(teamExists(teamName) == -1) {
            undoTeams = teams;
            undoMatches = matches;

            Team t(teamName);
            teams.push_back(t);
            updateWidgetTeams();
            QMessageBox::information(this, tr("Success"), tr("\"%1\" добавлена в список команд.").arg(teamName));
            undoButton->setDisabled(false);
            isSaved = false;
        } else {
            QMessageBox::warning(this, tr("Alredy exists"), tr("Ошибка, \"%1\" уже есть в списке команд.").arg(teamName));
            return;
        }
    } else
        this->setDisabled(false);
}

// Функция для добавления матча
void MainMenu::showAddMatch() {
    dialogAddMatch->show();
    this->setDisabled(true);
    if(dialogAddMatch->exec()) {
        this->setDisabled(false);
        QString teamNameOne = dialogAddMatch->getNameOneString();
        QString teamNameTwo = dialogAddMatch->getNameTwoString();

        if(teamNameOne == teamNameTwo) {
            QMessageBox::warning(this, tr("Alredy exists"), tr("Команда \"%1\" играет против себя же.").arg(teamNameOne));
            return;
        }

        int goals_scored_one = dialogAddMatch->getScoreOne();
        int goals_scored_two = dialogAddMatch->getScoreTwo();

        if(goals_scored_one < 0 || goals_scored_two < 0) {
            QMessageBox::warning(this, tr("Wrong score"), tr("Количество забитых голов должно быть больше или равно нуля").arg(teamNameOne));
            return;
        }

        undoButton->setDisabled(false);
        undoTeams = teams;
        undoMatches = matches;

        int winTeam = 0;
        if(goals_scored_one > goals_scored_two)         winTeam = 1;
        else if(goals_scored_one < goals_scored_two)    winTeam = 2;
        else winTeam = 0;

        int teamIdOne = teamExists(teamNameOne);
        int teamIdTwo = teamExists(teamNameTwo);

        Match match;
        match.set_first_team(teamNameOne);
        match.set_second_team(teamNameTwo);
        match.set_score_team_one(goals_scored_one);
        match.set_score_team_two(goals_scored_two);

        ////////// QMessageBox::information(this, tr("Alredy exists"), tr("Команда \"%1\" \"%2\".").arg(teamNameOne).arg(teamNameTwo));

        /// КОМАНДА 1
        Team team(teamNameOne);
        if(teamIdOne != -1) {
            // СДЕЛАТЬ КОПИРОВАНИЕ
            team = teams[teamIdOne];
        }
        if(winTeam == 1) {
            team.set_count_wins(team.get_count_wins()+1);
            team.set_score(team.get_score()+WIN_SCORE);
        }
        if(winTeam == 2) {
            team.set_count_lose(team.get_count_lose()+1);
            team.set_score(team.get_score()+LOSE_SCORE);
        }
        if(winTeam == 0) {
            team.set_count_draw(team.get_count_draw()+1);
            team.set_score(team.get_score()+DRAW_SCORE);
        }
        team.set_goals_scored(team.get_goals_scored()+goals_scored_one);
        team.set_goals_conceded(team.get_goals_conceded()+goals_scored_two);
        if(teamIdOne != -1) {
            // Команды уже есть
            teams[teamIdOne] = team;
        } else {
            teams.push_back(team);
        }
        /// КОМАНДА 2
        Team teamTwo(teamNameTwo);
        if(teamIdTwo != -1) {
            // СДЕЛАТЬ КОПИРОВАНИЕ
            teamTwo = teams[teamIdTwo];
        }
        if(winTeam == 2) {
            teamTwo.set_count_wins(teamTwo.get_count_wins()+1);
            teamTwo.set_score(teamTwo.get_score()+WIN_SCORE);
        }
        if(winTeam == 1) {
            teamTwo.set_count_lose(teamTwo.get_count_lose()+1);
            teamTwo.set_score(teamTwo.get_score()+LOSE_SCORE);
        }
        if(winTeam == 0) {
            teamTwo.set_count_draw(teamTwo.get_count_draw()+1);
            teamTwo.set_score(teamTwo.get_score()+DRAW_SCORE);
        }
        teamTwo.set_goals_scored(teamTwo.get_goals_scored()+goals_scored_two);
        teamTwo.set_goals_conceded(teamTwo.get_goals_conceded()+goals_scored_one);
        if(teamIdTwo != -1) {
            // Команды уже есть
            teams[teamIdTwo] = teamTwo;
        } else {
            teams.push_back(teamTwo);
        }
        matches.push_front(match);
        updateWidgetMatches();
        updateWidgetTeams();

        isSaved = false;
        QMessageBox::information(this, tr("Success"), tr("Матч успешно добавлен."));
        // Добавление матча
    } else
        this->setDisabled(false);
}

void MainMenu::showExportFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранение турнирной таблицы"), "",
        tr("CSV (*.csv);;All Files (*)"));

    if(fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }


        // Поток выхода
        QTextStream out(&file);
        out << "Team name, Score, Wins, Lose, Draw, Goals scored, Goals conceded\n";


        qSort(teams.begin(), teams.end(), less_than_key());
        for(auto i = teams.begin(); i < teams.end();) {
            out << i->get_name() << ", ";
            out << i->get_score() << ", ";
            out << i->get_count_wins() << ", ";
            out << i->get_count_lose() << ", ";
            out << i->get_count_draw() << ", ";
            out << i->get_goals_scored() << ", ";
            out << i->get_goals_conceded() << "\n";
            i++;
        }
        out << "Team name, Score, Wins, Lose, Draw, Goals scored, Goals conceded\n";
        QMessageBox::information(this, tr("Success"), tr("Успешный экспорт."));
    }
}

void MainMenu::showSaveFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Сохранение турнирной таблицы"), "",
        tr("Tournament table (*.tourt);;All Files (*)"));

    if(fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        // Поток выхода
        QTextStream out(&file);

        out << "{teams_save_start}\n";
        for(auto i = teams.begin(); i < teams.end();) {
            out << i->get_name() << "\n";
            out << i->get_score() << "\n";
            out << i->get_count_wins() << "\n";
            out << i->get_count_lose() << "\n";
            out << i->get_count_draw() << "\n";
            out << i->get_goals_scored() << "\n";
            out << i->get_goals_conceded() << "\n";
            i++;
        }
        out << "{matches_save_start}\n";
        for(auto i = matches.begin(); i < matches.end();) {
            out << i->get_first_team() << "\n";
            out << i->get_second_team() << "\n";
            out << i->get_score_team_one() << "\n";
            out << i->get_score_team_two() << "\n";
            i++;
        }

        isSaved = true;
        QMessageBox::information(this, tr("Success"), tr("Файл сохранен."));
    }
}

void MainMenu::showLoadFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Открытие турнирной таблицы"), "",
        tr("Tournament table (*.tourt);;All Files (*)"));

    if (fileName.isEmpty())
            return;
    else {
        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly|QIODevice::Text)) {
            QMessageBox::information(this, tr("Unable to open file"),
                file.errorString());
            return;
        }

        // Поток входа
        QTextStream in(&file);

        undoTeams = teams;
        undoMatches = matches;
        teams.clear();
        matches.clear();

        int mode = -1;
        int param = 0;

        Team team;
        Match match;
        while(!in.atEnd()) {
            QString line = in.readLine(); // Прочитаем строчку
            line = line.trimmed();
            if(!line.length() || line == EOF)
                continue;

            if(line == "{teams_save_start}") {
                mode = 1;
                param = 0;
            } else if(line == "{matches_save_start}") {
                mode = 2;
                param = 0;
            } else {
                if(mode == 1) {
                    // Читаем команды
                    if(param == 0) team.set_name(line);
                    if(param == 1) team.set_score(line.toInt());
                    if(param == 2) team.set_count_wins(line.toInt());
                    if(param == 3) team.set_count_lose(line.toInt());
                    if(param == 4) team.set_count_draw(line.toInt());
                    if(param == 5) team.set_goals_scored(line.toInt());
                    if(param == 6) {
                        team.set_goals_conceded(line.toInt());
                        teams.push_back(team); param = -1;
                    }
                    param++;
                }
                if(mode == 2) {
                    if(param == 0) match.set_first_team(line);
                    if(param == 1) match.set_second_team(line);
                    if(param == 2) match.set_score_team_one(line.toInt());
                    if(param == 3) {
                        match.set_score_team_two(line.toInt());
                        matches.push_back(match); param = -1;
                    }
                    param++;
                }
            }
        }

        // in >> teams;
        isSaved = true;
        QMessageBox::information(this, tr("Success"), tr("Файл открыт."));
        updateWidgetMatches();
        updateWidgetTeams();
    }
}

void MainMenu::undo() {
    QMessageBox::information(this, tr("Success"), tr("Отмена произошла успешно."));

    teams = undoTeams;
    matches = undoMatches;
    undoButton->setDisabled(true);
    updateWidgetMatches();
    updateWidgetTeams();
}

void MainMenu::closeEvent(QCloseEvent *event) {
    if(isSaved)
        return event->accept();

    event->ignore();
    if (QMessageBox::Yes == QMessageBox::question(this, "Close Confirmation", "У вас остались несохраненные данные. Вы действительно хотите выйти?", QMessageBox::Yes | QMessageBox::Cancel))
    {
        event->accept();
    }
}

// Существует ли команда, если да, то вернем ее индентификатор
int MainMenu::teamExists(QString key) {
    int elem = -1;
    for(auto i = teams.begin(); i < teams.end();) {
        elem++;
        if (i->get_name() == key) {
            return elem;
        }
        i++;
    }
    return -1;
}
