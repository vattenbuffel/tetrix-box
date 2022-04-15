#include "display.h"

static Adafruit_SSD1306 display(DISPLAY_W, DISPLAY_H, &Wire, OLED_RESET);

void display_init() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    Serial.println(F("display inint success"));
}

Adafruit_SSD1306 *display_get() { return &display; }
