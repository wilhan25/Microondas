#include "motor.h"
#include "../config.h"
#include <Arduino.h>
#include <AccelStepper.h>

// ordem exata para o 28BYJ-48 em half-step: IN1, IN3, IN2, IN4
static AccelStepper stepper(
    AccelStepper::HALF4WIRE,
    PIN_MOTOR_1, PIN_MOTOR_3,
    PIN_MOTOR_2, PIN_MOTOR_4
);

void motor_init() {
    pinMode(PIN_MOTOR_1, OUTPUT);
    pinMode(PIN_MOTOR_2, OUTPUT);
    pinMode(PIN_MOTOR_3, OUTPUT);
    pinMode(PIN_MOTOR_4, OUTPUT);

    stepper.setMaxSpeed(MOTOR_VELOCIDADE);
    stepper.setSpeed(MOTOR_VELOCIDADE);

    motor_parar();
}

void motor_girar() {
    stepper.setSpeed(MOTOR_VELOCIDADE);
    stepper.runSpeed();
}

void motor_parar() {
    // desliga as bobinas para não esquentar parado
    digitalWrite(PIN_MOTOR_1, LOW);
    digitalWrite(PIN_MOTOR_2, LOW);
    digitalWrite(PIN_MOTOR_3, LOW);
    digitalWrite(PIN_MOTOR_4, LOW);
}
