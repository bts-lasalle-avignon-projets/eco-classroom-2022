#ifndef UI_H
#define UI_H

#include <U8x8lib.h>

typedef U8X8_SSD1306_128X64_NONAME_SW_I2C Display;

extern Display ui;

void initialiserOLED();

#endif
