#include "game.h"
#include "display.h"
#include "serial_print.h"

static int8_t len;
static int16_t score;
static pos_t snake[25];
static pos_t food;

void game_draw() {
    Serial.println("game draw");

    Adafruit_SSD1306 *display = display_get();
    display->clearDisplay();

    // Draw food
    display->fillCircle(food.x*GAME_FOOD_SIZE, food.y*GAME_FOOD_SIZE, GAME_FOOD_SIZE, SSD1306_INVERSE);

    // Draw body
    for (typeof(len) i = 0; i < len; i++) {
        display->fillRoundRect(snake[i].x * GAME_SNAKE_PIECES_SIZE,
                               snake[i].y * GAME_SNAKE_PIECES_SIZE,
                               GAME_SNAKE_PIECES_SIZE, GAME_SNAKE_PIECES_SIZE,
                               1, SSD1306_INVERSE);
    }

    // Draw eye
    display->drawPixel(snake[0].x * GAME_SNAKE_PIECES_SIZE + 2,
                       snake[0].y * GAME_SNAKE_PIECES_SIZE + 1,
                       SSD1306_INVERSE);

    display->display();
    PRINTF("Game draw end\n", "");
}

int32_t game_update(game_dir_t dir);

void game_init() {
    PRINTF("Initializing game. Max snake len: %d\n", GAME_SNAKE_LEN_MAX);
    len = 2;
    score = 0;
    food.x = 10;
    food.y = 10;

    // memset(snake, 0, sizeof(snake));

    snake[0].x = 5;
    snake[0].y = 5;
    snake[1].x = 4;
    snake[1].y = 5;
}