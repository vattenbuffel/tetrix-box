#include "game.h"
#include "serial_print.h"
// #include "display.h"

static int8_t len;
static int16_t score;
// static uint8_t board[DISPLAY_H/GAME_SNAKE_PIECES_SIZE][DISPLAY_W/GAME_SNAKE_PIECES_SIZE];
static pos_t snake[GAME_SNAKE_LEN_MAX];


void game_draw(){
    // display.clearDisplay();

    // display.fillCircle(50, 50, 10, SSD1306_INVERSE);
    // display.display();


}

int32_t game_update(game_dir_t dir);

void game_init(){
    PRINTF("Initializing game. Max snake len: %d\n", GAME_SNAKE_LEN_MAX);
    len = 2;
    score =  0;
    // memset(snake, 0, sizeof(snake));

    snake[0].x = 5;
    snake[0].y = 5;
    snake[1].x = 5;
    snake[1].y = 4;
}