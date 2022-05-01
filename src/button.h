#ifndef BUTTON_H_
#define BUTTON_H_

#include "stdint.h"
#include <Arduino.h>

#define BUTTON_HOLD_MS 50

#define BUTTON_VAL_CUR_GET(button) (((button)->data >> 0) & 0b1)
#define BUTTON_VAL_PREV_GET(button) (((button)->data >> 1) & 0b1)
#define BUTTON_VAL_TEMP_GET(button) (((button)->data >> 2) & 0b1)
#define BUTTON_CHANGE_ONGOING_GET(button) (((button)->data >> 3) & 0b1)

#define BUTTON_VAL_CUR_SET(button, val) (((button)->data & 0b11111110) | (val<<0))
#define BUTTON_VAL_PREV_SET(button, val) (((button)->data & 0b11111101) | (val<<1))
#define BUTTON_VAL_TEMP_SET(button, val) (((button)->data & 0b11111011) | (val<<2))
#define BUTTON_CHANGE_ONGOING_SET(button, val) (((button)->data & 0b11110111) | (val<<3))

#define BUTTON_PRESSED(button) (BUTTON_VAL_CUR_GET(button) == 0 && BUTTON_VAL_PREV_GET(button) == 1)


// Maybe store time_val_change as uint8_t time[3]. This would only save 1 byte though and be really annoying
typedef struct button__ {
    uint8_t gpio;
    uint8_t data; // bit 0 = val_cur, bit 1 = val_prev, bit 2 = val_temp, bit 3
                  // = change_onging
    // uint8_t val_prev, val_curr, val_temp, val_change_ongoing;
    uint32_t time_val_change_ms;
} button_t;

void button_update(button_t *button);
void button_init(button_t *button, int8_t gpio);

#endif