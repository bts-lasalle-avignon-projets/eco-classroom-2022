#ifndef IHMECOCLASSROOM_H
#define IHMECOCLASSROOM_H

/**
 * @file ihmecoclassroom.h
 * @brief Déclaration de la classe IHMEcoClassroom
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

#include <QtWidgets>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM "Eco-Classroom"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION "0.1"

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHMEcoClassroom;
}
QT_END_NAMESPACE

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
    Ui::IHMEcoClassroom* ui; //!< la fenêtre graphique associée à cette classe
    CommunicationMQTT*
                         communicationMQTT; //!< association avec la classe CommunicationMQTT
    QStringList          nomColonnes;   //!< Liste de nom des colonnes
    int                  nbLignesSalle; //!< nombre de lignes
    QVector<QStringList> salle;         //!< Les salles
    QStandardItemModel*  modeleSalle;   //!< Modèle pour le QTableView

    /**
     * @enum Fenetre
     * @brief Définit les différentes fenêtres de l'IHM
     *
     */
    enum Fenetre
    {
        Fenetre1 = 0,
        Fenetre2,
        NbFenetres
    };

    /**
     * @enum ColonneSalle
     * @brief Définit les différentes colonne du QTableView
     */
    enum ColonneSalle
    {
        COLONNE_SALLE_NOM,               //!< Emplacment de nom
        COLONNE_SALLE_DESCRIPTION,       //!< Emplacment de description
        COLONNE_SALLE_INDICE_DE_CONFORT, //!< Emplacment d'indice de confort
        COLONNE_SALLE_FENETRES,          //!< Emplacment des fenétres
        COLONNE_SALLE_LUMIERES,          //!< Emplacment des lumières
        NB_COLONNES
    };

    void initialiser();

    void ajouterMenuAide();

  public slots:
    void afficherAPropos();
};

#endif // IHMECOCLASSROOM_H
