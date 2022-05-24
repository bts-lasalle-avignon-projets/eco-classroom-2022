#ifndef MQTT_H
#define MQTT_H

#include <WiFi.h>
#include <PubSubClient.h>

extern const char* mqttServer;
extern const int mqttPort;
//extern const char* mqttUser;
//extern const char* mqttPassword;
//extern const char* topic;

extern WiFiClient espClient;
extern PubSubClient client;

bool connecterMQTT();
bool estConnecteMQTT();
void recevoirMessage(char* topic, byte* payload, unsigned int length);
bool publier(const char *topic, const char *message);
void souscrire(const char *topic);

#endif
