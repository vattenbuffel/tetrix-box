#ifndef GAME_H_
#define GAME_H_

#include <Arduino.h>
#include "stdint.h"
#include "display.h"

#define GAME_FOOD_SIZE 5
#define GAME_SNAKE_PIECES_SIZE 5
#define GAME_SNAKE_LEN_MAX (DISPLAY_W*DISPLAY_H / sq(GAME_SNAKE_PIECES_SIZE))

typedef enum{
    none,
    left, 
    right,
} game_dir_t;

typedef struct pos{
    int8_t x, y;
} pos_t;

void game_draw();
int32_t game_update(game_dir_t dir);
void game_init();


#endif