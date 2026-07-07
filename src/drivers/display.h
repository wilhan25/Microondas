#pragma once
#include <Arduino.h>

// inicializa o display via I2C — retorna false se falhar
bool display_init();

// limpa a área útil e redesenha o bitmap de fundo
void display_fundo();

// exibe o relógio HH:MM com segundos menores abaixo
void display_relogio(uint8_t h, uint8_t m, uint8_t s);

// exibe os dígitos sendo digitados no formato MM:SS
void display_digitando(const uint8_t digitos[4]);

// exibe o contador regressivo MM:SS com label "AQUECENDO"
void display_aquecendo(uint32_t tempo_ms);

// envia o buffer para a tela (chamar após qualquer draw)
void display_atualizar();
