#pragma once

// inicializa pinos e configura o AccelStepper
void motor_init();

// inicia a rotação na velocidade configurada em config.h
void motor_girar();

// para a rotação e desliga as bobinas para não esquentar
void motor_parar();
