#ifndef TEAM_H
#define TEAM_H

#include <QString>

class Team
{
private:
    int score;                          // Очков
    int win_count;                      // Победы
    int lose_count;                     // Поражения
    int draw_count;                     // Ничья
    int goals_scored;                   // Забито мячей
    int goals_conceded;                 // Пропущенно мячей
    QString title;
public:
    Team();                             // Создание
    Team(QString t);                    // Создание с названием
    Team(const Team &obj);              // Копирование
    ~Team();                            // Удаление

    QString get_name();                 // ПОЛУЧИТЬ:: Узнать имя команды
    int get_score();                    // ПОЛУЧИТЬ:: Количество очков
    int get_count_wins();               // ПОЛУЧИТЬ:: Количество побед
    int get_count_lose();               // ПОЛУЧИТЬ:: Количество поражений
    int get_count_draw();               // ПОЛУЧИТЬ:: Количество ничей
    int get_goals_scored();             // ПОЛУЧИТЬ:: Забито голов
    int get_goals_conceded();           // ПОЛУЧИТЬ:: Пропущено голов

    void set_name(QString name);        // УСТАНОВИТЬ:: Новое имя команды
    void set_score(int count);          // УСТАНОВИТЬ:: Количество очков
    void set_count_wins(int count);     // УСТАНОВИТЬ:: Количество побед
    void set_count_lose(int count);     // УСТАНОВИТЬ:: Количество поражений
    void set_count_draw(int count);     // УСТАНОВИТЬ:: Количество ничей
    void set_goals_scored(int count);   // УСТАНОВИТЬ:: Забито голов
    void set_goals_conceded(int count); // УСТАНОВИТЬ:: Пропущено голов

    Team& operator=(const Team &t);     // Скопировать объект класса
};

#endif // TEAM_H
