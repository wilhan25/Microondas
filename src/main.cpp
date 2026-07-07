#include <Arduino.h>
#include "config.h"
#include "estado.h"
#include "drivers/motor.h"
#include "drivers/display.h"
#include "tasks/task_controle.h"
#include "tasks/task_motor.h"
#include "tasks/task_tela.h"

// ── definição das variáveis globais declaradas em estado.h ──
Estado            estado;
SemaphoreHandle_t mutex_estado;

void setup() {
    Serial.begin(115200);

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);

    motor_init();

    if (!display_init()) {
        Serial.println("Falha crítica: display não iniciou");
        while (1);
    }

    task_controle_init();

    mutex_estado = xSemaphoreCreateMutex();

    xTaskCreatePinnedToCore(task_controle, "controle",
        TASK_CONTROLE_STACK, NULL, TASK_CONTROLE_PRIO, NULL, TASK_CONTROLE_CORE);

    xTaskCreatePinnedToCore(task_motor, "motor",
        TASK_MOTOR_STACK, NULL, TASK_MOTOR_PRIO, NULL, TASK_MOTOR_CORE);

    xTaskCreatePinnedToCore(task_tela, "tela",
        TASK_TELA_STACK, NULL, TASK_TELA_PRIO, NULL, TASK_TELA_CORE);
}

void loop() {}
