#include "display.h"

void display_init(){
    Adafruit_SSD1306 display(DISPLAY_H, DISPLAY_W, &Wire, OLED_RESET);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    Serial.println(F("display inint success"));
}
