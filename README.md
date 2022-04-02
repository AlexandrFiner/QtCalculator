# QtCalculator

Была поставлена задача - разработать калькулятор турнирной таблицы. Стандартная сортировка - по количеству набранных очков. Экспорт в таблицу *.csv только со сортировкой по очкам.

# Видео демонстрация
[![Демонстрация](https://i.ytimg.com/vi/5XL6KyEjlBo/maxresdefault.jpg)](https://www.youtube.com/watch?v=5XL6KyEjlBo)
Для просмотра нажмите на превью выше

# Что использовалось
Для разработки использовалась IDE [Qt](https://www.qt.io/) и классы, определенные в данной библиотеке.

# Константы
```cpp
// menu.cpp
const int WIN_SCORE = 3;        // Количество очков за победу
const int DRAW_SCORE = 1;       // Количество очков за ничью
const int LOSE_SCORE = 0;       // Количество очков за поражение
```

# Классы
## Класс команд
```cpp
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
```

## Класс матчей
```cpp
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
```

# Демонстрация работы программы
![](https://i.ibb.co/VmLgS5V/2021-05-16-15-09-25.png)
> Загрузочное окно (splashscreen)

![](https://i.ibb.co/KxQ7jMZ/2021-05-16-15-09-40.png)
> Главное окно программы

![](https://i.ibb.co/kX2QZVq/2021-05-16-15-09-52.png)
> Окно добавления команды

![](https://i.ibb.co/Jtd9Hv9/2021-05-16-15-10-01.png)
> Окно добавления матча

![](https://i.ibb.co/F8rTk85/2021-05-16-15-10-49.png)
> Главное окно. Турнирная таблица с заполненными данными

![](https://i.ibb.co/chBWzsV/2021-05-16-15-10-59.png)
> Главное окно. Таблица с историей матчей от новых к старым

![](https://i.ibb.co/q5M1b2j/2021-05-16-15-11-47.png)
> Экспортированная турнирная таблица в формате CSV. Сортировка по колчеству очков

# UML диаграмма
![](https://i.ibb.co/KhdcSRy/2021-05-16-15-11-17.png)

# Credits
[doc.crossplatform.ru](http://doc.crossplatform.ru/qt/4.4.3/tutorials-addressbook-part1.html)
