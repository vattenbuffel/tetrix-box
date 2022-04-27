#include "button.h"
#include "serial_print.h"

void button_init(button_t *button, int gpio) {
    button->gpio = gpio;
    pinMode(button->gpio, INPUT);
    pinMode(button->gpio, INPUT_PULLUP);
    button->val_prev = false;
    button->val_curr = false;
    button->val_change_ongoing = false;
}

uint8_t button_update(button_t *button) {
    if (button->val_change_ongoing) {
        if (millis() < button->time_val_change_ms + BUTTON_HOLD_MS) {
            if (digitalRead(button->gpio) != button->val_temp) {
                button->val_change_ongoing = false;
            }
            return false;
        }

        button->val_change_ongoing = false;
        button->val_prev = button->val_curr;
        button->val_curr = button->val_temp;
        // serial_printf(Serial, "button changed. old val: %d, new val: %d\n", button->val_prev, button->val_curr);
        if(BUTTON_PRESSED_P(button)){
            return button_action_pressed;
        } else if (BUTTON_RELEASED_P(button))
        {
            return button_action_released;
        }
        
    }

    button->val_temp = digitalRead(button->gpio);
    if (button->val_temp != button->val_curr) {
        button->val_change_ongoing = true;
    } else {
        button->val_prev = button->val_curr;
        button->val_curr = button->val_temp;
    }
    return false;
}
