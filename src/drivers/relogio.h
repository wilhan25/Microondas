#pragma once
#include <Arduino.h>

// calcula a hora atual baseado em millis() desde o boot
// o horário inicial é definido em config.h
void relogio_hora_atual(uint8_t &h, uint8_t &m, uint8_t &s);
