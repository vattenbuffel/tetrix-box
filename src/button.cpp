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
    if (button->val_change_ongoing) {
        if (millis() < button->time_val_change_ms + BUTTON_HOLD_MS) {
            if (digitalRead(button->gpio) != button->val_temp) {
                button->val_change_ongoing = false;
            }
            return;
        }

        button->val_change_ongoing = false;
        button->val_prev = button->val_curr;
        button->val_curr = button->val_temp;
        return;
    }

    button->val_temp = digitalRead(button->gpio);
    if (button->val_temp != button->val_curr) {
        Serial.println("Start val change");
        button->val_change_ongoing = true;
    } else {
        button->val_prev = button->val_curr;
        button->val_curr = button->val_temp;
    }
}
