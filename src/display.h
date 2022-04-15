#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Arduino.h>
#include "stdint.h"

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define DISPLAY_W 128
#define DISPLAY_H 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)
extern Adafruit_SSD1306 display;

void display_init();





#endif