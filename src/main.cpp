#include "button.h"
#include "display.h"
#include "game.h"
#include "serial_print.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

/* TODO: Massive compression of everything. Use bits to store board and shit
    Replace enums with defs when possible
 */

typedef enum {
    state_init,
    state_playing,
    state_dead,
} state_t;

#define BUTTON_LEFT_GPIO 6
#define BUTTON_RIGHT_GPIO 7

button_t button_left, button_right;
static state_t state = state_init;
static int32_t score;
static char score_s[3];
uint32_t game_run_last_ms;

void game_start() {
    game_init();
    state = state_playing;
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
    if (state == state_playing) {
        score = game_update();
        if (score != -1) {
            state = state_dead;
            snprintf(score_s, sizeof(score_s), "%ld", score);
            game_start();
        }
        game_draw();

    } else if (state == state_dead) {
        Adafruit_SSD1306 *display = display_get();
        display->clearDisplay();
        display->setTextSize(1);              // Normal 1:1 pixel scale
        display->setTextColor(SSD1306_WHITE); // Draw white text
        display->setCursor(0, 0);             // Start at top-left corner
        display->print("You died.\n Score: ");
        display->print(score_s);
        display->display();

        // Restart game
        if (BUTTON_VAL_CUR_GET(&button_left) == 0 && BUTTON_VAL_CUR_GET(&button_right) == 0) {
            PRINTF("%s Restarting game\n", __func__);
            game_start();
        }
    } else {
        serial_printf(Serial, "%s invalid state: %d\n", __func__, state);
        for (;;)
            delay(100);
    }
}

void loop() {
    button_update(&button_left);
    button_update(&button_right);

    if (BUTTON_PRESSED(&button_right) || BUTTON_PRESSED(&button_left)) {
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
