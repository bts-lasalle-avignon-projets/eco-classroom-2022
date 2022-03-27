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
    ui->statusbar->showMessage(QString::fromUtf8(NOM_APPLICATION) + " " +
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
 *  utilisateur@fn IHM::chargerSalles
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
    QStandardItem* nom = new QStandardItem(salle.at(Salle::NOM));
    QStandardItem* description =
      new QStandardItem(salle.at(Salle::DESCRIPTION));
    QStandardItem* indiceDeConfort =
      new QStandardItem(salle.at(Salle::INDICE_DE_CONFORT));
    QStandardItem* fenetres =
      new QStandardItem(salle.at(Salle::ETAT_DES_FENETRES));
    QStandardItem* lumieres =
      new QStandardItem(salle.at(Salle::ETAT_DES_LUMIERES));

    // Ajouter les items dans le modèle de données
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_NOM,
                         nom);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_DESCRIPTION,
                         description);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_INDICE_DE_CONFORT,
                         indiceDeConfort);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_FENETRES,
                         fenetres);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_LUMIERES,
                         lumieres);

    // Personnaliser l'affichage d'une ligne
    QFont texte;
    // texte.setPointSize(12);
    texte.setBold(true);
    for(int i = 0; i < nomColonnes.size(); ++i)
    {
        QStandardItem* item = modeleSalle->item(nbLignesSalle, i);
        item->setBackground(QColor(255, 223, 0));
        item->setFont(texte);
    }
    // Incrémente le nombre de lignes
    qDebug() << Q_FUNC_INFO << "nbLignesUtilisateurs" << nbLignesSalle;

    nbLignesSalle += 1;

    // Configure l'affichage du QTableView
    ui->tableViewSalles->setSizePolicy(QSizePolicy::Minimum,
                                       QSizePolicy::Minimum);
    ui->tableViewSalles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewSalles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewSalles->setMinimumWidth(ui->centralwidget->width());
    ui->tableViewSalles->setFixedHeight(
      ui->tableViewSalles->verticalHeader()->length() +
      ui->tableViewSalles->horizontalHeader()->height());
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

    menuAide->addAction(QString::fromUtf8("À propos ") +
                          QString::fromUtf8(NOM_APPLICATION),
                        this,
                        SLOT(afficherAPropos()));
    menuAide->addAction(QString::fromUtf8("À propos de Qt"),
                        qApp,
                        SLOT(aboutQt()));
}

void IHMEcoClassroom::afficherAPropos()
{
    QMessageBox::about(
      this,
      QString::fromUtf8("À propos ..."),
      QString::fromUtf8("<p><b>") + QString::fromUtf8(NOM_APPLICATION) + " " +
        QString::fromUtf8(VERSION) + QString::fromUtf8("</b><br/>...</p>"));
}
