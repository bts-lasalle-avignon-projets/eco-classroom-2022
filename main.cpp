#include "salle.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Salle w;
    w.show();
    return a.exec();
}
