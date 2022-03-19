#ifndef UTILISATEUR_H
#define UTILISATEUR_H

/**
 * @file utilisateur.h
 * @brief Déclaration de la classe Utilisateur
 * @author Thierry Vaira
 * @version 1.0
 */

#include <QObject>

/**
 * @class Utilisateur
 * @brief La classe Utilisateur gère les données relative à l'utilisateur
 * @author Thierry Vaira
 * @version 1.0
 */

class Utilisateur : public QObject
{
    Q_OBJECT
  public:
    Utilisateur(QObject* parent = nullptr);
    Utilisateur(QStringList utilisateur, QObject* parent = nullptr);
    ~Utilisateur();

    QStringList getUtilisateur();
    QString     getIdUtilisateur();
    QString     getNom();
    QString     getPrenom();
    QString     getIdentifiant();
    QString     getCode();

    /**
     * @enum ChampsUtilisateur
     * @brief Définit les différents champs de la table Utilisateur
     */
    enum ChampsUtilisateur
    {
        TABLE_UTILISATEUR_ID_UTILISATEUR, //!< Emplacment de l'idUtilisateur
        TABLE_UTILISATEUR_NOM,            //!< Emplacment du nom
        TABLE_UTILISATEUR_PRENOM,         //!< Emplacment du prenom
        TABLE_UTILISATEUR_IDENTIFIANT,    //!< Emplacment de l'identifiant
        TABLE_UTILISATEUR_CODE,           //!< Emplacment du code
    };

  private slots:

  signals:

  private:
    QStringList utilisateur;   //!< les données d'un utilisateur
    QString     idUtilisateur; //!< idUtilisateur de l'utilisateur
    QString     nom;           //!< nom de l'utilisateur
    QString     prenom;        //!< prenom de l'utilisateur
    QString     identifiant;   //!< identifiant de l'utilisateur
    QString     code;          //!< badge de l'utilisateur
};

#endif // UTILISATEUR_H
