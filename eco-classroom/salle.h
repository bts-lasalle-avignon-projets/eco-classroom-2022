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
 */
class Salle
{
  private:
    QStringList salle;       //!< les données d'une salle
    QString     id;          //!< l'id de la salle dans la table
    QString     nom;         //!< nom de la salle
    QString     lieu;        //!< lieu de la salle
    QString     description; //!< la description d'une salle
    int         surface;     //!< la surface d'une salle
    QString     code; //!< le code administrateur pour paramétrer une salle
    int         indiceConfort;    //!< l'indice de confort d'une salle
    QString libelleIndiceConfort; //!< le libelle associé à l'indice de confort
                                  //!< d'une salle
    QString
         libelleQualiteAir; //!< le libelle associé à l'indice de qualité d'air
    bool etatFenetres;      //!< l'état des fenêtres
    bool etatLumieres;      //!< l'état des lumières
    bool etatOccupation;    //!< l'état d'occupation de la salle

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
