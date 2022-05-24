#ifndef COMMUNICATIONMQTT_H
#define COMMUNICATIONMQTT_H

#include <QObject>
#include <QtMqtt/QtMqtt>
#include <QtMqtt/QMqttClient>

/**
 * @file communicationmqtt.h
 * @brief Déclaration de la classe CommunicationMQTT
 * @author Zeryouhi Mohamed Amine
 * @version 0.2
 */

#define BROKER_MQTT_HOSTNAME "192.168.52.7"
#define BROKER_MQTT_PORT     1883

#define TOPIC_RACINE "salles"
/**
 * @class CommunicationMQTT
 * @brief Déclaration de la classe CommunicationMQTT
 * @details
 */
class CommunicationMQTT : public QObject
{
    Q_OBJECT
  private:
    QMqttClient* client; //!< le client MQTT

  public:
    CommunicationMQTT(QObject* parent = nullptr);
    virtual ~CommunicationMQTT();

    enum ChampsTopic
    {
        RACINE,     //!< La racine du topic (égal à salles)
        NOM_SALLE,  //!< Le nom de la salle dont provient la donnée
        TYPE_DONNEE //!< Le type de données (température, co2, etc...)
    };

  public slots:
    void connecter();
    void deconnecter();
    void abonner(QString topic);
    void desabonner(QString topic);
    void recevoir(const QByteArray& message, const QMqttTopicName& topic);
    void connecte();
    void deconnecte();

  signals:
    void nouvelleDonnee(QString nomSalle, QString typeDonnee, QString donnee);
};

#endif // COMMUNICATIONMQTT_H
