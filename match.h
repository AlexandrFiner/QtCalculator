#ifndef MATCH_H
#define MATCH_H

#include <QString>

class Match
{
private:
    QString team_1;
    QString team_2;
    int score_1;
    int score_2;
public:
    Match();                                // Создаем
    int get_score_team_one();               // Очки первой команды
    int get_score_team_two();               // Очки второй команды

    int get_win_team();                     // Кто выиграл ( 0 - ничья / 1 - первая / 2 - вторая )

    QString get_first_team();               // Имя первой команды
    QString get_second_team();              // Имя второй команды

    void set_score_team_one(int score);     // Очки первой команды
    void set_score_team_two(int score);     // Очки второй команды

    void set_first_team(QString team);      // Установить название первой команды
    void set_second_team(QString team);     // Установить название второй команды

    Match& operator=(const Match &t);       // Скопировать объект класса
};

#endif // MATCH_H
