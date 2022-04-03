#include "communicationmqtt.h"
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

/**
 * @file communicationmqtt.cpp
 * @brief  Définition de la classe CommunicationMQTT
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @brief Constructeur de la classe CommunicationMQTT
 *
 * @fn CommunicationMQTT::CommunicationMQTT
 * @param parent L'adresse de l'objet parent
 */
CommunicationMQTT::CommunicationMQTT(QObject* parent) : QObject(parent)
{
    qDebug() << Q_FUNC_INFO;
    client = new QMqttClient(this);
    client->setHostname(BROKER_MQTT_HOSTNAME);
    client->setPort(BROKER_MQTT_PORT);

    connect(client, SIGNAL(connected()), this, SLOT(connecte()));
    connect(client, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(client,
            SIGNAL(messageReceived(const QByteArray&, const QMqttTopicName&)),
            this,
            SLOT(recevoir(const QByteArray&, const QMqttTopicName&)));

    connecter();
}

/**
 * @brief Destructeur de la classe CommunicationMQTT
 *
 * @fn CommunicationMQTT::~CommunicationMQTT
 * @details Libère les ressources
 */
CommunicationMQTT::~CommunicationMQTT()
{
    desabonner(QString(TOPIC_RACINE) + QString("/#")); // tous les sujets
    deconnecter();
    qDebug() << Q_FUNC_INFO;
}

void CommunicationMQTT::connecter()
{
    qDebug() << Q_FUNC_INFO;
    client->connectToHost();
}

void CommunicationMQTT::abonner(QString topic)
{
    qDebug() << Q_FUNC_INFO;
    QMqttSubscription* subscription = client->subscribe(topic);
    if(!subscription)
    {
        qDebug() << Q_FUNC_INFO << "erreur subscribe";
        return;
    }
}

void CommunicationMQTT::desabonner(QString topic)
{
    qDebug() << Q_FUNC_INFO;
    client->unsubscribe(topic);
}

void CommunicationMQTT::deconnecter()
{
    qDebug() << Q_FUNC_INFO;
    client->disconnectFromHost();
}

void CommunicationMQTT::recevoir(const QByteArray&     message,
                                 const QMqttTopicName& topic)
{
    qDebug() << Q_FUNC_INFO << QDateTime::currentDateTime().toString()
             << topic.name() << message;
    qDebug() << Q_FUNC_INFO << message.toInt() << message.toDouble();

    QStringList champs = topic.name().split("/");
    for(int i = 0; i < champs.size(); ++i)
    {
        qDebug() << Q_FUNC_INFO << champs.at(i);
    }
}

void CommunicationMQTT::connecte()
{
    qDebug() << Q_FUNC_INFO;
    abonner("salles/#");
}

void CommunicationMQTT::deconnecte()
{
    qDebug() << Q_FUNC_INFO;
}
