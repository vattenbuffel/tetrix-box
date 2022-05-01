#ifndef GAME_H_
#define GAME_H_

#include <Arduino.h>
#include "stdint.h"
#include "display.h"

#define GAME_FOOD_SIZE 5
#define GAME_SNAKE_PIECES_SIZE 5
#define GAME_SNAKE_LEN_MAX (DISPLAY_W*DISPLAY_H / sq(GAME_SNAKE_PIECES_SIZE))
#define GAME_W (DISPLAY_W / GAME_SNAKE_PIECES_SIZE)
#define GAME_H (DISPLAY_H / GAME_SNAKE_PIECES_SIZE)
#define GAME_START_LEN 2


typedef uint8_t game_dir_t;
#define DIR_DOWN 0
#define DIR_LEFT 1
#define DIR_UP 2
#define DIR_RIGHT 3
#define DIR_NONE 4



typedef struct pos{
    int8_t x, y;
} pos_t;

void game_draw();
int16_t game_update();
void game_init();
game_dir_t game_snake_dir_get();
void game_snake_dir_set(game_dir_t dir);


#endif