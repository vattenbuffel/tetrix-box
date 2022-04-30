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

void button_update(button_t *button) {
    if (!button->val_change_ongoing) {
        button->val_temp = digitalRead(button->gpio);
        if (button->val_temp != button->val_curr) {
            // Initiate val change
            button->val_change_ongoing = true;
            button->time_val_change_ms = millis();
        } else {
            // Same value twice in a row
            button->val_prev = button->val_curr;
            button->val_curr = button->val_temp;
        }
        return;
    } else if (button->val_change_ongoing) {
        // See if val has changed or if it was noise
        if (millis() > button->time_val_change_ms + BUTTON_HOLD_MS) {
            button->val_change_ongoing = false;
            if (digitalRead(button->gpio) != button->val_temp) {
                return;
            }
            button->val_prev = button->val_curr;
            button->val_curr = button->val_temp;
            return;
        }
    }
}
