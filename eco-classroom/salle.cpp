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
Salle::Salle()
{
    qDebug() << Q_FUNC_INFO;
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
