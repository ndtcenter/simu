#include "simumw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CSimuMW w;
    w.show();

    return a.exec();
}
