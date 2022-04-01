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
Mesure::Mesure() : temperature(0.), humidite(0), co2(0), luminosite(0)
{
    qDebug() << Q_FUNC_INFO;
}

/**
 * @brief Mesure::Mesure
 *
 * @brief Constructeur d'initialisation de la classe Mesure
 * @param temperature
 * @param humidite
 * @param co2
 * @param luminosite
 */
Mesure::Mesure(double temperature, int humidite, int co2, int luminosite) :
    temperature(temperature), humidite(humidite), co2(co2),
    luminosite(luminosite)
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
 * @brief Retourne la température dans la salle
 * @return
 */
double Mesure::getTemperature() const
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
int Mesure::getLuminosite() const
{
    return luminosite;
}

/**
 * @brief Mesure::setTemperature
 * @param temperature
 */
void Mesure::setTemperature(double temperature)
{
    this->temperature = temperature;
}

/**
 * @brief Mesure::setHumidite
 * @param humidite
 */
void Mesure::setHumidite(int humidite)
{
    this->humidite = humidite;
}

/**
 * @brief Mesure::setCo2
 * @param co2
 */
void Mesure::setCo2(int co2)
{
    this->co2 = co2;
}

/**
 * @brief Mesure::setLuminosite
 * @param luminosite
 */
void Mesure::setLuminosite(int luminosite)
{
    this->luminosite = luminosite;
}
