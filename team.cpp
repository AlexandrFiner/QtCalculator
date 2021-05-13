#include <QVector>
#include "team.h"

Team::Team() {
    title = "undefined";
    score = 0;
    win_count = 0;
    lose_count = 0;
    draw_count = 0;
    goals_scored = 0;
    goals_conceded = 0;
}

Team::Team(QString t) { // Может быть использовано
    title = t;
    score = 0;
    win_count = 0;
    lose_count = 0;
    draw_count = 0;
    goals_scored = 0;
    goals_conceded = 0;
}

Team::Team(const Team &obj) {
    title = obj.title; // Копируем название команды
    score = obj.score;
    win_count = obj.win_count;
    lose_count = obj.lose_count;
    draw_count = obj.draw_count;
    goals_scored = obj.goals_scored;
    goals_conceded = obj.goals_conceded;
}

Team::~Team() {}

QString Team::get_name() {
    return title;
}

int Team::get_score() {
    return score;
}

int Team::get_count_wins() {
    return win_count;
}

int Team::get_count_lose() {
    return lose_count;
}

int Team::get_count_draw() {
    return draw_count;
}

int Team::get_goals_scored() {
    return goals_scored;
}

int Team::get_goals_conceded() {
    return goals_conceded;
}

/**** FUNC *****/
void Team::set_name(QString name) {
    title = name;
}

void Team::set_score(int count) {
    score = count;
}

void Team::set_count_wins(int count) {
    win_count = count;
}

void Team::set_count_lose(int count) {
    lose_count = count;
}

void Team::set_count_draw(int count) {
    draw_count = count;
}

void Team::set_goals_scored(int count) {
    goals_scored = count;
}

void Team::set_goals_conceded(int count) {
    goals_conceded = count;
}

Team& Team::operator=(const Team &t) {
    if (&t == this) {
        // На самом деле проверка не особо нужна, но иногда пригодится
        return *this;
    }
    title = t.title; // Копируем название команды
    score = t.score;
    win_count = t.win_count;
    lose_count = t.lose_count;
    draw_count = t.draw_count;
    goals_scored = t.goals_scored;
    goals_conceded = t.goals_conceded;
    return *this;
}
