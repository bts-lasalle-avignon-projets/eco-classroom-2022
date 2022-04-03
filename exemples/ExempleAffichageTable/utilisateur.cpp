#include "utilisateur.h"
#include <QDebug>

/**
 * @file utilisateur.cpp
 * @brief Définition de la classe Utilisateur
 * @author Thierry Vaira
 * @version 1.0
 */

/**
 * @brief Constructeur de la classe Utilisateur
 * @details Initialise un objet Utilisateur
 * @param parent
 */
Utilisateur::Utilisateur(QObject* parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    idUtilisateur = "";
    nom           = "";
    prenom        = "";
    identifiant   = "";
    code          = "";
}

/**
 * @brief Constructeur de la classe Utilisateur
 * @details Initialise un objet Utilisateur
 * @param utilisateur les données d'un utilisateur
 * @param parent
 */
Utilisateur::Utilisateur(QStringList utilisateur, QObject* parent) :
    QObject(parent), utilisateur(utilisateur)
{
    qDebug() << Q_FUNC_INFO << utilisateur;
    idUtilisateur = utilisateur.at(TABLE_UTILISATEUR_ID_UTILISATEUR);
    nom           = utilisateur.at(TABLE_UTILISATEUR_NOM);
    prenom        = utilisateur.at(TABLE_UTILISATEUR_PRENOM);
    identifiant   = utilisateur.at(TABLE_UTILISATEUR_IDENTIFIANT);
    code          = utilisateur.at(TABLE_UTILISATEUR_CODE);
}

/**
 * @brief Destructeur de la classe Utilisateur
 * @fn Utilisateur::~Utilisateur()
 * @details Détruit un objet Utilisateur
 */
Utilisateur::~Utilisateur()
{
}

/**
 * @brief Retourne les données de l'utilisateur
 * @return QStringList
 */
QStringList Utilisateur::getUtilisateur()
{
    return utilisateur;
}

/**
 * @brief Retourne l'id de l'utilisateur
 * @return QString idUtilisateur
 */
QString Utilisateur::getIdUtilisateur()
{
    return idUtilisateur;
}

/**
 * @brief Retourne le nom de l'utilisateur
 * @return QString nom
 */
QString Utilisateur::getNom()
{
    return nom;
}

/**
 * @brief Retourne le prénom de l'utilisateur
 * @return QString prenom
 */
QString Utilisateur::getPrenom()
{
    return prenom;
}

/**
 * @brief Retourne l'identifiant de l'utilisateur
 * @return QString identifiant
 */
QString Utilisateur::getIdentifiant()
{
    return identifiant;
}

/**
 * @brief Retourne le code de l'utilisateur
 * @return QString code
 */
QString Utilisateur::getCode()
{
    return code;
}
