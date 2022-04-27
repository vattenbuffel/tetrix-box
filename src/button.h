#ifndef BUTTON_H_
#define BUTTON_H_

#include <Arduino.h>
#include "stdint.h"

#define BUTTON_HOLD_MS 50

#define BUTTON_PRESSED(button) ((button.val_curr == 0) && (button.val_prev == 1))
#define BUTTON_PRESSED_P(button) ((button->val_curr == 0) && (button->val_prev == 1))
#define BUTTON_RELEASED_P(button) ((button->val_curr == 1) && (button->val_prev == 0))

typedef enum {
    button_action_none,
    button_action_released,
    button_action_pressed,
} button_action_t;

typedef struct button {
    uint8_t gpio;
    bool val_prev;
    bool val_curr;
    bool val_temp;
    bool val_change_ongoing;
    uint32_t time_val_change_ms;
} button_t;

uint8_t button_update(button_t* button);
void button_init(button_t* button, int gpio);



#endif