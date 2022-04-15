#include "game.h"
#include "display.h"
#include "serial_print.h"

static int8_t len;
static int16_t score;
static pos_t snake[25];
static pos_t food;
static game_dir_t snake_dir;

void game_draw() {
    Adafruit_SSD1306 *display = display_get();
    display->clearDisplay();

    // Draw food
    display->fillCircle(food.x * GAME_FOOD_SIZE, food.y * GAME_FOOD_SIZE,
                        GAME_FOOD_SIZE, SSD1306_INVERSE);

    // Draw body
    for (typeof(len) i = 0; i < len; i++) {
        display->fillRoundRect(snake[i].x * GAME_SNAKE_PIECES_SIZE,
                               snake[i].y * GAME_SNAKE_PIECES_SIZE,
                               GAME_SNAKE_PIECES_SIZE, GAME_SNAKE_PIECES_SIZE,
                               1, SSD1306_INVERSE);
    }

    // Draw eye
    // Do this based on dir
    display->drawPixel(snake[0].x * GAME_SNAKE_PIECES_SIZE + 2,
                       snake[0].y * GAME_SNAKE_PIECES_SIZE + 1,
                       SSD1306_INVERSE);

    display->display();
}

static void dir_dxdy(int *dx, int *dy, game_dir_t dir) {
    if (dir == dir_up) {
        *dx = 0;
        *dy = -1;
    } else if (dir == dir_right) {
        *dx = 1;
        *dy = 0;
    } else if (dir == dir_down) {
        *dx = 0;
        *dy = 1;
    } else if (dir == dir_left) {
        *dx = -1;
        *dy = 0;
    }
}

int32_t game_update(game_dir_t dir) {
    if (dir != dir_none) {
        snake_dir = dir;
    }

    // Move body
    int dx, dy;
    dir_dxdy(&dx, &dy, snake_dir);

    for (typeof(len) i = len; i > 0; i--) {
        snake[i] = snake[i-1];
    }
    snake[0].x += dx;
    snake[0].y += dy;

    // Check for death. Collision with body first, then sides
    bool death = false;
    for (typeof(len) i = 1; i < len; i++) {
        if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
            death = true;
            break;
        }
    }

    if (snake[0].x < 0) {
        death = true;
    } else if (snake[0].x > GAME_W) {
        death = true;
    } else if (snake[0].y < 0) {
        death = true;
    } else if (snake[0].y > GAME_H) {
        death = true;
    } 

    if (death) {
        PRINTF("You died with score: %d\n", score);
        return score;
    }

    return -1;
}

void game_init() {
    PRINTF("Initializing game. Max snake len: %d\n", GAME_SNAKE_LEN_MAX);
    food.x = 10;
    food.y = 10;

    len = 2;
    score = 0;
    snake[0].x = 5;
    snake[0].y = 5;
    snake[1].x = 4;
    snake[1].y = 5;
    snake_dir = dir_up;
}