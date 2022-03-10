#include "ihmclassroom.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IhmClassroom w;
    w.show();
    return a.exec();
}
