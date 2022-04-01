#ifndef MESURE_H
#define MESURE_H

/**
 * @file mesure.h
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
    double temperature; //!< la température dans la salle
    int    humidite;    //!< l'humidité dans la salle
    int    co2;         //!< le taux de CO2 dans la salle
    int    luminosite;  //!< la luminosite dans la salle

  public:
    Mesure();
    Mesure(double temperature, int humidite, int co2, int luminosite);
    ~Mesure();

    double getTemperature() const;
    int    getHumidite() const;
    int    getCo2() const;
    int    getLuminosite() const;

    void setTemperature(double temperature);
    void setHumidite(int humidite);
    void setCo2(int co2);
    void setLuminosite(int luminosite);
};

#endif // MESURE_H
