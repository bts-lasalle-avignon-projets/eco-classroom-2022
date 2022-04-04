#include <mylora.h>
#include <Arduino.h>

bool initialiserLora()
{
  #if defined(HELTEC_LORA)
  //SPI.begin(SCK, MISO, MOSI, SS); // cf. LoRa.cpp (bibliothèque LoRa ID 1167)
  LoRa.setPins(SS, RST, DIO0);
  // initialise 433 MHz
  if (!LoRa.begin(LoRa_frequency))
  {
    Serial.println("Erreur initialisation LoRa 433 MHz !");
    return false;
  }
  #elif defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
  //SPI.begin(SCK, MISO, MOSI, SS); // cf. LoRa.cpp (bibliothèque LoRa ID 1167)
  LoRa.setPins(SS, RST, DIO0);
  // initialise 868 MHz
  if (!LoRa.begin(LoRa_frequency))
  //if (!LoRa.begin(LoRa_frequency))
  {
    Serial.println("Erreur initialisation LoRa 868 MHz !");
    return false;
  }
  #endif

  // Les modules LoRa écoutent tous les paquets dans sa plage.
  // Pour vous assurer de ne recevoir que les paquets de votre expéditeur,
  // vous pouvez définir un mot de synchronisation (compris entre 0 et 0xFF).
  //LoRa.setSyncWord(0xF3); // ranges from 0-0xFF, default 0x34, see API docs

  #ifdef DEBUG_MYLORA
  LoRa.dumpRegisters(Serial);
  #endif

  Serial.println("LoRa Node ok !");

  return true;
}

void sendMessage(const char *message)
{
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
}

void recevoirMessage()
{
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    Serial.print("Paquet recu '");

    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }

    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    //Serial.println("Snr: " + String(LoRa.packetSnr()));
  }
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
