#include "task_tela.h"
#include "../config.h"
#include "../estado.h"
#include "../drivers/display.h"
#include "../drivers/relogio.h"
#include <Arduino.h>

void task_tela(void *pv) {
    while (1) {
        // copia o estado para variáveis locais e libera o mutex
        // antes de fazer qualquer operação de desenho (que é lenta)
        xSemaphoreTake(mutex_estado, portMAX_DELAY);
        bool     ligado    = estado.motor_ligado;
        bool     digitando = estado.digitando;
        uint32_t tempo     = estado.tempo_ms;
        uint8_t  nd        = estado.num_digitos;
        uint8_t  d[4];
        memcpy(d, estado.digitos, 4);
        xSemaphoreGive(mutex_estado);

        display_fundo();

        if (ligado) {
            display_aquecendo(tempo);

        } else if (nd > 0) {
            display_digitando(d);

        } else {
            uint8_t h, m, s;
            relogio_hora_atual(h, m, s);
            display_relogio(h, m, s);
        }

        display_atualizar();

        vTaskDelay(pdMS_TO_TICKS(200)); // atualiza 5x por segundo
    }
}
