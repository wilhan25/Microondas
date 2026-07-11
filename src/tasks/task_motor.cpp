#include "task_motor.h"
#include "../config.h"
#include "../estado.h"
#include "../drivers/motor.h"
#include "../drivers/buzzer.h"
#include <Arduino.h>

void task_motor(void *pv) {
    TickType_t ultimo_tick = xTaskGetTickCount();

    while (1) {
        // copia só o que precisa para não segurar o mutex durante o giro
        xSemaphoreTake(mutex_estado, portMAX_DELAY);
        bool ligado = estado.motor_ligado;
        xSemaphoreGive(mutex_estado);

        if (ligado) {
            motor_girar();

            // desconta o tempo real decorrido desde o último tick
            TickType_t agora      = xTaskGetTickCount();
            uint32_t   decorrido  = (agora - ultimo_tick) * portTICK_PERIOD_MS;
            ultimo_tick = agora;

            xSemaphoreTake(mutex_estado, portMAX_DELAY);

            if (estado.tempo_ms > decorrido)
                estado.tempo_ms -= decorrido;
            else
                estado.tempo_ms = 0;

            if (estado.tempo_ms == 0) {
                estado.motor_ligado = false;
                estado.digitando    = true;
                estado.num_digitos  = 0;
                memset(estado.digitos, 0, sizeof(estado.digitos));
                digitalWrite(PIN_LED, LOW);
                motor_parar();
                buzzer_bip(3);  
                Serial.println("[motor] tempo esgotado");
            }

            xSemaphoreGive(mutex_estado);

        } else {
            motor_parar();
            ultimo_tick = xTaskGetTickCount(); // reseta referência quando parado
        }

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
