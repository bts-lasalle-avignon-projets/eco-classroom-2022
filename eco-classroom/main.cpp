#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include "ihmecoclassroom.h"

/**
 * @file main.cpp
 * @brief Programme principal
 * @details Crée et affiche la fenêtre principale de l'application eco-classroom
 * @author Zeryouhi Mohamed Amine
 * @version 1.1
 *
 * @param argc
 * @param argv[]
 * @return int
 *
 */
int main(int argc, char* argv[])
{
    QApplication    a(argc, argv);
    QString         locale = QLocale::system().name().section('_', 0, 0);
    QTranslator     translator;
    IHMEcoClassroom w;

    // ajoute le support du français pour les boîtes de dialogue
    translator.load(QString("qt_") + locale,
                    QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&translator);

    // w.showFullScreen();
    w.show();

    return a.exec();
}
