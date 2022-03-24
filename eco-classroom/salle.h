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
    QStringList salle;         //!< les données d'une salle
    QString     nom;           //!< nom de la salle
    QString     lieu;          //!< lieu de la salle
    QString     description;   //!< la description d'une salle
    int         surface;       //!< la surface d'une salle
    QString     indiceConfort; //!< l'indice de confort d'une salle
    QString     code; //!< le code administrateur pour paramétrer une salle
    bool        etatFenetres; //!< l'état des fenêtres
    bool        etatLumieres; //!< l'état des lumières

  public:
    Salle();
    Salle(QStringList salle);
    ~Salle();

    QStringList getSalle();
    QString     getNom();
    QString     getLieu();
    QString     getDesciption();
    int         getSurface();
    QString     getIndiceConfort();
    QString     getCode();
    bool        getEtatFenetres();
    bool        getEtatLumierres();

    /**
     * @enum ChampsSalle
     * @brief Définit les différents champs de la table Salle
     */
    enum ChampsSalle
    {
        TABLE_SALLE_NOM,               //!< Emplacement du nom
        TABLE_SALLE_DESCRIPTION,       //!< Emplacement de description
        TABLE_SALLE_INDICE_DE_CONFORT, //!< Emplacement de l'indice de confort
        TABLE_SALLE_ETAT_DES_FENETRES, //!< Emplacement d'état des fenêtres
        TABLE_SALLE_ETAT_DES_LUMIERES, //!< Emplacement d'état des lumieres
    };
};

#endif // SALLE_H
