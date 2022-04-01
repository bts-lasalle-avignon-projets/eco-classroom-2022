#include "mesure.h"
#include <QDebug>

/**
 * @file mesure.cpp
 * @brief Définition de la classe Mesure
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @brief Constructeur par défaut de la classe Mesure
 *
 * @fn Mesure::Mesure
 */

Mesure::Mesure() : temperature(0), humidite(0), co2(0), luminosite(0.)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Destructeur de la classe Mesure
 *
 * @fn Mesure::~Mesure
 * @details Libère les ressources
 */
Mesure::~Mesure()
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Retourne les données de la mesure
 * @return
 */
int Mesure::getTemperature() const
{
    return temperature;
}

/**
 * @brief Mesure::getHumidite
 * @return
 */
int Mesure::getHumidite() const
{
    return humidite;
}

/**
 * @brief Mesure::getCo2
 * @return
 */
int Mesure::getCo2() const
{
    return co2;
}

/**
 * @brief Mesure::getLuminosite
 * @return
 */
double Mesure::getLuminosite() const
{
    return luminosite;
}
