#ifndef UI_H
#define UI_H

#include <U8x8lib.h>

//#define LILYGO_OLED
#define HELTEC_OLED

#if defined(HELTEC_OLED)
#define OLED_I2C_ADDR 0x3C
#define OLED_RESET    16
#define OLED_SDA      4
#define OLED_SCL      15
#elif defined(LILYGO_OLED)
#define OLED_I2C_ADDR 0x3C
#define OLED_RESET    16
#define OLED_SDA      21
#define OLED_SCL      22
#endif

typedef U8X8_SSD1306_128X64_NONAME_SW_I2C Display;

extern Display ui;

void initialiserOLED();

#endif
