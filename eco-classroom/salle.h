#ifndef SALLE_H
#define SALLE_H

/**
 * @file salle.h
 * @brief Déclaration de la classe Salle
 * @author Zeryouhi Mohamed Amine
 * @version 0.2
 */

#include <QString>
#include <QStringList>

/**
 * @class Salle
 * @brief Déclaration de la classe Salle
 */
class Salle
{
  private:
    QStringList salle;       //!< Les données d'une salle
    QString     id;          //!< L'id de la salle dans la table
    QString     nom;         //!< Nom de la salle
    QString     lieu;        //!< Lieu de la salle
    QString     description; //!< La description d'une salle
    int         surface;     //!< La surface d'une salle
    QString     code; //!< Le code administrateur pour paramétrer une salle
    int         indiceConfort;    //!< L'indice de confort d'une salle
    QString libelleIndiceConfort; //!< Le libelle associé à l'indice de confort
                                  //!< D'une salle
    QString
         libelleQualiteAir; //!< Le libelle associé à l'indice de qualité d'air
    bool etatFenetres;      //!< L'état des fenêtres
    bool etatLumieres;      //!< L'état des lumières
    bool etatOccupation;    //!< L'état d'occupation de la salle

  public:
    Salle();
    Salle(QStringList salle);
    ~Salle();

    QStringList getSalle() const;
    QString     getId() const;
    QString     getNom() const;
    QString     getLieu() const;
    QString     getDesciption() const;
    int         getSurface() const;
    QString     getCode() const;
    int         getIndiceConfort() const;
    QString     getLibelleIndiceConfort() const;
    QString     getLibelleQualiteAir() const;
    bool        getEtatFenetres() const;
    bool        getEtatLumierres() const;
    bool        getEtatOccupation() const;

    void setSalle(QStringList salle);

    /**
     * @enum ChampsTableSalle
     * @brief Définit les différents champs de la table Salle
     */
    enum ChampsTableSalle
    {
        ID,                        //!< Emplacement de l'id dans la table
        NOM,                       //!< Emplacement du nom
        LIEU,                      //!< Emplacement du lieu
        DESCRIPTION,               //!< Emplacement de description
        SUPERFICIE,                //!< Emplacement de la superficie
        CODE,                      //!< Emplacement du code d'administration
        INDICE_DE_CONFORT,         //!< Emplacement de l'indice de confort
        LIBELLE_INDICE_DE_CONFORT, //!< Emplacement du libelle de l'indice de
        LIBELLE_QUALITE_AIR, //!< Emplacement du libelle de la qualité d'air
        ETAT_DES_FENETRES,   //!< Emplacement d'état des fenêtres
        ETAT_DES_LUMIERES,   //!< Emplacement d'état des lumieres
        ETAT_OCCUPATION,     //!< Emplacement d'état d'occupation de la salle
    };
};

#endif // SALLE_H
