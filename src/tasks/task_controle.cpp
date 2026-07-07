#include "task_controle.h"
#include "../config.h"
#include "../estado.h"
#include "../drivers/controle.h"
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

static IRrecv ir(PIN_IR, IR_BUFFER_SIZE, IR_TIMEOUT);
static decode_results resultado;

// converte os 4 dígitos [MM dez, MM uni, SS dez, SS uni] em milissegundos
static uint32_t digitos_para_ms(const uint8_t d[4]) {
    uint8_t min = d[0] * 10 + d[1];
    uint8_t seg = d[2] * 10 + d[3];
    if (seg > 59) seg = 59;
    return ((uint32_t)min * 60 + seg) * 1000UL;
}

// zera os dígitos e volta ao modo de digitação
static void resetar_estado() {
    estado.motor_ligado = false;
    estado.digitando    = true;
    estado.tempo_ms     = 0;
    estado.num_digitos  = 0;
    memset(estado.digitos, 0, sizeof(estado.digitos));
    digitalWrite(PIN_LED, LOW);
}

void task_controle_init() {
    ir.enableIRIn();
}

void task_controle(void *pv) {
    while (1) {
        if (ir.decode(&resultado)) {
            uint32_t raw = resultado.value;
            ir.resume();

            // protocolo NEC envia 0xFFFFFFFF enquanto o botão é segurado
            if (raw == 0xFFFFFFFF) {
                vTaskDelay(pdMS_TO_TICKS(10));
                continue;
            }

            botoes_controle btn = conversaoBtn(raw);
            Serial.printf("[IR] %s (0x%08X)\n", nomeBtn(btn), raw);

            xSemaphoreTake(mutex_estado, portMAX_DELAY);

            switch (btn) {

                // ── dígitos numéricos ─────────────────────────────────────
                // BTN_0 até BTN_9 são sequenciais no enum:
                // subtrair BTN_0 dá o dígito diretamente
                case BTN_0: case BTN_1: case BTN_2: case BTN_3: case BTN_4:
                case BTN_5: case BTN_6: case BTN_7: case BTN_8: case BTN_9: {
                    if (!estado.digitando) break;

                    uint8_t num = (uint8_t)(btn - BTN_0);

                    if (estado.num_digitos < 4) {
                        estado.digitos[estado.num_digitos++] = num;
                    } else {
                        // já tem 4 dígitos: empurra para a esquerda e insere no final
                        estado.digitos[0] = estado.digitos[1];
                        estado.digitos[1] = estado.digitos[2];
                        estado.digitos[2] = estado.digitos[3];
                        estado.digitos[3] = num;
                    }

                    Serial.printf("Digitando: %d%d:%d%d\n",
                        estado.digitos[0], estado.digitos[1],
                        estado.digitos[2], estado.digitos[3]);
                    break;
                }

                // ── PLAY: inicia aquecimento ──────────────────────────────
                case BTN_PLAY: {
                    if (!estado.digitando) break;

                    uint32_t ms = digitos_para_ms(estado.digitos);
                    if (ms == 0) break;

                    estado.tempo_ms     = ms;
                    estado.motor_ligado = true;
                    estado.digitando    = false;
                    digitalWrite(PIN_LED, HIGH);

                    Serial.printf("Iniciando: %d%d:%d%d → %lu ms\n",
                        estado.digitos[0], estado.digitos[1],
                        estado.digitos[2], estado.digitos[3], ms);
                    break;
                }

                // ── POWER: cancela tudo imediatamente ────────────────────
                case BTN_POWER:
                    resetar_estado();
                    Serial.println("Cancelado");
                    break;

                case BTN_UNKNOWN:
                    Serial.printf("Não mapeado: 0x%08X\n", raw);
                    break;

                default:
                    break;
            }

            xSemaphoreGive(mutex_estado);
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
