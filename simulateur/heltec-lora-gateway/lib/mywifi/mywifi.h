#ifndef MYWIFI_H
#define MYWIFI_H

#include <WiFi.h>

extern WiFiClient espClient;

bool initialiserWiFi(const char *ssid, const char *password);

#endif
