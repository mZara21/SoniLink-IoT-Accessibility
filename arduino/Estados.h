#ifndef ESTADOS_H
#define ESTADOS_H

#include <Arduino.h>

extern const uint8_t LEDS_AMARELOS[2];
extern const uint8_t LEDS_VERMELHOS[2];
constexpr uint8_t LED_VERDE = 4;

constexpr uint8_t LED_BRANCO = 9;
constexpr uint8_t BUZZER     = 10;   // Active Low
constexpr uint8_t BOTAO_AGENCIA = 11; // Botão Branco
constexpr uint8_t BOTAO_SIM    = 12; // Botão que liga som/buzzer
constexpr uint8_t RELAY_PIN = 13; 
constexpr uint8_t SENSOR_SOM   = A0; 

enum Estado { SEGURO, ALERTA, EMERGENCIA };

void inicializarSistema();
void processarSistema();
void desenharMatriz(unsigned long nivel);
void apagarLedsSinalizacao();
void gerirRelay(unsigned long nivel, bool protegido);

#endif