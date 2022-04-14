#ifndef BUTTON_H_
#define BUTTON_H_

#include <Arduino.h>
#include "stdint.h"

#define BUTTON_HOLD_MS 50

typedef struct button {
    uint8_t gpio;
    bool val_prev;
    bool val_curr;
    bool val_temp;
    bool val_change_ongoing;
    uint32_t time_val_change_ms;
} button_t;

void button_update(button_t* button);
void button_init(button_t* button, int gpio);



#endif