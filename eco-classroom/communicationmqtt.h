#ifndef COMMUNICATIONMQTT_H
#define COMMUNICATIONMQTT_H

#include <QObject>

/**
 * @file communicationmqtt.h
 * @brief Déclaration de la classe CommunicationMQTT
 * @author Zeryouhi Mohamed Amine
 * @version 0.1
 */

/**
 * @class CommunicationMQTT
 * @brief Déclaration de la classe CommunicationMQTT
 * @details
 */
class CommunicationMQTT : public QObject
{
    Q_OBJECT
  private:
  public:
    CommunicationMQTT(QObject* parent = nullptr);
    virtual ~CommunicationMQTT();

  public slots:
  signals:
};

#endif // COMMUNICATIONMQTT_H
