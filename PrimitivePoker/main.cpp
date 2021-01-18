#include <QtGui/QApplication>
#include "MainApplication.h"
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(NULL));
    MainApplication w;
    w.show();

    return a.exec();
}
