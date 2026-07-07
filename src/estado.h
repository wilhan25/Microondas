#pragma once
#include <Arduino.h>
#include <freertos/semphr.h>

// ════════════════════════════════════════════════
//   ESTADO COMPARTILHADO
//   Único ponto de verdade do sistema.
//   Toda leitura/escrita deve usar o mutex.
// ════════════════════════════════════════════════
struct Estado {
    bool     motor_ligado = false;
    bool     digitando    = true;   // false quando motor está rodando
    uint32_t tempo_ms     = 0;      // tempo restante em ms
    uint8_t  digitos[4]   = {0, 0, 0, 0}; // [MM dez, MM uni, SS dez, SS uni]
    uint8_t  num_digitos  = 0;
};

// instância global — acessada por todas as tasks via mutex
extern Estado         estado;
extern SemaphoreHandle_t mutex_estado;
