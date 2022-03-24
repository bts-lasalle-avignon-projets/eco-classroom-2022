#include "communicationmqtt.h"
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
}

/**
 * @brief Destructeur de la classe CommunicationMQTT
 *
 * @fn CommunicationMQTT::~CommunicationMQTT
 * @details Libère les ressources
 */
CommunicationMQTT::~CommunicationMQTT()
{
    qDebug() << Q_FUNC_INFO;
}
