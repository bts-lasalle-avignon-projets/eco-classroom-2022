#include <mywifi.h>
#include <Arduino.h>

WiFiClient espClient;

bool initialiserWiFi(const char *ssid, const char *password)
{
    int nbTentatives = 0;

    WiFi.begin(ssid, password);

    Serial.println("Connexion WiFi ...");
    while (WiFi.status() != WL_CONNECTED)
    {
        if(nbTentatives < 3)
        {
          delay(1000);
          nbTentatives++;
        }
        else
          return false;
    }

    Serial.println("Connecté au réseau WiFi !");
    return true;
}

bool estWiFiConnecte()
{
  return espClient.connected();
}
