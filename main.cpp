#include "MainWindow.h"

#include <QApplication>
//#include "AI/AI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
//        AI ai = AI();
//        ai.readfromFile("output.txt", ai.data);
//        ai.teachAI();
//        ai.testAI("test.txt");
}
