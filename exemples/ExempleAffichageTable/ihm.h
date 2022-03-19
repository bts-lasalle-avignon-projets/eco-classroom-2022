#ifndef IHM_H
#define IHM_H

/**
 * @file ihm.h
 *
 * @brief Déclaration de la classe IHM
 * @author Thierry Vaira <tvaira@free.fr>
 * @version 1.0
 *
 */

#include <QtWidgets>

/**
 * @def NOM_APPLICATION
 * @brief Le nom de l'application
 */
#define NOM_APPLICATION "Exemple QTableView"

/**
 * @def VERSION_APPLICATION
 * @brief La version de l'application
 */
#define VERSION_APPLICATION "1.0"

QT_BEGIN_NAMESPACE
namespace Ui
{
class IHM;
}
QT_END_NAMESPACE

class BaseDeDonnees;

/**
 * @class IHM
 * @brief Déclaration de la classe IHM
 * @details Cette classe s'occupe de l'affichage de la fenêtre principale
 */
class IHM : public QMainWindow
{
    Q_OBJECT

  public:
    IHM(QWidget* parent = nullptr);
    ~IHM();

  private:
    Ui::IHM*       ui; //!< la fenêtre graphique associée à cette classe
    BaseDeDonnees* baseDeDonnees;        //!< Instance d'un objet BaseDeDonnees
    QStringList    nomColonnes;          //!< Liste de nom des colonnes
    int            nbLignesUtilisateurs; //!< nombre de lignes
    QVector<QStringList> utilisateurs;   //!< Les utilisateurs
    QStandardItemModel*  modeleUtilisateur; //!< Modèle pour le QTableView

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
     * @enum ColonneUtilisateur
     * @brief Définit les différentes colonne du QTableView
     */
    enum ColonneUtilisateur
    {
        COLONNE_UTILISATEUR_NOM,         //!< Emplacment du nom
        COLONNE_UTILISATEUR_PRENOM,      //!< Emplacment du prenom
        COLONNE_UTILISATEUR_IDENTIFIANT, //!< Emplacment de l'identifiant
        COLONNE_UTILISATEUR_CODE,        //!< Emplacment du code
        NB_COLONNES
    };

    void initialiser();
    void gererEvenements();
    void ajouterMenuAide();

  public slots:
    void chargerUtilisateurs();
    void effacerTableUtilisateurs();
    void afficherUtilisateurTable(QStringList utilisateur);
    void selectionner(QModelIndex index);
    void afficherFenetre(IHM::Fenetre fenetre);
    void afficherFenetrePrincipale();
    void afficherAPropos();
};

#endif // IHM_H
