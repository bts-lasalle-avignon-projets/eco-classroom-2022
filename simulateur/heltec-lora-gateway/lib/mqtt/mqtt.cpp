#include <mqtt.h>
#include <Arduino.h>

const int mqttPort = 1883;
//const char* mqttUser = "yourMQTTuser";
//const char* mqttPassword = "yourMQTTpassword";

PubSubClient client(espClient);

bool connecterMQTT()
{
  int nbTentatives = 0;
  client.setServer(mqttServer, mqttPort);
  client.setCallback(recevoirMessage);

  while (!client.connected())
  {
    Serial.println("Connexion au broker ...");

    if (client.connect(""))
    {
      Serial.println("Connecté au broker !");
      return true;
    }
    else
    {
      Serial.print("Erreur : ");
      Serial.print(client.state());
      Serial.println("");
      if(nbTentatives < 3)
      {
        delay(2000);
        nbTentatives++;
      }
      else
        return false;
    }
  }
  return false;
}

bool estConnecteMQTT()
{
  return client.connected();
}

void recevoirMessage(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

bool publier(const char *topic, const char *message)
{
  return client.publish(topic, message);
}

void souscrire(const char *topic)
{
  client.subscribe(topic);
}
