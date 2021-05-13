 #ifndef MENU_H
 #define MENU_H

 #include <QWidget>
 #include <QMap>
 #include <QVector>
 #include <QCloseEvent>


// Окна
 #include "teamdialog.h"
 #include "matchadddialog.h"

// Классы
 #include "team.h"
 #include "match.h"

 class QPushButton;
 class QLabel;
 class QLineEdit;
 class QTextEdit;

 class MainMenu : public QWidget
 {
     Q_OBJECT

 public:
     MainMenu(QWidget *parent = 0); // Создаем окно
     void updateWidgetTeams();
     void updateWidgetMatches();

 public slots:
     void showAddTeam();                 // Функция:: Показать добавление команды
     void showAddMatch();                // Функция:: Показать добавление матча
     void showExportFile();              // Функция:: Экспортировать в CSV
     void showSaveFile();                // Функция:: Сохранить в файл
     void showLoadFile();                // Функция:: Считать из файла
     void undo();                        // Функция:: отмена последнего действия

     void closeEvent(QCloseEvent *event);// Отлавливаем закрытие окна

     int teamExists(QString key);        // Функция:: Есть ли такая команда

 private:
     QPushButton *addButtonTeam;         // Добавить команду
     QPushButton *addButtonMatch;        // Добавить матч
     QPushButton *exportButton;          // Экспортировать
     QPushButton *saveButton;            // Сохранить
     QPushButton *loadButton;            // Открыть файл
     QPushButton *undoButton;            // Показать список матчей

     TeamDialog *dialogAddTeam;          // Окно:: Добавление команды
     MatchAddDialog *dialogAddMatch;     // Окно:: Добавление матча

     QVector<Team> teams;                // Команды
     QVector<Match> matches;             // Матчи
     QVector<Team> undoTeams;            // Для отмены:: команды
     QVector<Match> undoMatches;         // Для отмены:: матчи

     QTableWidget *tableWidget;          // Виджет таблицы команд
     QTableWidget *tableWidgetMatches;   // Виджет таблицы матчей

     bool isSaved = true;                // Сохранены ли данные?
 };

 #endif
