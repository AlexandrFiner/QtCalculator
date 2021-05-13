#include <menu.h>
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QFile>
#include <QTextCodec>

static const int LOAD_TIME_MSEC = 1 * 1000;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile fileStyle(":/qss/style.qss");
    fileStyle.open(QFile::ReadOnly);
    app.setStyleSheet(fileStyle.readAll());
    MainMenu menu;
    QPixmap pix( ":/files/splash_mini.png" );                   // Картинка
    QSplashScreen splashScreen(pix, Qt::WindowStaysOnTopHint);  // Сплеш скрин (aka загрузка)
    splashScreen.show();                                        // Показываем
    app.processEvents();
    QTimer::singleShot(LOAD_TIME_MSEC, &splashScreen, &QWidget::close);
    QTimer::singleShot(LOAD_TIME_MSEC, &menu, &QWidget::show);
    return app.exec();
}
