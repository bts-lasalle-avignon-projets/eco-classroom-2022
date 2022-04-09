#include "ihmecoclassroom.h"
#include "ui_ihmecoclassroom.h"
#include "basededonnees.h"
#include "salle.h"
#include "mesure.h"
#include <QDebug>

/**
 * @file ihmecoclassroom.cpp
 * @brief Définition de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 0.2
 */

/**
 * @brief Constructeur de la classe IHMEcoClassroom
 *
 * @fn IHMEcoClassroom::IHMEcoClassroom
 * @param parent L'adresse de l'objet parent, si nullptr IHMEcoClassroom sera la
 * fenêtre principale de l'application
 */
IHMEcoClassroom::IHMEcoClassroom(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMEcoClassroom), nbLignesSalle(0),
    salleSelectionnee(-1)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);
    baseDeDonnees = BaseDeDonnees::getInstance();
    baseDeDonnees->ouvrir("eco-classroom.db");
    ajouterMenuAide();
    initialiserAffichage();

    gererEvenements();
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
                << "Qualité d'air"
                << "Fenêtres"
                << "Lumières";
    modeleSalle = new QStandardItemModel(0, nomColonnes.size());
    modeleSalle->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewSalles->setModel(modeleSalle);
    ui->tableViewSalles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewSalles->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
    nbLignesSalle = modeleSalle->rowCount();

    // afficherFenetre(IHMEcoClassroom::Fenetre3);
    chargerSalles();
    afficherFenetre(IHMEcoClassroom::Fenetre::Accueil);
}

/**
 * @brief assla connexion des signaux et slots
 *
 * @fn IHMEcoClassroom::gererEvenements()
 */
void IHMEcoClassroom::gererEvenements()
{
    qDebug() << Q_FUNC_INFO;
    // Fenêtre Accueil
    connect(ui->boutonCharger,
            SIGNAL(clicked(bool)),
            this,
            SLOT(chargerSalles()));
    connect(ui->boutonEffacer,
            SIGNAL(clicked(bool)),
            this,
            SLOT(effacerTableSalles()));
    connect(ui->tableViewSalles,
            SIGNAL(clicked(QModelIndex)),
            this,
            SLOT(selectionner(QModelIndex)));
    // Fenêtre InformationsSalle
    connect(ui->buttonAccueil,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherFenetrePrincipale()));
    connect(ui->buttonEditerSalle, SIGNAL(clicked(bool)), this, SLOT(editer()));
    // Fenêtre SaisieCode
    connect(ui->buttonValiderCode,
            SIGNAL(clicked()),
            this,
            SLOT(verifierCode()));
    connect(ui->buttonAnnulerCode,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherFenetrePrincipale()));
    // Fenêtre EditionSalle
    connect(ui->buttonValiderEdition,
            SIGNAL(clicked(bool)),
            this,
            SLOT(validerEditionSalle()));
    connect(ui->buttonAnnulerEdition,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherFenetrePrincipale()));
}

/**
 * @brief Charge les données des salles dans le QTableView
 *
 * @fn IHMEcoClassroom::chargerSalles
 */
void IHMEcoClassroom::chargerSalles()
{
    effacerTableSalles();

    QString requete =
      "SELECT Salle.idSalle,"
      "Salle.nom,Salle.lieu,Salle.description,Salle.superficie,Salle.code,"
      "IndiceConfort.indice AS indiceConfort,IndiceConfort.libelle AS "
      "libelleIndiceConfort,IndiceQualiteAir.libelle AS "
      "libelleIndiceQualiteAir,Salle.etatFenetres,Salle.etatLumieres,Salle."
      "estOccupe FROM Salle INNER JOIN IndiceConfort ON "
      "IndiceConfort.idIndiceConfort=Salle.idIndiceConfort INNER JOIN "
      "IndiceQualiteAir ON "
      "IndiceQualiteAir.idIndiceQualiteAir=Salle.idIndiceQualiteAir";
    bool retour;

    retour = baseDeDonnees->recuperer(requete, salles);
    qDebug() << Q_FUNC_INFO << salles;
    if(retour)
    {
        for(int i = 0; i < salles.size(); ++i)
            afficherSalleTable(salles.at(i));
    }
}

/**
 * @brief Affiche les données d'une salle dans le QTableView
 *
 * @fn IHMEcoClassroom::afficherSalleTable
 * @param salle Les informations sur une salle
 */
void IHMEcoClassroom::afficherSalleTable(QStringList salle)
{
    qDebug() << Q_FUNC_INFO << salle;

    // Crée les items pour les cellules d'une ligne
    QStandardItem* nom = new QStandardItem(salle.at(Salle::NOM));
    QStandardItem* description =
      new QStandardItem(salle.at(Salle::DESCRIPTION));
    QString libelleIndiceConfort = salle.at(Salle::LIBELLE_INDICE_DE_CONFORT);
    libelleIndiceConfort.replace(0, 1, libelleIndiceConfort.at(0).toUpper());
    QStandardItem* indiceDeConfort   = new QStandardItem(libelleIndiceConfort);
    QString        libelleQualiteAir = salle.at(Salle::LIBELLE_QUALITE_AIR);
    libelleQualiteAir.replace(0, 1, libelleQualiteAir.at(0).toUpper());
    QStandardItem* qualiteAir   = new QStandardItem(libelleQualiteAir);
    QString        etatFenetres = "Fermées";
    if(salle.at(Salle::ETAT_DES_FENETRES).toInt())
        etatFenetres = "Ouvertes";
    QStandardItem* fenetres     = new QStandardItem(etatFenetres);
    QString        etatLumieres = "Éteintes";
    if(salle.at(Salle::ETAT_DES_LUMIERES).toInt())
        etatLumieres = "Allumées";
    QStandardItem* lumieres = new QStandardItem(etatLumieres);

    // Ajoute les items dans le modèle de données
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
                         IHMEcoClassroom::COLONNE_SALLE_QUALITE_AIR,
                         qualiteAir);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_FENETRES,
                         fenetres);
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_LUMIERES,
                         lumieres);

    // Personnalise l'affichage d'une ligne
    QFont texte;
    texte.setPointSize(12);
    texte.setBold(true);
    for(int i = 0; i < nomColonnes.size(); ++i)
    {
        QStandardItem* item = modeleSalle->item(nbLignesSalle, i);
        item->setBackground(QColor(255, 223, 0));
        item->setFont(texte);
    }

    // Incrémente le nombre de lignes
    qDebug() << Q_FUNC_INFO << "nbLignesSalle" << nbLignesSalle;
    nbLignesSalle += 1;

    // Configure l'affichage du QTableView
    ui->tableViewSalles->setSizePolicy(QSizePolicy::Minimum,
                                       QSizePolicy::Minimum);
    ui->tableViewSalles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewSalles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->tableViewSalles->setFixedHeight(
      ui->tableViewSalles->verticalHeader()->length() +
      ui->tableViewSalles->horizontalHeader()->height());
}

/**
 * @brief Efface les salles du QTableView
 *
 * @fn IHMEcoClassroom::effacerTableSalles
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

void IHMEcoClassroom::selectionner(QModelIndex index)
{
    qDebug() << Q_FUNC_INFO << "numéro de ligne"
             << index.row(); // le numéro de ligne
    qDebug() << Q_FUNC_INFO << salles.at(index.row());

    // Récupère la dernière mesure effectuée dans cette salle
    QString idSalle   = salles.at(index.row()).at(Salle::ID);
    salleSelectionnee = index.row();
    QStringList mesureSalle;
    QString requete = "SELECT * FROM Mesure WHERE Mesure.idSalle=" + idSalle +
                      " AND horodatage IN (SELECT max(horodatage) FROM Mesure)";
    bool retour;
    retour = baseDeDonnees->recuperer(requete, mesureSalle);
    qDebug() << Q_FUNC_INFO << mesureSalle;

    // Affiche la dernière mesure effectuée dans cette salle
    if(retour)
    {
        ui->labelCo2Salle->setText(mesureSalle.at(Mesure::CO2) + " ppm");
        ui->labelCo2->setVisible(true);
        ui->labelCo2Salle->setVisible(true);
        ui->labelTemperatureSalle->setText(mesureSalle.at(Mesure::TEMPERATURE) +
                                           " °C");
        ui->labelTemperature->setVisible(true);
        ui->labelTemperatureSalle->setVisible(true);
        QDateTime horodatage =
          QDateTime::fromString(mesureSalle.at(Mesure::HORODATAGE),
                                "yyyy-MM-dd HH:mm:ss");
        ui->labelHorodatage->setText(
          horodatage.toString("Le dd/MM/yyyy à HH:mm:ss"));
        ui->labelHorodatage->setVisible(true);
    }
    else
    {
        ui->labelCo2Salle->setText("");
        ui->labelCo2->setVisible(false);
        ui->labelCo2Salle->setVisible(false);
        ui->labelTemperatureSalle->setText("");
        ui->labelTemperature->setVisible(false);
        ui->labelTemperatureSalle->setVisible(false);
        ui->labelHorodatage->setText("");
        ui->labelHorodatage->setVisible(false);
    }

    // Affiche les informations d'une salle
    ui->labelNomSalle->setText(salles.at(index.row()).at(Salle::NOM));
    ui->labelLieuSalle->setText(salles.at(index.row()).at(Salle::LIEU));
    ui->labelDescriptionSalle->setText(
      salles.at(index.row()).at(Salle::DESCRIPTION));
    ui->labelSurfaceSalle->setText(
      salles.at(index.row()).at(Salle::SUPERFICIE) + " m2");
    QString libelleQualiteAir =
      salles.at(index.row()).at(Salle::LIBELLE_QUALITE_AIR);
    libelleQualiteAir.replace(0, 1, libelleQualiteAir.at(0).toUpper());
    ui->labelAirSalle->setText(libelleQualiteAir);
    QString libelleIndiceConfort =
      salles.at(index.row()).at(Salle::LIBELLE_INDICE_DE_CONFORT);
    libelleIndiceConfort.replace(0, 1, libelleIndiceConfort.at(0).toUpper());
    ui->labelIndiceDeConfortSalle->setText(libelleIndiceConfort);
    QString etatFenetres = "Fermées";
    if(salles.at(index.row()).at(Salle::ETAT_DES_FENETRES).toInt())
        etatFenetres = "Ouvertes";
    ui->labelFenetresSalle->setText(etatFenetres);
    QString etatLumieres = "Éteintes";
    if(salles.at(index.row()).at(Salle::ETAT_DES_LUMIERES).toInt())
        etatLumieres = "Allumées";
    ui->labelLumieresSalle->setText(etatLumieres);

    // Affiche la fenêtre de la salle
    afficherFenetre(IHMEcoClassroom::Fenetre::InformationsSalle);
}

/**
 * @brief saisir le code de modification
 * @fn  IHMEcoClassroom::editer
 */
void IHMEcoClassroom::editer()
{
    ui->lineEditCode->setText("");
    ui->labelEtatSaisie->setText("");
    afficherFenetre(IHMEcoClassroom::Fenetre::SaisieCode);
}

/**
 * @brief verifier le code d'administrateur pour paramétrer une salle
 *
 * @fn IHMEcoClassroom::verifierCode
 */

void IHMEcoClassroom::verifierCode()
{
    QString code = ui->lineEditCode->text();
    qDebug() << Q_FUNC_INFO << "code" << code;

    if(code.isEmpty())
    {
        QMessageBox::information(this,
                                 "Attention",
                                 "Vous devez saisir un code !");
    }
    else if(code == salles.at(salleSelectionnee).at(Salle::CODE))
    {
        // Affiche la fenêtre pour éditer les informations de la salle
        afficherFenetre(IHMEcoClassroom::Fenetre::EditionSalle);
        editerSalle();
    }
    else
    {
        ui->labelEtatSaisie->setText("Code invalide !");
    }
}

/**
 * @brief Éditer les différentes informations d'une salle
 * @fn  IHMEcoClassroom::editerSalle
 */
void IHMEcoClassroom::editerSalle()
{
    qDebug() << Q_FUNC_INFO;

    ui->lineEditNom->setText(salles.at(salleSelectionnee).at(Salle::NOM));
    ui->lineEditLieu->setText(salles.at(salleSelectionnee).at(Salle::LIEU));
    ui->lineEditDescription->setText(
      salles.at(salleSelectionnee).at(Salle::DESCRIPTION));
    ui->lineEditSurface->setText(
      salles.at(salleSelectionnee).at(Salle::SUPERFICIE));
    afficherFenetre(IHMEcoClassroom::Fenetre::EditionSalle);
    ui->labelLieuEdite->setText("");
}

/**
 * @brief Valide et enregistre les nouvelles informations d'une salle
 * @fn  IHMEcoClassroom::editerSalle
 */
void IHMEcoClassroom::validerEditionSalle()
{
    qDebug() << Q_FUNC_INFO << ui->lineEditNom->text()
             << ui->lineEditLieu->text() << ui->lineEditDescription->text()
             << ui->lineEditSurface->text();

    if(ui->lineEditNom->text().isEmpty())
    {
        QMessageBox::information(this,
                                 "Attention",
                                 "Vous devez saisir le nom de la salle !");
    }
    else
    {
        QString requete =
          "UPDATE Salle SET nom='" + ui->lineEditNom->text() + "', lieu='" +
          ui->lineEditLieu->text() + "', description='" +
          ui->lineEditDescription->text() + "', superficie='" +
          ui->lineEditSurface->text() +
          "' WHERE idSalle=" + salles.at(salleSelectionnee).at(Salle::ID) + ";";
        bool retour = baseDeDonnees->executer(requete);
        if(!retour)
        {
            QMessageBox::critical(
              this,
              "Erreur",
              "Les modifications n'ont pas été effectuées !");
        }
        else
        {
            chargerSalles();
            afficherFenetrePrincipale();
        }
    }
}

/**
 * @brief Méthode qui permet d'afficher une fenêtre de la pile
 * QStackedWidget
 *
 * @fn IHMEcoClassroom::afficherFenetre
 * @param fenetre le numéro de fenêtre à afficher
 */
void IHMEcoClassroom::afficherFenetre(IHMEcoClassroom::Fenetre fenetre)
{
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetre;
    ui->fenetres->setCurrentIndex(fenetre);
}

/**
 * @brief Affiche la première fenêtre
 *
 * @fn IHMEcoClassroom:afficherFenetrePrincipale
 */
void IHMEcoClassroom::afficherFenetrePrincipale()
{
    qDebug() << Q_FUNC_INFO;
    salleSelectionnee = -1;
    afficherFenetre(IHMEcoClassroom::Fenetre::Accueil);
}

void IHMEcoClassroom::ajouterMenuAide()
{
    qDebug() << Q_FUNC_INFO;
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
