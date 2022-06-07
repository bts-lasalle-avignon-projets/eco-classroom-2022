#ifndef IHMECOCLASSROOM_H
#define IHMECOCLASSROOM_H

/**
 * @file ihmecoclassroom.h
 * @brief Déclaration de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 0.2
 */

#include <QtWidgets>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM_APPLICATION "Eco-Classroom"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION "0.2"

#define TEST_SANS_BROKER_MQTT

namespace Ui
{
class IHMEcoClassroom;
}

class BaseDeDonnees;
class CommunicationMQTT;

/**
 * @class IHMEcoClassroom
 * @brief Déclaration de la classe IHMEcoClassroom
 * @details Cette classe s'occupe de l'affichage de la fenêtre principale
 */
class IHMEcoClassroom : public QMainWindow
{
    Q_OBJECT

  public:
    IHMEcoClassroom(QWidget* parent = nullptr);
    ~IHMEcoClassroom();

  private:
    Ui::IHMEcoClassroom* ui; //!< La fenêtre graphique associée à cette classe
    BaseDeDonnees*       baseDeDonnees; //!< Base de donnes
    CommunicationMQTT*   communicationMQTT;
    QStringList          nomColonnes;   //!< Liste de nom des colonnes
    int                  nbLignesSalle; //!< Nombre de lignes
    QVector<QStringList> salles;        //!< Les salles
    QStandardItemModel*  modeleSalle;   //!< Modèle pour le QTableView
    int
      salleSelectionnee; //!< Indice de la salle sélectionnée à éditer sinon -1
#ifdef TEST_SANS_BROKER_MQTT
    QTimer* timerSimulation;
    int     simulerDonnee(QString typeDonnee);
    int     randInt(int min, int max);
#endif

    /**
     * @enum Fenetre
     * @brief Définit les différentes fenêtres de l'IHM
     *
     */
    enum Fenetre
    {
        Accueil = 0,
        InformationsSalle,
        EditionSalle,
        NbFenetres
    };

    /**
     * @enum ColonneSalle
     * @brief Définit les différentes colonne du QTableView
     */
    enum ColonneSalle
    {
        COLONNE_SALLE_NOM,               //!< Emplacement de nom
        COLONNE_SALLE_DESCRIPTION,       //!< Emplacement de description
        COLONNE_SALLE_INDICE_DE_CONFORT, //!< Emplacement d'indice de confort
        COLONNE_SALLE_QUALITE_AIR, //!< Emplacement d'indice de qualité d'air
        COLONNE_SALLE_FENETRES,    //!< Emplacement des fenétres
        COLONNE_SALLE_LUMIERES,    //!< Emplacement des lumières
        COLONNE_SALLE_OCCUPATION,  //!< Emplacement d'occupation
        NB_COLONNES
    };

    /**
     * @enum FiltreSalles
     * @brief Définit les différents index de la liste déroulante
     */
    enum FiltreSalles
    {
        TOUTES,
        OCCUPEES,
        DISPONIBLES,
        QUALITE_AIR,
        A_VERIFIER
    };

    void    initialiserEcoClassroom();
    void    initialiserAffichage();
    void    ajouterMenuAide();
    void    gererEvenements();
    QString recupererIdSalle(QString nomSalle);
    int     recupererIndexSalle(QString idSalle);
    void    reinitialiserAffichageMesureSalle();
    void afficherMesureSalle(QStringList mesureSalle, QString mesureCo2Salle);
    void afficheInformationsSalle(int index);
    bool mettreAJourDonnee(QString donnee, QString typeDonnee, QString idSalle);
    QString insererNouvelleSalle(QString nomSalle);

  public slots:
    void chargerSalles();
    void filtrerSalles();
    void afficherSalleTable(QStringList salle);
    void effacerTableSalles();
    void selectionner(QModelIndex index);
    void supprimerSalle();
    void editerSalle();
    void validerEditionSalle();
    void traiterNouvelleDonnee(QString nomSalle,
                               QString typeDonnee,
                               QString donnee);
    void afficherFenetre(IHMEcoClassroom::Fenetre fenetre);
    void afficherFenetrePrincipale();
    void afficherAPropos();
#ifdef TEST_SANS_BROKER_MQTT
    void simuler();
#endif
};

#endif // IHMECOCLASSROOM_H
