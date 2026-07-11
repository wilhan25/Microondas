#pragma once

// ════════════════════════════════════════════════
//   PINOS
// ════════════════════════════════════════════════
#define PIN_LED      2
#define PIN_IR       15
#define PIN_MOTOR_1  14
#define PIN_MOTOR_2  27
#define PIN_MOTOR_3  26
#define PIN_MOTOR_4  25
#define PIN_SDA      22
#define PIN_SCL      23
#define PIN_BUZZER   32

// ════════════════════════════════════════════════
//   MOTOR
// ════════════════════════════════════════════════
#define MOTOR_VELOCIDADE  600   // passos/s — limite seguro do 28BYJ-48
#define MOTOR_STEPS_REV   4096  // passos por volta em half-step

// ════════════════════════════════════════════════
//   DISPLAY
// ════════════════════════════════════════════════
#define DISPLAY_LARGURA   128
#define DISPLAY_ALTURA     64
#define DISPLAY_ENDERECO  0x3C

// área útil dentro do bitmap do microondas
#define AREA_X   5
#define AREA_Y  10
#define AREA_W  80
#define AREA_H  40

// ════════════════════════════════════════════════
//   CONTROLE IR
// ════════════════════════════════════════════════
#define IR_BUFFER_SIZE  1024
#define IR_TIMEOUT        50   // ms

// ════════════════════════════════════════════════
//   RELÓGIO
// ════════════════════════════════════════════════
#define RELOGIO_HORA     10
#define RELOGIO_MINUTO   30
#define RELOGIO_SEGUNDO   0

// ════════════════════════════════════════════════
//   TASKS — prioridades e stacks
// ════════════════════════════════════════════════
#define TASK_CONTROLE_PRIO    2
#define TASK_MOTOR_PRIO       3
#define TASK_TELA_PRIO        1

#define TASK_CONTROLE_STACK   4096
#define TASK_MOTOR_STACK      4096
#define TASK_TELA_STACK       4096

#define TASK_CONTROLE_CORE    0
#define TASK_MOTOR_CORE       0
#define TASK_TELA_CORE        1
