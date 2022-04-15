#include "button.h"
#include "display.h"
#include "game.h"
#include "serial_print.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

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
static char score_s[8];

void game_start(){
    game_init();
    state = state_playing;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Hello wrodl\n");

    button_init(&button_left, BUTTON_LEFT_GPIO);
    button_init(&button_right, BUTTON_RIGHT_GPIO);
    display_init();

	game_start();
}

game_dir_t dir_get(){
	bool button_right_pressed = button_right.val_curr == 0 && button_right.val_prev == 1;
	bool button_left_pressed = button_left.val_curr == 0 && button_left.val_prev == 1;
	game_dir_t snake_dir = game_snake_dir_get();

	if(button_right_pressed){
		PRINTF("Button right pressed\n", NULL);
		if(snake_dir == dir_up){
			return dir_right;
		}
		return (game_dir_t) (snake_dir - 1);

	} else if(button_left_pressed){
		if(snake_dir == dir_right){
			return dir_up;
		}
		return (game_dir_t) (snake_dir + 1);
	}

	return dir_none;
}


void loop() {
	button_update(&button_left);
	button_update(&button_right);
	// if (button_left.val_curr != button_left.val_prev) {
	// 	serial_printf(Serial, "%l: left old_value: %d, new value: %d\n",
	// 					millis(), button_left.val_prev, button_left.val_curr);
	// }
	// if (button_right.val_curr != button_right.val_prev) {
	// 	serial_printf(Serial, "%l: right old_value: %d, new value: %d\n",
	// 					millis(), button_right.val_prev, button_right.val_curr);
	// }

    if (state == state_playing) {
		game_dir_t dir = dir_get();
		PRINTF("Updated dir: %d\n", dir);
        score = game_update(dir);
        if (score != -1) {
            state = state_dead;
			snprintf(score_s, sizeof(score_s), "%ld", score);
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
		if(button_left.val_curr == 0 && button_right.val_curr == 0){
			PRINTF("%s Restarting game\n", __func__);
			game_start();
		}
    }

    delay(50);
}
