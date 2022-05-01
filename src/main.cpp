#include "button.h"
#include "display.h"
#include "game.h"
#include "serial_print.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

typedef uint8_t state_t;
#define STATE_INIT 0
#define STATE_PLAYING 1
#define STATE_DEAD 2

#define BUTTON_LEFT_GPIO 6
#define BUTTON_RIGHT_GPIO 7

button_t button_left, button_right;
static state_t state = STATE_INIT;
static int16_t score;
static char score_s[3];
uint32_t game_run_last_ms;

void game_start() {
    game_init();
    state = STATE_PLAYING;
    game_run_last_ms = millis();
}

void setup() {
    Serial.begin(115200);
    Serial.println("Hello wrodl\n");

    button_init(&button_left, BUTTON_LEFT_GPIO);
    button_init(&button_right, BUTTON_RIGHT_GPIO);
    display_init();

    game_start();
}

game_dir_t dir_get() {
    game_dir_t snake_dir = game_snake_dir_get();

    if (BUTTON_PRESSED(&button_right)) {
        return (game_dir_t)((snake_dir + 1) % 4);
    } else if (BUTTON_PRESSED(&button_left)) {
        return (game_dir_t)(snake_dir-1==-1 ? 3 : snake_dir-1);
    }
    return DIR_NONE;
}

void state_loop() {
    if (state == STATE_PLAYING) {
        score = game_update();
        if (score != -1) {
            state = STATE_DEAD;
            snprintf(score_s, sizeof(score_s), "%d", score);
            // game_start();
        }
        game_draw();

    } else if (state == STATE_DEAD) {
        Adafruit_SSD1306 *display = display_get();
        display->clearDisplay();
        display->setTextSize(2);              // Normal 1:1 pixel scale
        display->setTextColor(SSD1306_WHITE); // Draw white text
        display->setCursor(0, 10);             // Start at top-left corner
        display->print("You died.\nScore: ");
        display->print(score_s);
        display->display();

        // Restart game
        if (BUTTON_VAL_CUR_GET(&button_left) == 0 && BUTTON_VAL_CUR_GET(&button_right) == 0) {
            Serial.println(F("Restarting game"));
            game_start();
        }
    } else {
        Serial.print(F("Invalid state"));
        Serial.println(state);
        for (;;)
            delay(100);
    }
}

void loop() {
    button_update(&button_left);
    button_update(&button_right);

    if (state == STATE_PLAYING && BUTTON_PRESSED(&button_right) || BUTTON_PRESSED(&button_left)) {
        game_dir_t new_dir = dir_get();
        if (new_dir != DIR_NONE) {
            game_snake_dir_set(new_dir);
        }
    }

    if (millis() - game_run_last_ms > 50) {
        state_loop();
        game_run_last_ms = millis();
    }
}
