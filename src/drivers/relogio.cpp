#include "relogio.h"
#include "../config.h"

void relogio_hora_atual(uint8_t &h, uint8_t &m, uint8_t &s) {
    // segundos totais desde meia-noite no momento do boot
    static const uint32_t boot_s =
        (RELOGIO_HORA   * 3600UL) +
        (RELOGIO_MINUTO *   60UL) +
         RELOGIO_SEGUNDO;

    // soma com o tempo decorrido e aplica módulo 24h
    uint32_t total = (boot_s + millis() / 1000UL) % 86400UL;

    h = total / 3600;
    m = (total % 3600) / 60;
    s = total % 60;
}
