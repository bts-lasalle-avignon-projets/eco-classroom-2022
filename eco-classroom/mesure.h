#ifndef MESURE_H
#define MESURE_H

/**
 * @file mesure.h
 * @brief Déclaration de la classe  Mesure
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

#include <QStringList>

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
    Mesure(QStringList mesure);
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

    enum ChampsTableMesure
    {
        ID,          //!< Emplacement de l'id de la mesure
        ID_SALLE,    //!< Emplacement de l'id de la salle
        TEMPERATURE, //!< Emplacement de la température dans la salle
        LUMINOSITE,  //!< Emplacement de la luminosité dans la salle
        HUMIDITE,    //!< Emplacement de l'humidité dans la salle
        CO2,         //!< Emplacement du taux de CO2 dans la salle
        HORODATAGE   //!< Emplacement de l'horodatage de la mesure
    };
};

#endif // MESURE_H
