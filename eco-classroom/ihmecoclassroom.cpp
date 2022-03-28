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
    QMainWindow(parent), ui(new Ui::IHMEcoClassroom), nbLignesSalle(0)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
    ajouterMenuAide();
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

    // Initialise le QTableView pour les salles
    nomColonnes << "Nom"
                << "Description"
                << "Indice de confort"
                << "Fenêtres"
                << "Lumières";
    modeleSalle = new QStandardItemModel(0, nomColonnes.size());
    modeleSalle->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewSalles->setModel(modeleSalle);
    ui->tableViewSalles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewSalles->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
    nbLignesSalle = modeleSalle->rowCount();

    chargerSalles();
}

/**
 * @brief Charge les données des salles dans le QTableView
 *
 * @fn IHM::chargerSalles
 */
void IHMEcoClassroom::chargerSalles()
{
    effacerTableSalles();

    // Exemple simple (pour le test)
    QStringList uneSalle;
    uneSalle << "B20"
             << "Atelier BTS"
             << "5 Tiède"
             << "Fermées"
             << "Eteintes";
    afficherSalleTable(uneSalle);
    // fin exemple
}

/**
 * @brief Affiche les données d'une salle dans le QTableView
 *
 * @fn IHM::afficherSalleTable
 * @param salle Les informations sur une salle
 */
void IHMEcoClassroom::afficherSalleTable(QStringList salle)
{
    qDebug() << Q_FUNC_INFO << salle;

    /**
     * @todo Implémenter la méthode en respectant les étapes ci-desssous
     *
     */

    // Créer les items pour les cellules d'une ligne

    // Ajouter les items dans le modèle de données

    // Personnaliser l'affichage d'une ligne

    // Incrémente le nombre de lignes
}

/**
 * @brief Efface les salles du QTableView
 *
 * @fn IHM::effacerTableSalles
 */
void IHMEcoClassroom::effacerTableSalles()
{
    qDebug() << Q_FUNC_INFO;
    salles.clear();
    modeleSalle->clear();
    modeleSalle->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewSalles->setModel(modeleSalle);
    nbLignesSalle = 0;
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
