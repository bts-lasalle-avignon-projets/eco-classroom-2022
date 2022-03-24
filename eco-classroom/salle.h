#ifndef SALLE_H
#define SALLE_H

/**
 * @file salle.h
 * @brief Déclaration de la classe Salle
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

#include <QString>
#include <QStringList>

/**
 * @class Salle
 * @brief Déclaration de la classe Salle
 * @details
 */
class Salle
{
  private:
    QStringList salle;       //!< les données d'une salle
    QString     nom;         //!< nom de la salle
    QString     lieu;        //!< lieu de la salle
    QString     description; //!< la description d'une salle
    int         surface;     //!< la surface d'une salle
    int         code; //!< le code administrateur pour paramétrer une salle
    bool        etatfenetres; //!< l'état des fenétres
    bool        etatlumieres; //!< l'état des lumières

  public:
    Salle();
    ~Salle();

    QStringList getSalle();
    QString     getNom();
    QString     getLieu();
    QString     getDesciption();
    int         getSurface();
    int         getCode();
    bool        getEtatFenetres();
    bool        getEtatLumierres();

    /**
     * @enum ChampsUtilisateur
     * @brief Définit les différents champs de la table Salle
     */
    enum ChampsSalle
    {
        TABLE_SALLER_NOM,              //!< Emplacment du nom
        TABLE_SALLER_DESCRIPTION,      //!< Emplacment de description
        TABLE_SALLE_INDICE_DE_CONFORT, //!< Emplacment de l'indice de confort
        TABLE_SALLE_ETAT_DES_FENETRES, //!< Emplacment d'état des fenétres
        TABLE_SALLE_ETAT_DES_LUMIERES, //!< Emplacment d'état des lumieres
    };
};

#endif // SALLE_H
