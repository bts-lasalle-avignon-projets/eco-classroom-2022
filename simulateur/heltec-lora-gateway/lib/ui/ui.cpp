#include <ui.h>

Display ui(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);

void initialiserOLED()
{
  ui.begin();
  ui.setFont(u8x8_font_chroma48medium8_r);
  ui.setFlipMode(1);
}
