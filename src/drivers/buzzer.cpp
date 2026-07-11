// buzzer.cpp
#include "buzzer.h"
#include "../config.h"
#include <Arduino.h>

void buzzer_init() {
    pinMode(PIN_BUZZER, OUTPUT);
    digitalWrite(PIN_BUZZER, LOW);
}

void buzzer_bip(int vezes) {
    for (int i = 0; i < vezes; i++) {
        digitalWrite(PIN_BUZZER, HIGH);
        vTaskDelay(pdMS_TO_TICKS(150));
        digitalWrite(PIN_BUZZER, LOW);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}