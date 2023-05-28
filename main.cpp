#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    a.setAttribute(Qt::ScrollBarAlwaysOff);
    MainWindow w;

    w.showFullScreen();
    return a.exec();
}