#include "ihmecoclassroom.h"
#include "ui_ihmecoclassroom.h"
#include "basededonnees.h"
#include "communicationmqtt.h"
#include "salle.h"
#include "mesure.h"
#include <QDebug>

/**
 * @file ihmecoclassroom.cpp
 * @brief Définition de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 1.1
 */

/**
 * @brief Constructeur de la classe IHMEcoClassroom
 *
 * @fn IHMEcoClassroom::IHMEcoClassroom
 * @param parent L'adresse de l'objet parent, si nullptr IHMEcoClassroom sera la
 * fenêtre principale de l'application
 */
IHMEcoClassroom::IHMEcoClassroom(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::IHMEcoClassroom), baseDeDonnees(nullptr),
    communicationMQTT(nullptr), nbLignesSalle(0), salleSelectionnee(-1)
{
    qDebug() << Q_FUNC_INFO;
    ui->setupUi(this);

    initialiserEcoClassroom();
    ajouterMenuAide();
    initialiserAffichage();
    gererEvenements();

#ifdef TEST_SANS_BROKER_MQTT
    // Exemple pour simuler une réception
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    timerSimulation = new QTimer(this);
    connect(timerSimulation, SIGNAL(timeout()), this, SLOT(simuler()));
    timerSimulation->start(5000); // toutes les secondes
#endif
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

void IHMEcoClassroom::initialiserEcoClassroom()
{
    baseDeDonnees = BaseDeDonnees::getInstance();
    baseDeDonnees->ouvrir("eco-classroom.db");
    communicationMQTT = new CommunicationMQTT(this);
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
                << "Lumières"
                << "Occupation";
    modeleSalle = new QStandardItemModel(0, nomColonnes.size());
    modeleSalle->setHorizontalHeaderLabels(nomColonnes);
    ui->tableViewSalles->setModel(modeleSalle);
    ui->tableViewSalles->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewSalles->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
    nbLignesSalle = modeleSalle->rowCount();

    // Pour les tests : appeler show()
    ui->boutonCharger->hide();
    ui->boutonEffacer->hide();
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
    connect(ui->buttonEditerSalle,
            SIGNAL(clicked(bool)),
            this,
            SLOT(editerSalle()));
    // Fenêtre EditionSalle
    connect(ui->buttonValiderEdition,
            SIGNAL(clicked(bool)),
            this,
            SLOT(validerEditionSalle()));
    connect(ui->buttonAnnulerEdition,
            SIGNAL(clicked(bool)),
            this,
            SLOT(afficherFenetrePrincipale()));
    // Supprimer une salle
    connect(ui->buttonSupprimer,
            SIGNAL(clicked(bool)),
            this,
            SLOT(supprimerSalle()));
    // Communication
    connect(communicationMQTT,
            SIGNAL(nouvelleDonnee(QString, QString, QString)),
            this,
            SLOT(traiterNouvelleDonnee(QString, QString, QString)));
    // filtrer les salles
    connect(ui->listeSallesDetectees,
            SIGNAL(currentTextChanged(QString)),
            this,
            SLOT(filtrerSalles()));
}

/**
 * @brief Retourne l'idSalle à partir de son nom
 *
 * @fn IHMEcoClassroom::recupererIdSalle
 */
QString IHMEcoClassroom::recupererIdSalle(QString nomSalle)
{
    QString idSalle;
    QString requete = "SELECT idSalle FROM Salle WHERE nom='" + nomSalle + "';";
    baseDeDonnees->recuperer(requete, idSalle);
    qDebug() << Q_FUNC_INFO << nomSalle << "idSalle" << idSalle;
    return idSalle;
}

/**
 * @brief Retourne l'index à partir de son idSalle
 *
 * @fn IHMEcoClassroom::recupererIndexSalle
 */
int IHMEcoClassroom::recupererIndexSalle(QString idSalle)
{
    for(int i = 0; i < salles.size(); ++i)
    {
        if(idSalle == salles.at(i).at(Salle::ID))
        {
            return i;
        }
    }

    qDebug() << Q_FUNC_INFO << "index introuvable pour" << idSalle;
    return -1;
}

/**
 * @brief IHMEcoClassroom::reinitialiserAffichageMesureSalle
 */
void IHMEcoClassroom::reinitialiserAffichageMesureSalle()
{
    ui->labelCo2Salle->setText("");
    ui->labelCo2->setVisible(false);
    ui->labelCo2Salle->setVisible(false);
    ui->labelTemperatureSalle->setText("");
    ui->labelTemperature->setVisible(false);
    ui->labelTemperatureSalle->setVisible(false);
    ui->labelHumiditeSalle->setText("");
    ui->labelHumidite->setVisible(false);
    ui->labelHumiditeSalle->setVisible(false);
    ui->labelLuminositeSalle->setText("");
    ui->labelLuminosite->setVisible(false);
    ui->labelLuminositeSalle->setVisible(false);
    ui->labelHorodatage->setText("");
    ui->labelHorodatage->setVisible(false);
}

/**
 * @brief IHMEcoClassroom::afficherMesureSalle
 * @param mesureSalle
 */
void IHMEcoClassroom::afficherMesureSalle(QStringList mesureSalle,
                                          QString     mesureCo2Salle)
{
    ui->labelCo2Salle->setText(mesureCo2Salle + " ppm");
    ui->labelCo2->setVisible(true);
    ui->labelCo2Salle->setVisible(true);
    ui->labelTemperatureSalle->setText(mesureSalle.at(Mesure::TEMPERATURE) +
                                       " °C");
    ui->labelTemperature->setVisible(true);
    ui->labelTemperatureSalle->setVisible(true);
    ui->labelHumiditeSalle->setText(mesureSalle.at(Mesure::HUMIDITE) + " %");
    ui->labelHumidite->setVisible(true);
    ui->labelHumiditeSalle->setVisible(true);
    ui->labelLuminositeSalle->setText(mesureSalle.at(Mesure::LUMINOSITE) +
                                      " lux");
    ui->labelLuminosite->setVisible(true);
    ui->labelLuminositeSalle->setVisible(true);
    QDateTime horodatage =
      QDateTime::fromString(mesureSalle.at(Mesure::HORODATAGE),
                            "yyyy-MM-dd HH:mm:ss");
    ui->labelHorodatage->setText(
      horodatage.toString("Le dd/MM/yyyy à HH:mm:ss"));
    ui->labelHorodatage->setVisible(true);
}

/**
 * @brief IHMEcoClassroom::afficheInformationsSalle
 * @param index
 */
void IHMEcoClassroom::afficheInformationsSalle(int index)
{
    ui->labelNomSalle->setText(salles.at(index).at(Salle::NOM));
    ui->labelLieuSalle->setText(salles.at(index).at(Salle::LIEU));
    ui->labelDescriptionSalle->setText(salles.at(index).at(Salle::DESCRIPTION));
    ui->labelSurfaceSalle->setText(salles.at(index).at(Salle::SUPERFICIE) +
                                   " m2");
    QString libelleQualiteAir = salles.at(index).at(Salle::LIBELLE_QUALITE_AIR);
    libelleQualiteAir.replace(0, 1, libelleQualiteAir.at(0).toUpper());
    ui->labelAirSalle->setText(libelleQualiteAir);
    QString libelleIndiceConfort =
      salles.at(index).at(Salle::LIBELLE_INDICE_DE_CONFORT);
    libelleIndiceConfort.replace(0, 1, libelleIndiceConfort.at(0).toUpper());
    ui->labelIndiceDeConfortSalle->setText(libelleIndiceConfort);
    QString etatFenetres = "Fermées";
    if(salles.at(index).at(Salle::ETAT_DES_FENETRES).toInt())
        etatFenetres = "Ouvertes";
    ui->labelFenetresSalle->setText(etatFenetres);
    QString etatLumieres = "Éteintes";
    if(salles.at(index).at(Salle::ETAT_DES_LUMIERES).toInt())
        etatLumieres = "Allumées";
    ui->labelLumieresSalle->setText(etatLumieres);
    QString estOccupe = "Occupée";
    if(salles.at(index).at(Salle::ETAT_OCCUPATION).toInt())
        estOccupe = "Disponible";
    ui->labelOccupationSalle->setText(estOccupe);
}

/**
 * @brief IHMEcoClassroom::mettreAJourDonnee
 * @param donnee
 * @param typeDonnee
 * @param idSalle
 * @return
 */
bool IHMEcoClassroom::mettreAJourDonnee(QString donnee,
                                        QString typeDonnee,
                                        QString idSalle)
{
    QString   requete;
    QDateTime horodatage = QDateTime::currentDateTime();

    qDebug() << Q_FUNC_INFO << typeDonnee << donnee << idSalle;
    if(typeDonnee == ("temperature"))
    {
        requete = "UPDATE Mesure SET temperature='" + donnee +
                  "', horodatage='" +
                  horodatage.toString("yyyy-MM-dd HH:mm:ss") +
                  "' WHERE idSalle=" + idSalle + ";";
        calculerConfortThermique(idSalle);
    }
    else if(typeDonnee == ("humidite"))
    {
        requete = "UPDATE Mesure SET humidite='" + donnee + "', horodatage='" +
                  horodatage.toString("yyyy-MM-dd HH:mm:ss") +
                  "' WHERE idSalle=" + idSalle + ";";
        calculerConfortThermique(idSalle);
    }
    else if(typeDonnee == ("luminosite"))
    {
        requete = "UPDATE Mesure SET luminosite='" + donnee +
                  "', horodatage='" +
                  horodatage.toString("yyyy-MM-dd HH:mm:ss") +
                  "' WHERE idSalle=" + idSalle + ";";
    }
    else if(typeDonnee == ("confort"))
    {
        requete = "UPDATE Salle SET idIndiceConfort='" + donnee +
                  "' WHERE idSalle=" + idSalle + ";";
    }
    else if(typeDonnee == ("air"))
    {
        requete = "UPDATE Salle SET idIndiceQualiteAir='" + donnee +
                  "' WHERE idSalle=" + idSalle + ";";
    }
    else if(typeDonnee == ("fenetres"))
    {
        requete = "UPDATE Salle SET etatFenetres='" + donnee +
                  "' WHERE idSalle=" + idSalle + ";";
    }
    else if(typeDonnee == ("lumieres"))
    {
        requete = "UPDATE Salle SET etatLumieres='" + donnee +
                  "' WHERE idSalle=" + idSalle + ";";
    }
    else if(typeDonnee == ("occupation"))
    {
        requete = "UPDATE Salle SET estOccupe='" + donnee +
                  "' WHERE idSalle=" + idSalle + ";";
    }
    else if(typeDonnee == ("co2"))
    {
        requete = "INSERT INTO MesureCo2(co2, idSalle, horodatage) VALUES ('" +
                  donnee + "', '" + idSalle + "', '" +
                  horodatage.toString("yyyy-MM-dd HH:mm:ss") + "');";
    }
    else
    {
        return false;
    }

    // Enregistrer la nouvelle donnée dans la base de données
    bool retour = baseDeDonnees->executer(requete);

    return retour;
}

/**
 * @brief IHMEcoClassroom::insererNouvelleSalle
 * @param nomSalle
 * @return
 */
QString IHMEcoClassroom::insererNouvelleSalle(QString nomSalle)
{
    qDebug() << Q_FUNC_INFO << nomSalle << "nouvelle salle détectée !";
    QString requete = "INSERT INTO Salle(nom) VALUES ('" + nomSalle + "');";
    QString idSalle;
    bool    retour = baseDeDonnees->executer(requete);
    if(retour)
    {
        requete = "SELECT last_insert_rowid();";
        // Voir aussi : SELECT seq FROM sqlite_sequence WHERE name="Salle"
        retour = baseDeDonnees->recuperer(requete, idSalle);
        if(retour)
        {
            qDebug() << Q_FUNC_INFO << nomSalle << idSalle;
            QDateTime horodatage = QDateTime::currentDateTime();
            requete = "INSERT INTO Mesure(idSalle, horodatage) VALUES ('" +
                      idSalle + "', '" +
                      horodatage.toString("yyyy-MM-dd HH:mm:ss") + "');";
            retour = baseDeDonnees->executer(requete);

            requete = "INSERT INTO MesureCo2(idSalle, horodatage) VALUES ('" +
                      idSalle + "', '" +
                      horodatage.toString("yyyy-MM-dd HH:mm:ss") + "');";
            retour = baseDeDonnees->executer(requete);
            if(retour)
                return idSalle;
        }
    }

    return QString();
}

/**
 * @brief Charge les données des salles dans le QTableView
 *
 * @fn IHMEcoClassroom::chargerSalles
 */
void IHMEcoClassroom::chargerSalles()
{
    QString requete;

    requete = "SELECT Salle.idSalle,Salle.nom,Salle.lieu,Salle.description,"
              "Salle.superficie,"
              "IndiceConfort.idIndiceConfort AS indiceConfort,"
              "IndiceQualiteAir.idIndiceQualiteAir AS indiceQualiteAir,"
              "IndiceConfort.libelle AS libelleIndiceConfort,"
              "IndiceQualiteAir.libelle AS libelleIndiceQualiteAir,"
              "Salle.etatFenetres,Salle.etatLumieres,"
              "Salle.estOccupe FROM Salle "
              "INNER JOIN IndiceConfort ON "
              "IndiceConfort.idIndiceConfort=Salle.idIndiceConfort "
              "INNER JOIN IndiceQualiteAir ON "
              "IndiceQualiteAir.idIndiceQualiteAir=Salle.idIndiceQualiteAir";

    effacerTableSalles();

    bool retour;
    retour = baseDeDonnees->recuperer(requete, salles);
    qDebug() << Q_FUNC_INFO << salles;

    if(retour)
    {
        for(int i = 0; i < salles.size(); ++i)
        {
            afficherSalleTable(salles.at(i));
        }
    }
}

/**
 * @brief IHMEcoClassroom::filtrerSalles
 */
void IHMEcoClassroom::filtrerSalles()
{
    qDebug() << Q_FUNC_INFO << ui->listeSallesDetectees->currentIndex()
             << ui->listeSallesDetectees->currentText();

    chargerSalles();
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

    switch(ui->listeSallesDetectees->currentIndex())
    {
        case FiltreSalles::OCCUPEES:
            if(salle.at(Salle::ETAT_OCCUPATION).toInt())
                return;
            break;
        case FiltreSalles::DISPONIBLES:
            if(!salle.at(Salle::ETAT_OCCUPATION).toInt())
                return;
            break;
            // Utilisables
        case FiltreSalles::QUALITE_AIR:

            if(!salle.at(Salle::ETAT_OCCUPATION).toInt())
                return;
            // qualité d'air
            if(salle.at(Salle::INDICE_QUALITE_AIR).toInt() >=
               Salle::IndiceDeQualiteAir::MAUVAIS)
                return;
            break;
        case FiltreSalles::A_VERIFIER:
            // occupée ?
            if(!salle.at(Salle::ETAT_OCCUPATION).toInt())
                return;
            // ouverte ou allumée ?
            bool salleAVerifier = (salle.at(Salle::ETAT_DES_FENETRES).toInt() ||
                                   salle.at(Salle::ETAT_DES_LUMIERES).toInt());
            if(!salleAVerifier)
                return;
            if(salle.at(Salle::INDICE_QUALITE_AIR).toInt() <=
               Salle::IndiceDeQualiteAir::MAUVAIS)
                return;
            break;
    }

    // Crée les items pour les cellules d'une ligne
    QStandardItem* nom = new QStandardItem(salle.at(Salle::NOM));
    QStandardItem* description =
      new QStandardItem(salle.at(Salle::DESCRIPTION));

    QString libelleIndiceConfort = salle.at(Salle::LIBELLE_INDICE_DE_CONFORT);
    libelleIndiceConfort.replace(0, 1, libelleIndiceConfort.at(0).toUpper());
    QString libelleQualiteAir = salle.at(Salle::LIBELLE_QUALITE_AIR);
    libelleQualiteAir.replace(0, 1, libelleQualiteAir.at(0).toUpper());
    QString etatFenetres;
    QString etatLumieres;
    QString estOccupe;

    if(salle.at(Salle::ETAT_DES_FENETRES).toInt())
    {
        etatFenetres = "Ouvertes";
    }
    else
    {
        etatFenetres = "Fermées";
    }

    if(salle.at(Salle::ETAT_DES_LUMIERES).toInt())
    {
        etatLumieres = "Allumées";
    }
    else
    {
        etatLumieres = "Éteintes";
    }

    if(salle.at(Salle::ETAT_OCCUPATION).toInt())
    {
        estOccupe = "Disponible";
    }
    else
    {
        estOccupe = "Occupée";
    }

    QStandardItem* indiceDeConfort = new QStandardItem(libelleIndiceConfort);
    QStandardItem* qualiteAir      = new QStandardItem(libelleQualiteAir);
    QStandardItem* fenetres        = new QStandardItem(etatFenetres);
    QStandardItem* lumieres        = new QStandardItem(etatLumieres);
    QStandardItem* occupation      = new QStandardItem(estOccupe);

    if(salle.at(Salle::ETAT_DES_FENETRES).toInt() &&
       !salle.at(Salle::ETAT_OCCUPATION).toInt())
    {
        fenetres->setForeground(QColor(255, 0, 0));
    }
    else
    {
    }

    if(salle.at(Salle::ETAT_DES_LUMIERES).toInt() &&
       !salle.at(Salle::ETAT_OCCUPATION).toInt())
    {
        lumieres->setForeground(QColor(255, 0, 0));
    }
    else
    {
    }

    if(salle.at(Salle::ETAT_OCCUPATION).toInt())
    {
        occupation->setForeground(QColor(0, 255, 0));
    }
    else
    {
        occupation->setForeground(QColor(255, 0, 0));
    }

    // si l'indice de qualité d'air est au moins mauvais
    if(salle.at(Salle::INDICE_QUALITE_AIR).toInt() >=
       Salle::IndiceDeQualiteAir::TRES_MAUVAIS)
    {
        qualiteAir->setForeground(QColor(255, 0, 0));
    }
    if(salle.at(Salle::INDICE_QUALITE_AIR).toInt() ==
       Salle::IndiceDeQualiteAir::MAUVAIS)
    {
        qualiteAir->setForeground(QColor(0xf9, 0x92, 0x05));
    }
    else if(salle.at(Salle::INDICE_QUALITE_AIR).toInt() <=
            Salle::IndiceDeQualiteAir::BON)
    {
        qualiteAir->setForeground(QColor(0, 255, 0));
    }

    // si l'indice de confort est au moins tiéde
    if(salle.at(Salle::INDICE_DE_CONFORT).toInt() >=
         Salle::IndiceDeConfort::TIEDE ||
       salle.at(Salle::INDICE_DE_CONFORT).toInt() <=
         Salle::IndiceDeConfort::FRAIS)
    {
        indiceDeConfort->setForeground(QColor(255, 0, 0));
    }

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
    modeleSalle->setItem(nbLignesSalle,
                         IHMEcoClassroom::COLONNE_SALLE_OCCUPATION,
                         occupation);

    // Personnalise l'affichage d'une ligne
    QFont texte;
    texte.setPointSize(12);
    texte.setBold(true);
    for(int i = 0; i < nomColonnes.size(); ++i)
    {
        QStandardItem* item = modeleSalle->item(nbLignesSalle, i);
        item->setBackground(QColor(255, 223, 0));
        item->setFont(texte);
        item->setTextAlignment(Qt::AlignCenter);
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

    // Récupère la mesure effectuée dans cette salle
    QString idSalle   = salles.at(index.row()).at(Salle::ID);
    salleSelectionnee = index.row();
    QStringList mesureSalle;
    QString     mesureCo2Salle;
    QString     requete;

    // Récupére les mesures de cette salle
    requete     = "SELECT * FROM Mesure WHERE Mesure.idSalle=" + idSalle + "";
    bool retour = baseDeDonnees->recuperer(requete, mesureSalle);
    qDebug() << Q_FUNC_INFO << mesureSalle;
    if(retour)
    {
        // Récupére la dernière mesure de CO2
        requete =
          "SELECT co2 FROM MesureCo2 WHERE MesureCo2.idSalle=" + idSalle +
          " AND horodatage IN (SELECT max(horodatage) FROM MesureCo2" +
          " WHERE MesureCo2.idSalle=" + idSalle + ")";
        retour = baseDeDonnees->recuperer(requete, mesureCo2Salle);
        qDebug() << Q_FUNC_INFO << "mesureCo2Salle" << mesureCo2Salle;
        verifierSeuilCO2(mesureCo2Salle.toInt());

        // Affiche les mesures effectuées dans cette salle
        afficherMesureSalle(mesureSalle, mesureCo2Salle);
    }
    else
    {
        reinitialiserAffichageMesureSalle();
    }

    calculerConfortThermique(salles.at(salleSelectionnee).at(Salle::ID));

    // Affiche les informations de la salle
    afficheInformationsSalle(index.row());

    // Affiche la fenêtre de la salle
    afficherFenetre(IHMEcoClassroom::Fenetre::InformationsSalle);
}

/**
 * @brief IHMEcoClassroom::calculerConfortThermique
 */
void IHMEcoClassroom::calculerConfortThermique(QString idSalle)
{
    qDebug() << Q_FUNC_INFO << "idSalle" << idSalle;
    QString requete;
    QString mesureTemperature;
    QString mesureHumidite;
    bool    retour;

    // Récupérer les mesures de températures et d'humidité
    requete =
      "SELECT temperature FROM Mesure WHERE Mesure.idSalle=" + idSalle + "";
    retour = baseDeDonnees->recuperer(requete, mesureTemperature);
    qDebug() << Q_FUNC_INFO << "mesuretemperature" << mesureTemperature;

    requete =
      "SELECT humidite FROM Mesure WHERE Mesure.idSalle=" + idSalle + "";
    retour = baseDeDonnees->recuperer(requete, mesureHumidite);
    qDebug() << Q_FUNC_INFO << "mesurehumidite" << mesureHumidite;
    if(retour)
    {
        // Calculer l'indice de Thom
        double temperature = mesureTemperature.toDouble();
        double humidite    = mesureHumidite.toDouble();

        double thom =
          temperature - (0.55 - 0.0055 * humidite) * (temperature - 14.5);
        qDebug() << Q_FUNC_INFO << "thom" << thom;

        // Déterminer l'indice de niveau de confort
        Salle::IndiceDeConfort indiceDeConfort =
          (Salle::IndiceDeConfort::INCONNU);

        if(thom < SEUIL_THOM_FROID)
        {
            indiceDeConfort = (Salle::IndiceDeConfort::FROID);
        }
        else if(thom >= SEUIL_THOM_FROID && thom < SEUIL_THOM_FRAIS)
        {
            indiceDeConfort = (Salle::IndiceDeConfort::FRAIS);
        }
        else if(thom >= SEUIL_THOM_FRAIS && thom < SEUIL_THOM_LEGEREMENT_FRAIS)
        {
            indiceDeConfort = (Salle::IndiceDeConfort::LEGEREMENT_FRAIS);
        }
        else if(thom >= SEUIL_THOM_LEGEREMENT_FRAIS && thom < SEUIL_THOM_NEUTRE)
        {
            indiceDeConfort = (Salle::IndiceDeConfort::NEUTRE);
        }
        else if(thom >= SEUIL_THOM_NEUTRE && thom < SEUIL_THOM_LEGEREMENT_TIEDE)
        {
            indiceDeConfort = (Salle::IndiceDeConfort::LEGEREMENT_TIEDE);
        }
        else if(thom >= SEUIL_THOM_LEGEREMENT_TIEDE && thom < SEUIL_THOM_TIEDE)
        {
            indiceDeConfort = (Salle::IndiceDeConfort::TIEDE);
        }
        else if(thom >= SEUIL_THOM_TIEDE)
        {
            indiceDeConfort = (Salle::IndiceDeConfort::CHAUD);
        }

        qDebug() << Q_FUNC_INFO << "indiceDeConfort" << indiceDeConfort;

        QString requete = "UPDATE Salle SET idIndiceConfort='" +
                          QString::number(indiceDeConfort) +
                          "' WHERE idSalle=" + idSalle + ";";

        // Enregistrer la nouvelle donnée dans la base de données
        retour = baseDeDonnees->executer(requete);
    }
}

/**
 * @brief IHMEcoClassroom::verifierSeuilCO2
 * @param int mesureCo2Salle
 */
void IHMEcoClassroom::verifierSeuilCO2(int mesureCo2Salle)
{
    qDebug() << Q_FUNC_INFO << "mesureCo2Salle" << mesureCo2Salle
             << "SEUIL_MAX_CO2" << SEUIL_MAX_CO2;

    if(mesureCo2Salle >= SEUIL_MAX_CO2)
    {
        ui->labelCo2Max->setText("Attention, la qualité d'air dans cette "
                                 "salle dépasse le seuil réglementaire. "
                                 "Il faut aérer.");
    }
}

/**
 * @brief Supprime la salle sélectionnée
 */
void IHMEcoClassroom::supprimerSalle()
{
    if(salleSelectionnee == -1)
        return;
    qDebug() << Q_FUNC_INFO << salleSelectionnee;

    QString                     requete;
    QMessageBox::StandardButton reponse;
    reponse = QMessageBox::question(this,
                                    "Supprimer une salle",
                                    "Voulez-vous supprimer cette salle ?",
                                    QMessageBox::Yes | QMessageBox::No);
    if(reponse == QMessageBox::Yes)
    {
        requete = "DELETE FROM Salle WHERE idSalle='" +
                  salles.at(salleSelectionnee).at(Salle::ID) + "';";

        bool retour = baseDeDonnees->executer(requete);
        if(!retour)
        {
            QMessageBox::critical(this, "Erreur", "La suppression a échoué !");
        }
        else
        {
            qDebug() << Q_FUNC_INFO
                     << salles.at(salleSelectionnee).at(Salle::ID)
                     << salles.at(salleSelectionnee).at(Salle::NOM);
            salleSelectionnee = -1;
            chargerSalles();
            afficherFenetrePrincipale();
        }
    }
}

/**
 * @brief Éditer les différentes informations d'une salle
 * @fn  IHMEcoClassroom::editerSalle
 */
void IHMEcoClassroom::editerSalle()
{
    if(salleSelectionnee == -1)
        return;
    qDebug() << Q_FUNC_INFO << salleSelectionnee;

    ui->lineEditNom->setText(salles.at(salleSelectionnee).at(Salle::NOM));
    ui->labelSalleNomEdite->setText(
      salles.at(salleSelectionnee).at(Salle::NOM));
    ui->lineEditLieu->setText(salles.at(salleSelectionnee).at(Salle::LIEU));
    ui->lineEditDescription->setText(
      salles.at(salleSelectionnee).at(Salle::DESCRIPTION));
    ui->lineEditSurface->setText(
      salles.at(salleSelectionnee).at(Salle::SUPERFICIE));
    afficherFenetre(IHMEcoClassroom::Fenetre::EditionSalle);
}

/**
 * @brief Valide et enregistre les nouvelles informations d'une salle
 * @fn  IHMEcoClassroom::editerSalle
 */
void IHMEcoClassroom::validerEditionSalle()
{
    if(salleSelectionnee == -1)
        return;

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
            salleSelectionnee = -1;
            chargerSalles();
            afficherFenetrePrincipale();
        }
    }
}

/**
 * @brief Cette méthode permet de traiter la trams reçu
 * @param nomSalle
 * @param typeDonnee
 * @param donnee
 * @fn IHMEcoClassroom::traiterNouvelleDonnee
 */
void IHMEcoClassroom::traiterNouvelleDonnee(QString nomSalle,
                                            QString typeDonnee,
                                            QString donnee)
{
    QString idSalle = recupererIdSalle(nomSalle);

    if(idSalle.isEmpty())
    {
        idSalle = insererNouvelleSalle(nomSalle);
    }

    if(!idSalle.isEmpty())
    {
        bool retour = mettreAJourDonnee(donnee, typeDonnee, idSalle);
        if(retour)
        {
            chargerSalles();
            idSalle   = recupererIdSalle(nomSalle);
            int index = recupererIndexSalle(idSalle);
            if(index != -1 && index == salleSelectionnee)
            {
                QStringList mesureSalle;
                QString     mesureCo2Salle;
                QString     requete =
                  "SELECT * FROM Mesure WHERE Mesure.idSalle=" + idSalle + "";
                retour  = baseDeDonnees->recuperer(requete, mesureSalle);
                requete = "SELECT * FROM MesureCo2 WHERE MesureCo2.idSalle =" +
                          idSalle + "";
                retour = baseDeDonnees->recuperer(requete, mesureCo2Salle);
                if(retour)
                {
                    verifierSeuilCO2(mesureCo2Salle.toInt());
                    afficherMesureSalle(mesureSalle, mesureCo2Salle);
                }
                afficheInformationsSalle(index);
            }
        }
        else
        {
            qDebug() << "erreur modification !";
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
        QString::fromUtf8(VERSION) +
        QString::fromUtf8(
          "</b><br/><br/>Supervision de salles dans un établissement "
          "scolaire<br/><br/>Zeryouhi Mohamed Amine</p>"));
}

#ifdef TEST_SANS_BROKER_MQTT
void IHMEcoClassroom::simuler()
{
    // simule une réception de donnée sans MQTT
    QStringList nomsDeSalle;
    nomsDeSalle << "B11"
                << "B20"
                << "B21"
                << "B22"
                << "G21";
    QStringList nomsDeTopic;
    nomsDeTopic << "temperature"
                << "humidite"
                << "co2"
                << "luminosite"
                << "air"
                << "fenetres"
                << "lumieres"
                << "occupation";
    QString    salle      = nomsDeSalle.at(randInt(0, nomsDeSalle.size() - 1));
    QString    typeDonnee = nomsDeTopic.at(randInt(0, nomsDeTopic.size() - 1));
    QByteArray donnee =
      QString::number(simulerDonnee(typeDonnee)).toLocal8Bit();
    qDebug() << Q_FUNC_INFO << salle << typeDonnee << donnee;
    communicationMQTT->recevoir(
      donnee,
      QMqttTopicName(QString("salles/") + salle + QString("/") + typeDonnee));
}

int IHMEcoClassroom::simulerDonnee(QString typeDonnee)
{
    if(typeDonnee == ("temperature"))
    {
        return randInt(15, 35);
    }
    else if(typeDonnee == ("humidite"))
    {
        return randInt(0, 100);
    }
    else if(typeDonnee == ("co2"))
    {
        return randInt(1300, 1500);
    }
    else if(typeDonnee == ("luminosite"))
    {
        return randInt(40, 400);
    }
    else if(typeDonnee == ("air"))
    {
        return randInt(6, 6);
    }
    else if(typeDonnee == ("fenetres"))
    {
        return randInt(1, 1);
    }
    else if(typeDonnee == ("lumieres"))
    {
        return randInt(1, 1);
    }
    else if(typeDonnee == ("occupation"))
    {
        return randInt(0, 1);
    }
    return -1;
}

int IHMEcoClassroom::randInt(int min, int max)
{
    return qrand() % ((max + 1) - min) + min;
}
#endif
