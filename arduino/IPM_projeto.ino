#include "Estados.h"

void setup() {
  inicializarSistema();
  Serial.begin(9600); 
}

void loop() {
  processarSistema();
}