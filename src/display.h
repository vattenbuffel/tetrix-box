#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "stdint.h"
#include <Arduino.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DISPLAY_W 128
#define DISPLAY_H 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)

void display_init();
Adafruit_SSD1306 *display_get();

#endif