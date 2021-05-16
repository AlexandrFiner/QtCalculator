#include <QString>
#include <QVector>
#include "match.h"

QVector<Match> matches;

Match::Match()
{
    team_1 = "";
    team_2 = "";
    score_1 = 0;
    score_2 = 0;
}

int Match::get_score_team_one() {
    return score_1;
}

int Match::get_score_team_two() {
    return score_2;
}

int Match::get_win_team() {
    if(score_1 > score_2) return 1;
    else if(score_1 < score_2) return 2;
    else return 0;
}

QString Match::get_first_team() {
    return team_1;
}

QString Match::get_second_team() {
    return team_2;
}

void Match::set_score_team_one(int score) {
    score_1 = score;
}

void Match::set_score_team_two(int score) {
    score_2 = score;
}

void Match::set_first_team(QString team) {
    team_1 = team;
}

void Match::set_second_team(QString team) {
        team_2 = team;
    }

Match& Match::operator=(const Match &t) {
    if (&t == this) {
        // На самом деле проверка не особо нужна, но иногда пригодится
        return *this;
    }
    team_1 = t.team_1;
    team_2 = t.team_2;
    score_1 = t.score_1;
    score_2 = t.score_2;
    return *this;
}
