#include <mywifi.h>
#include <ui.h>
#include <mqtt.h>
#include <mylora.h>

#define DEBUG

// OLED 8 lignes x 16 colonnes
// Linge de 0 à 7
#define LIGNE_TITRE 0
#define LIGNE_STATUS_WIFI  2
#define LIGNE_STATUS_LORA  3
#define LIGNE_STATUS_MQTT  4
#define LIGNE_DATA_LORA  6
#define LIGNE_DATA_MQTT  7

const char *ssid = "btssn";
const char *password = "bts-sn84";
const char* mqttServer = "192.168.52.7";
//const char* topic = "salles";
String topicPrincipal = "salles";
String topic = "";

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  #ifdef DEBUG
  Serial.println("LoRa Gateway");
  Serial.print("ssid : ");
  Serial.print(ssid);
  Serial.println("");
  Serial.print("serveur mqqt : ");
  Serial.print(mqttServer);
  Serial.println("");
  Serial.print("topic mqqt : ");
  Serial.print(topic);
  Serial.println("");
  #endif

  initialiserOLED();
  ui.drawString(0, LIGNE_TITRE, "* LoRa Gateway *");

  if(initialiserWiFi(ssid, password))
  {
    ui.drawString(0, LIGNE_STATUS_WIFI, "Wifi ok");
    if(connecterMQTT())
    {
      ui.drawString(0, LIGNE_STATUS_MQTT, "Broker ok");
    }
    else
    {
      ui.drawString(0, LIGNE_STATUS_MQTT, "Erreur Broker !");
    }
  }
  else
  {
    ui.drawString(0, LIGNE_STATUS_WIFI, "Erreur Wifi !");
  }

  if(initialiserLora())
  {
    ui.drawString(0, LIGNE_STATUS_LORA, "LoRa ok");
  }
  else
  {
    ui.drawString(0, LIGNE_STATUS_LORA, "Erreur LoRa !");
  }
}

void loop()
{
  delay(50);
  client.loop();

  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {    
    String messageLoRa = "";
    while (LoRa.available())
    {
      messageLoRa += (char)LoRa.read();
    }
    
    #ifdef DEBUG
    Serial.print("Paquet recu : ");
    Serial.print(messageLoRa);
    Serial.println("");
    Serial.print("   * RSSI : " + String(LoRa.packetRssi()));
    Serial.println(" dBm");
    Serial.print("   * SNR  : " + String(LoRa.packetSnr()));
    Serial.println(" dB");
    #endif

    //String messageUI = "LoRa <- " + messageLoRa;
    String messageUI = "LoRa <- " + messageLoRa.substring(0, messageLoRa.indexOf("/"));
    ui.clearLine(LIGNE_DATA_LORA);
    ui.drawString(0, LIGNE_DATA_LORA, messageUI.c_str());

    String sousTopic;
    int position = messageLoRa.lastIndexOf("/");
    if(position != -1)
    {
      sousTopic = messageLoRa.substring(0, position);
      messageLoRa.remove(0, position+1);
    }

    String messageMQTT = messageLoRa;
    if(sousTopic.length() > 0)
        topic = topicPrincipal + String("/") + sousTopic;
    #ifdef DEBUG
    Serial.print("Topic : ");
    Serial.println(topic);
    Serial.print("Message MQTT envoyé : ");
    Serial.println(messageMQTT);
    #endif
    messageUI = "MQTT -> " + messageMQTT;
    ui.clearLine(LIGNE_DATA_MQTT);
    ui.drawString(0, LIGNE_DATA_MQTT, messageUI.c_str());
    if(estConnecteMQTT())
    {      
      publier(topic.c_str(), messageMQTT.c_str());      
    }
  }
}
