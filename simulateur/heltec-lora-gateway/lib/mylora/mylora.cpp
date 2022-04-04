#include <mylora.h>
#include <Arduino.h>

bool initialiserLora()
{
  //SPI.begin(SCK, MISO, MOSI, SS); // cf. LoRa.cpp (bibliothèque LoRa ID 1167)
  LoRa.setPins(SS, RST, DIO0);
  // initialise 433 MHz
  if (!LoRa.begin(BAND))
  {
    Serial.println("Erreur initialisation LoRa !");
    //while (true); // boucle infinie !
    return false;
  }

  // Les modules LoRa écoutent tous les paquets dans sa plage.
  // Pour vous assurer de ne recevoir que les paquets de votre expéditeur,
  // vous pouvez définir un mot de synchronisation (compris entre 0 et 0xFF).
  //LoRa.setSyncWord(0xF3); // ranges from 0-0xFF, default 0x34, see API docs

  #ifdef DEBUG_MYLORA
  LoRa.dumpRegisters(Serial);
  #endif

  Serial.println("LoRa initialisé !");
  return true;
}

void sendMessage(const char *message)
{
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  //LoRa.endPacket(true); // true = async / non-blocking mode
}

bool aMessageDisponible()
{
  return LoRa.parsePacket();
}

String recevoirMessage()
{
  String messageLoRa = "";
  int packetSize = LoRa.parsePacket();

  messageLoRa += packetSize;
  Serial.print("LoRa '");
  Serial.print(packetSize);
  Serial.println("'");

  if (packetSize)
  {
    Serial.print("Paquet recu '");

    while (LoRa.available())
    {
      messageLoRa += (char)LoRa.read();
    }
    Serial.print(messageLoRa);
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    //Serial.println("Snr: " + String(LoRa.packetSnr()));
  }

  return messageLoRa;
}

void onReceive(int packetSize)
{
  if (packetSize == 0) return; // if there's no packet, return

  Serial.print("Paquet recu '");

  for (int i = 0; i < packetSize; i++)
  {
    Serial.print((char)LoRa.read());
  }

  Serial.print("' with RSSI ");
  Serial.println(LoRa.packetRssi());
}

void recevoir()
{
  LoRa.onReceive(onReceive);
  LoRa.receive();
}

void LoRa_rxMode()
{
  LoRa.receive();                       // set receive mode
}

void LoRa_txMode()
{
  LoRa.idle();                          // set standby mode
}

bool runEvery(unsigned long interval)
{
  static unsigned long previousMillis = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    return true;
  }

  return false;
}
