#include "ihm.h"
#include "ui_ihm.h"
#include "utilisateur.h"
#include "basededonnees.h"
#include <QDebug>

/**
 * @file ihm.cpp
 *
 * @brief Définition de la classe IHM
 * @author Thierry Vaira <tvaira@free.fr>
 * @version 1.0
 *
 */

/**
 * @brief Constructeur de la classe IHM
 *
 * @fn IHM::IHM
 * @param parent L'adresse de l'objet parent, si nullptr IHM sera la
 * fenêtre principale de l'application
 */
IHM::IHM(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHM), nbLignesUtilisateurs(0)
{
    ui->setupUi(this);
    qDebug() << Q_FUNC_INFO;

    baseDeDonnees = BaseDeDonnees::getInstance();
    baseDeDonnees->ouvrir("exemple.sqlite");

    initialiser();

    gererEvenements();
}

/**
 * @brief Destructeur de la classe IHM
 *
 * @fn IHM::~IHM
 * @details Libère les ressources de l'application
 */
IHM::~IHM()
{
    delete ui;
    BaseDeDonnees::detruireInstance();
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Initialise le contenu de la fenêtre
 *
 * @fn IHM::initialiser
 */
void IHM::initialiser()
{
    ajouterMenuAide();

    ui->statusbar->showMessage(QString::fromUtf8(NOM_APPLICATION) + " " +
                               QString::fromUtf8(VERSION_APPLICATION));

    // Initialise le QTableView
    nomColonnes << "Nom"
                << "Prénom"
                << "Identifiant"
                << "Code";
    modeleUtilisateur = new QStandardItemModel(0, nomColonnes.size());
    modeleUtilisateur->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewUtilisateurs->setModel(modeleUtilisateur);
    ui->tableViewUtilisateurs->setEditTriggers(
      QAbstractItemView::NoEditTriggers);

    // Redimensionner automatiquement la colonne pour occuper l'espace
    // disponible
    ui->tableViewUtilisateurs->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
    nbLignesUtilisateurs = modeleUtilisateur->rowCount();

    afficherFenetre(IHM::Fenetre1);
}

/**
 * @brief Assure la connexion des signaux et slots
 *
 * @fn IHM::gererEvenements
 */
void IHM::gererEvenements()
{
    connect(ui->boutonCharger,
            SIGNAL(clicked(bool)),
            this,
            SLOT(chargerUtilisateurs()));
    connect(ui->boutonEffacer,
            SIGNAL(clicked(bool)),
            this,
            SLOT(effacerTableUtilisateurs()));
    connect(ui->tableViewUtilisateurs,
            SIGNAL(clicked(QModelIndex)),
            this,
            SLOT(selectionner(QModelIndex)));
    connect(ui->boutonRetour,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherFenetrePrincipale()));
}

/**
 * @brief Ajoute l'entrée de menu "Aide" dans la barre de menu
 *
 * @fn IHM::ajouterMenuAide
 */
void IHM::ajouterMenuAide()
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

/**
 * @brief Charge des données dans le QTableView
 *
 * @fn IHM::chargerUtilisateurs
 */
void IHM::chargerUtilisateurs()
{
    effacerTableUtilisateurs();

    // Exemple simple (si pas de base de données)
    /*
    QStringList utilisateur;
    utilisateur << "1"
                << "VAIRA"
                << "Thierry"
                << "tvaira"
                << "1234";
    afficherUtilisateurTable(utilisateur);
    */

    // Exemple avec une base de données SQLite
    QString requete = "SELECT * FROM Utilisateur";
    bool    retour;

    retour = baseDeDonnees->recuperer(requete, utilisateurs);
    qDebug() << Q_FUNC_INFO << retour;
    qDebug() << Q_FUNC_INFO << utilisateurs;
    for(int i = 0; i < utilisateurs.size(); ++i)
        afficherUtilisateurTable(utilisateurs.at(i));
}

/**
 * @brief Efface le QTableView
 *
 * @fn IHM::effacerTableUtilisateurs
 */
void IHM::effacerTableUtilisateurs()
{
    qDebug() << Q_FUNC_INFO;
    utilisateurs.clear();
    modeleUtilisateur->clear();
    modeleUtilisateur->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewUtilisateurs->setModel(modeleUtilisateur);
    nbLignesUtilisateurs = 0;
}

/**
 * @brief Affiche un utilisateur dans le QTableView
 *
 * @fn IHM::afficherUtilisateurTable
 * @param utilisateur Les informations sur un utilisateur
 */
void IHM::afficherUtilisateurTable(QStringList utilisateur)
{
    qDebug() << Q_FUNC_INFO << utilisateur;

    // Crée les items pour les cellules d'une ligne
    QStandardItem* nom =
      new QStandardItem(utilisateur.at(Utilisateur::TABLE_UTILISATEUR_NOM));
    QStandardItem* prenom =
      new QStandardItem(utilisateur.at(Utilisateur::TABLE_UTILISATEUR_PRENOM));
    QStandardItem* identifiant = new QStandardItem(
      utilisateur.at(Utilisateur::TABLE_UTILISATEUR_IDENTIFIANT));
    QStandardItem* code =
      new QStandardItem(utilisateur.at(Utilisateur::TABLE_UTILISATEUR_CODE));

    // Ajoute les items dans le modèle de données
    modeleUtilisateur->setItem(nbLignesUtilisateurs,
                               IHM::COLONNE_UTILISATEUR_NOM,
                               nom);
    modeleUtilisateur->setItem(nbLignesUtilisateurs,
                               IHM::COLONNE_UTILISATEUR_PRENOM,
                               prenom);
    modeleUtilisateur->setItem(nbLignesUtilisateurs,
                               IHM::COLONNE_UTILISATEUR_IDENTIFIANT,
                               identifiant);
    // exemple de personnalisation
    code->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    modeleUtilisateur->setItem(nbLignesUtilisateurs,
                               IHM::COLONNE_UTILISATEUR_CODE,
                               code);

    // Exemple de personnalisation de l'affichage d'une ligne
    QFont texte;
    // texte.setPointSize(12);
    texte.setBold(true);
    for(int i = 0; i < nomColonnes.size(); ++i)
    {
        QStandardItem* item = modeleUtilisateur->item(nbLignesUtilisateurs, i);
        item->setBackground(QColor(255, 223, 0));
        item->setFont(texte);
    }

    qDebug() << Q_FUNC_INFO << "nbLignesUtilisateurs" << nbLignesUtilisateurs;

    nbLignesUtilisateurs += 1;

    // Configure l'affichage du QTableView
    ui->tableViewUtilisateurs->setSizePolicy(QSizePolicy::Minimum,
                                             QSizePolicy::Minimum);
    ui->tableViewUtilisateurs->setVerticalScrollBarPolicy(
      Qt::ScrollBarAlwaysOff);
    ui->tableViewUtilisateurs->setHorizontalScrollBarPolicy(
      Qt::ScrollBarAlwaysOff);
    // ui->tableViewUtilisateurs->resizeColumnsToContents();

    ui->tableViewUtilisateurs->setMinimumWidth(ui->centralwidget->width());
    // ui->tableViewUtilisateurs->setMinimumHeight(ui->centralwidget->height());
    /*ui->tableViewUtilisateurs->setFixedSize(
      ui->tableViewUtilisateurs->horizontalHeader()->length() +
        ui->tableViewUtilisateurs->verticalHeader()->width(),
      ui->tableViewUtilisateurs->verticalHeader()->length() +
        ui->tableViewUtilisateurs->horizontalHeader()->height());*/
    ui->tableViewUtilisateurs->setFixedHeight(
      ui->tableViewUtilisateurs->verticalHeader()->length() +
      ui->tableViewUtilisateurs->horizontalHeader()->height());
}

/**
 * @brief Affiche les données de l'utilisateur sélectionné
 *
 * @fn IHM::selectionner
 * @param index index dans le modèle de données
 */
void IHM::selectionner(QModelIndex index)
{
    qDebug() << Q_FUNC_INFO << index.row(); // le numéro de ligne
    qDebug() << Q_FUNC_INFO
             << index.data().toString(); // le contenu de la cellule
    qDebug() << Q_FUNC_INFO
             << modeleUtilisateur->item(index.row(), 0)->text(); //
    qDebug() << Q_FUNC_INFO << utilisateurs.at(index.row());

    // Insère les données d'un utilisateur à afficher
    ui->nomUtilisateur->setText(
      utilisateurs.at(index.row()).at(Utilisateur::TABLE_UTILISATEUR_NOM));
    ui->prenomUtilisateur->setText(
      utilisateurs.at(index.row()).at(Utilisateur::TABLE_UTILISATEUR_PRENOM));
    ui->identifiantUtilisateur->setText(
      utilisateurs.at(index.row())
        .at(Utilisateur::TABLE_UTILISATEUR_IDENTIFIANT));
    ui->codeUtilisateur->setText(
      utilisateurs.at(index.row()).at(Utilisateur::TABLE_UTILISATEUR_CODE));

    // Affiche la fenêtre associée
    afficherFenetre(IHM::Fenetre2);
}

/**
 * @brief Méthode qui permet d'afficher une fenêtre de la pile
 * QStackedWidget
 *
 * @fn IHM::afficherFenetre
 * @param fenetre le numéro de fenêtre à afficher
 */
void IHM::afficherFenetre(IHM::Fenetre fenetre)
{
    qDebug() << Q_FUNC_INFO << "fenetre" << fenetre;
    ui->fenetres->setCurrentIndex(fenetre);
}

/**
 * @brief Affiche la première fenêtre
 *
 * @fn IHM::afficherFenetrePrincipale
 */
void IHM::afficherFenetrePrincipale()
{
    afficherFenetre(IHM::Fenetre1);
}

/**
 * @brief Affiche la boîte de dialogue A Propos ...
 *
 * @fn IHM::afficherAPropos
 */
void IHM::afficherAPropos()
{
    QMessageBox::about(
      this,
      QString::fromUtf8("À propos ..."),
      QString::fromUtf8("<p><b>") + QString::fromUtf8(NOM_APPLICATION) + " " +
        QString::fromUtf8(VERSION_APPLICATION) +
        QString::fromUtf8("</b><br/>") +
        QString::fromUtf8("Exemple de mise en oeuvre d'un QTableView") +
        QString::fromUtf8("</p>"));
}
