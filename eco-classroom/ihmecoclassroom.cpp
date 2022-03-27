#include "ihmecoclassroom.h"
#include "ui_ihmecoclassroom.h"
#include "salle.h"
#include <QDebug>

/**
 * @file ihmecoclassroom.cpp
 * @brief Définition de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe IHMEcoClassroom
 *
 * @fn IHMEcoClassroom::IHMEcoClassroom
 * @param parent L'adresse de l'objet parent, si nullptr IHMEcoClassroom sera la
 * fenêtre principale de l'application
 */
IHMEcoClassroom::IHMEcoClassroom(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMEcoClassroom)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
    ajouterMenuAide();
    ui->statusbar->showMessage(QString::fromUtf8(NOM) + " " +
                               QString::fromUtf8(VERSION));

    initialiserAffichage();
}

/**
 * @brief Destructeur de la classe IHMEcoClassroom
 *
 * @fn IHMEcoClassroom::~IHMEcoClassroom
 * @details Libère les ressources de l'application
 */
IHMEcoClassroom::~IHMEcoClassroom()
{
    delete ui;
    qDebug() << Q_FUNC_INFO;
}

void IHMEcoClassroom::initialiserAffichage()
{
    qDebug() << Q_FUNC_INFO;
    ui->statusbar->showMessage(QString::fromUtf8(NOM) + " " +
                               QString::fromUtf8(VERSION));
    // Initialise le QTableView
    nomColonnes << "Nom"
                << "Description"
                << "Indice de confort"
                << "Fenétres"
                << "Lumières";
    modeleSalle = new QStandardItemModel(0, nomColonnes.size());
    modeleSalle->setHorizontalHeaderLabels(nomColonnes);

    tableViewSalles->setModel(modeleSalle);
    tableViewSalles->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Redimensionner automatiquement la colonne pour occuper l'espace
    // disponible
    tableViewSalles->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
    nbLignesSalle = modeleSalle->rowCount();
}

void IHMEcoClassroom::ajouterMenuAide()
{
    QMenu* menuAide = new QMenu(QString::fromUtf8("&Aide"), this);
    menuBar()->addMenu(menuAide);

    menuAide->addAction(QString::fromUtf8("À propos ") + QString::fromUtf8(NOM),
                        this,
                        SLOT(afficherAPropos()));
    menuAide->addAction(QString::fromUtf8("À propos de Qt"),
                        qApp,
                        SLOT(aboutQt()));
}

void IHMEcoClassroom::afficherAPropos()
{
    QMessageBox::about(this,
                       QString::fromUtf8("À propos ..."),
                       QString::fromUtf8("<p><b>") + QString::fromUtf8(NOM) +
                         " " + QString::fromUtf8(VERSION) +
                         QString::fromUtf8("</b><br/>...</p>"));
}
