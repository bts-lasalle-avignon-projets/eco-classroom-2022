#include <ui.h>

Display ui(/* clock=*/ OLED_SCL, /* data=*/ OLED_SDA, /* reset=*/ OLED_RESET);

void initialiserOLED()
{
  ui.begin();
  ui.setFont(u8x8_font_chroma48medium8_r);
  ui.setFlipMode(1);
}
