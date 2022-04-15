#include "button.h"
#include "display.h"
#include "game.h"
#include "serial_print.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#define BUTTON_LEFT_GPIO 6
#define BUTTON_RIGHT_GPIO 7

button_t button_left, button_right;

void setup() {
    Serial.begin(115200);
    Serial.println("Hello wrodl\n");

    button_init(&button_left, BUTTON_LEFT_GPIO);
    display_init();

    game_init();
    game_draw();
}

void loop() {
    button_update(&button_left);
    if (button_left.val_curr != button_left.val_prev) {
        serial_printf(Serial, "%l: old_value: %d, new value: %d\n", millis(),
                      button_left.val_prev, button_left.val_curr);
    }
    delay(10);
}
