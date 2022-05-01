#include "button.h"
#include "serial_print.h"

void button_init(button_t *button, int8_t gpio) {
    button->gpio = gpio;
    pinMode(button->gpio, INPUT);
    pinMode(button->gpio, INPUT_PULLUP);
    BUTTON_VAL_PREV_SET(button, false);
    BUTTON_VAL_CUR_SET(button, false);
    BUTTON_VAL_TEMP_SET(button, false);
    BUTTON_CHANGE_ONGOING_SET(button, false);
}

void button_update(button_t *button) {
    if (!BUTTON_CHANGE_ONGOING_GET(button)) {
        BUTTON_VAL_TEMP_SET(button, digitalRead(button->gpio));
        if (BUTTON_VAL_TEMP_GET(button) != BUTTON_VAL_CUR_GET(button)) {
            // Initiate val change
            BUTTON_CHANGE_ONGOING_SET(button, true);
            button->time_val_change_ms = millis();
        } else {
            // Same value twice in a row
            BUTTON_VAL_PREV_SET(button, BUTTON_VAL_CUR_GET(button));
            BUTTON_VAL_CUR_SET(button, BUTTON_VAL_TEMP_GET(button));
        }
        return;
    } else if (BUTTON_CHANGE_ONGOING_GET(button)) {
        // See if val has changed or if it was noise
        if (millis() > button->time_val_change_ms + BUTTON_HOLD_MS) {
            BUTTON_CHANGE_ONGOING_SET(button, false);
            if (digitalRead(button->gpio) != BUTTON_VAL_TEMP_GET(button)) {
                return;
            }
            BUTTON_VAL_PREV_SET(button, BUTTON_VAL_CUR_GET(button));
            BUTTON_VAL_CUR_SET(button, BUTTON_VAL_CUR_GET(button));
            return;
        }
    }
}
