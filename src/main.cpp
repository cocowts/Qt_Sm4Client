#include "mainwindow.h"
#include <QApplication>

#include <QPixmap>
#include <QSplashScreen>
#include <QElapsedTimer>

static void setStyle(const QString &styleName)
{
    QFile file(QString(":/qss/qss/%1.qss").arg(styleName));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    qApp->setStyleSheet(qss);
    qApp->setPalette(QPalette(QColor("#F0F0F0")));
}

static void startSplashScreen(QString path, quint16 timems)
{
    QPixmap pixmap(path);
    QSplashScreen splash(pixmap);
    splash.show();

    QElapsedTimer t;
    t.start();
    while(t.elapsed()<timems);

    splash.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    setStyle("white");
    startSplashScreen(":/pic/pic/logo.png", 1500);

    MainWindow w;
    w.show();

    return a.exec();
}
