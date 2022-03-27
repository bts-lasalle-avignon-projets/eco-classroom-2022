#ifndef SALLE_H
#define SALLE_H

/**
 * @file salle.h
 * @brief Déclaration de la classe Salle
 * @author
 * @version 0.1
 */

/**
 * @class Salle
 * @brief Déclaration de la classe Salle
 * @details
 */
class Salle
{
  private:
  public:
    Salle();
    ~Salle();
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
        //!< confort
        LIBELLE_QUALITE_AIR, //!< Emplacement du libelle de la qualité d'air
        ETAT_DES_FENETRES,   //!< Emplacement d'état des fenêtres
        ETAT_DES_LUMIERES,   //!< Emplacement d'état des lumieres
        ETAT_OCCUPATION,     //!< Emplacement d'état d'occupation de la salle
    };
};

#endif // SALLE_H
