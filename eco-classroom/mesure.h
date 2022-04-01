#ifndef MESURE_H
#define MESURE_H

/**
 * @file mesure
 * @brief Déclaration de la classe  Mesure
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @class Mesure
 * @brief Déclaration de la classe Mesure
 */

class Mesure
{
  private:
    int    temperature; //!< la temperature d'une salle
    int    humidite;    //!< humidite du salle
    int    co2;         //!< le taux de co2 dans une salle
    double luminosite;  //!< la luminosite d'une salle

  public:
    Mesure();
    ~Mesure();

    int    getTemperature() const;
    int    getHumidite() const;
    int    getCo2() const;
    double getLuminosite() const;

#endif // MESURE_H
