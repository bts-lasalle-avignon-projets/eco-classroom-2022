#ifndef MYLORA_H
#define MYLORA_H

#include <SPI.h>
#include <LoRa.h>

//#define LILYGO_TBeam_V1_1
#define HELTEC_LORA

#if defined(HELTEC_LORA)
#define LoRa_frequency      433E6
#define SCK     5    // GPIO5  -- SX127x's SCK
#define MISO    19   // GPIO19 -- SX127x's MISO
#define MOSI    27   // GPIO27 -- SX127x's MOSI
#define SS      18   // GPIO18 -- SX127x's CS
#define RST     14   // GPIO14 -- SX127x's RESET
#define DIO0    26   // GPIO26 -- SX127x's IRQ(Interrupt Request)
#define DIO1    33   // GPIO33 -- SX127x's IRQ(Interrupt Request)
#define DIO2    32   // ESP32 GPIO32 (Pin12) – SX1276 DIO2 (Pin10) not used by LMIC
#elif defined(LILYGO_TBeam_V1_0) || defined(LILYGO_TBeam_V1_1)
#define LoRa_frequency      868E6
#define SCK     5    // GPIO5  -- SX127x's SCK
#define MISO    19   // GPIO19 -- SX127x's MISO
#define MOSI    27   // GPIO27 -- SX127x's MOSI
#define SS      18   // GPIO18 -- SX127x's CS
#define RST     23   // GPIO14 -- SX127x's RESET
#define DIO0    26   // GPIO26 -- SX127x's IRQ(Interrupt Request)
#define DIO1    33   // GPIO33 -- SX127x's IRQ(Interrupt Request)
#define RADIO_BUSY_PIN              32

#define BUTTON_PIN                  38
#define BUTTON_PIN_MASK             GPIO_SEL_38
#define I2C_SDA                     21
#define I2C_SCL                     22
#define BOARD_LED                   4
#define LED_ON                      LOW
#define LED_OFF                     HIGH
#endif

//#define DEBUG_MYLORA

bool initialiserLora();
void sendMessage(const char *message);
void recevoirMessage();
void onReceive(int packetSize);
void recevoir();
void LoRa_rxMode();
void LoRa_txMode();

bool runEvery(unsigned long interval);

#endif
