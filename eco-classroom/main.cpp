#include "ihmecoclassroom.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication    a(argc, argv);
    IHMEcoClassroom w;

    // w.showFullScreen();
    w.show();

    return a.exec();
}
