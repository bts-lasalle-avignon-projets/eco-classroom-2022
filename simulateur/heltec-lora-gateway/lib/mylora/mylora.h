#ifndef MYLORA_H
#define MYLORA_H

#include <SPI.h>
#include <LoRa.h>

#define SCK     5    // GPIO5  -- SX127x's SCK
#define MISO    19   // GPIO19 -- SX127x's MISO
#define MOSI    27   // GPIO27 -- SX127x's MOSI
#define SS      18   // GPIO18 -- SX127x's CS
#define RST     14   // GPIO14 -- SX127x's RESET
#define DIO0    26   // GPIO26 -- SX127x's IRQ(Interrupt Request)
#define DIO1    33   // GPIO33 -- SX127x's IRQ(Interrupt Request)
#define DIO2    32   // ESP32 GPIO32 (Pin12) – SX1276 DIO2 (Pin10) not used by LMIC

#define BAND 433E6
#define PABOOST true

//#define DEBUG_MYLORA

bool initialiserLora();
void sendMessage(const char *message);
bool aMessageDisponible();
String recevoirMessage();
void onReceive(int packetSize);
void recevoir();
void LoRa_rxMode();
void LoRa_txMode();

bool runEvery(unsigned long interval);

#endif
