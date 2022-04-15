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

typedef enum{
    dir_none,
    dir_up,
    dir_left, 
    dir_down,
    dir_right,
} game_dir_t;

typedef struct pos{
    int8_t x, y;
} pos_t;

void game_draw();
int32_t game_update(game_dir_t dir);
void game_init();
game_dir_t game_snake_dir_get();


#endif