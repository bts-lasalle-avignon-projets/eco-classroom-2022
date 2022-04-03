#include "salle.h"
#include <QDebug>

/**
 * @file salle.cpp
 * @brief Définition de la classe Salle
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @brief Constructeur par défaut de la classe Salle
 *
 * @fn Salle::Salle
 */
Salle::Salle() :
    id(""), nom(""), lieu(""), description(""), surface(0), code(""),
    indiceConfort(0), libelleIndiceConfort(""), libelleQualiteAir(""),
    etatFenetres(false), etatLumieres(false), etatOccupation(false)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Constructeur de la classe Salle
 *
 * @fn Salle::Salle
 * @param salle
 */
Salle::Salle(QStringList salle) : salle(salle)
{
    qDebug() << Q_FUNC_INFO << salle;
    id            = salle.at(ChampsTableSalle::ID);
    nom           = salle.at(ChampsTableSalle::NOM);
    lieu          = salle.at(ChampsTableSalle::LIEU);
    description   = salle.at(ChampsTableSalle::DESCRIPTION);
    surface       = salle.at(ChampsTableSalle::SUPERFICIE).toInt();
    code          = salle.at(ChampsTableSalle::CODE);
    indiceConfort = salle.at(ChampsTableSalle::INDICE_DE_CONFORT).toInt();
    libelleIndiceConfort =
      salle.at(ChampsTableSalle::LIBELLE_INDICE_DE_CONFORT);
    libelleQualiteAir = salle.at(ChampsTableSalle::LIBELLE_QUALITE_AIR);
    etatFenetres      = salle.at(ChampsTableSalle::ETAT_DES_FENETRES).toInt();
    etatLumieres      = salle.at(ChampsTableSalle::ETAT_DES_LUMIERES).toInt();
    etatOccupation    = salle.at(ChampsTableSalle::ETAT_OCCUPATION).toInt();
}

/**
 * @brief Destructeur de la classe Salle
 *
 * @fn Salle::~Salle
 * @details Libère les ressources
 */
Salle::~Salle()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Retourne les données de la salle
 * @return QStringList
 */
QStringList Salle::getSalle() const
{
    return salle;
}

/**
 * @fn Salle::getId
 * @return QString
 */
QString Salle::getId() const
{
    return id;
}

/**
 * @fn Salle::getNom
 * @return QString
 */
QString Salle::getNom() const
{
    return nom;
}

/**
 * @fn Salle::getLieu
 * @return
 */
QString Salle::getLieu() const
{
    return lieu;
}

/**
 * @fn Salle::getDesciption
 * @return
 */
QString Salle::getDesciption() const
{
    return description;
}

/**
 * @fn Salle::getSurface
 * @return
 */
int Salle::getSurface() const
{
    return surface;
}

/**
 * @brief Salle::getCode
 * @return
 */
QString Salle::getCode() const
{
    return code;
}

/**
 * @fn Salle::getIndiceConfort
 * @return int
 */
int Salle::getIndiceConfort() const
{
    return indiceConfort;
}

/**
 * @fn Salle::getLibelleIndiceConfort
 * @return
 */
QString Salle::getLibelleIndiceConfort() const
{
    return libelleIndiceConfort;
}

/**
 * @fn Salle::getLibelleQualiteAir
 * @return
 */
QString Salle::getLibelleQualiteAir() const
{
    return libelleQualiteAir;
}

/**
 * @fn Salle::getEtatFenetres
 * @return
 */
bool Salle::getEtatFenetres() const
{
    return etatFenetres;
}

/**
 * @fn Salle::getEtatLumierres
 * @return
 */
bool Salle::getEtatLumierres() const
{
    return etatLumieres;
}

/**
 * @fn Salle::getEtatOccupation
 * @return
 */
bool Salle::getEtatOccupation() const
{
    return etatOccupation;
}

/**
 * @brief
 *
 * @fn Salle::setSalle
 * @param salle
 */
void Salle::setSalle(QStringList salle)
{
    qDebug() << Q_FUNC_INFO << salle;
    this->salle   = salle;
    id            = salle.at(ChampsTableSalle::ID);
    nom           = salle.at(ChampsTableSalle::NOM);
    lieu          = salle.at(ChampsTableSalle::LIEU);
    description   = salle.at(ChampsTableSalle::DESCRIPTION);
    surface       = salle.at(ChampsTableSalle::SUPERFICIE).toInt();
    code          = salle.at(ChampsTableSalle::CODE);
    indiceConfort = salle.at(ChampsTableSalle::INDICE_DE_CONFORT).toInt();
    libelleIndiceConfort =
      salle.at(ChampsTableSalle::LIBELLE_INDICE_DE_CONFORT);
    libelleQualiteAir = salle.at(ChampsTableSalle::LIBELLE_QUALITE_AIR);
    etatFenetres      = salle.at(ChampsTableSalle::ETAT_DES_FENETRES).toInt();
    etatLumieres      = salle.at(ChampsTableSalle::ETAT_DES_LUMIERES).toInt();
    etatOccupation    = salle.at(ChampsTableSalle::ETAT_OCCUPATION).toInt();
}
