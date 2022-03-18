#include "ihmecoclassroom.h"
#include <QApplication>

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application eco-classroom
 * @author Zeryouhi Mohamed Amine
 * @version 1.0
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */
int main(int argc, char* argv[])
{
    QApplication    a(argc, argv);
    IHMEcoClassroom w;

    // w.showFullScreen();
    w.show();

    return a.exec();
}
