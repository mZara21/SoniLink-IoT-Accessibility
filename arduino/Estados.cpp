#include "Estados.h"

const uint8_t LEDS_AMARELOS[2]  = {5, 6};
const uint8_t LEDS_VERMELHOS[2] = {7, 8};


unsigned long contadorStress = 0; 
unsigned long tempoAnterior = 0;
unsigned long tempoEntradaAmarelo = 0;

bool brancoAtivo = false;
bool ultimoEstadoAgencia = HIGH;

void inicializarSistema() {
  for(int i = 2; i <= 10; i++) pinMode(i, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BOTAO_AGENCIA, INPUT_PULLUP);
  pinMode(BOTAO_SIM, INPUT_PULLUP);
  
  digitalWrite(BUZZER, HIGH); 
  digitalWrite(RELAY_PIN, LOW);
  tempoAnterior = millis();
  Serial.begin(9600);
}



void gerirRelay(unsigned long nivel, bool protegido) {
  
  if (protegido || nivel == 0) {
    tempoEntradaAmarelo = 0; 
  }

  if (protegido || nivel < 1500) {
    digitalWrite(RELAY_PIN, LOW);
    return;
  }

  unsigned long tempoCiclo;
  
  // 3. ESTADO VERMELHO, ALARME CONTÍNUO (4 Cliques rápidos)
  if (nivel >= 4000) {
    tempoCiclo = millis() % 1500; // Ciclo contínuo
    if ((tempoCiclo > 0   && tempoCiclo < 100) ||  // Clique 1
        (tempoCiclo > 200 && tempoCiclo < 300) ||  // Clique 2
        (tempoCiclo > 400 && tempoCiclo < 500) ||  // Clique 3
        (tempoCiclo > 600 && tempoCiclo < 700))    // Clique 4
    {
      digitalWrite(RELAY_PIN, HIGH);
    } else {
      digitalWrite(RELAY_PIN, LOW);
    }
  } 
  // 4. ESTADO AMARELO, MÁXIMO DE 2 AVISOS
  else if (nivel >= 1500) {
    if (tempoEntradaAmarelo == 0) {
        tempoEntradaAmarelo = millis();
    }

    if (millis() - tempoEntradaAmarelo <= 3000) {
        tempoCiclo = (millis() - tempoEntradaAmarelo) % 1500; 
        
        if ((tempoCiclo > 0   && tempoCiclo < 150) ||  
            (tempoCiclo > 400 && tempoCiclo < 550))    
        {
          digitalWrite(RELAY_PIN, HIGH);
        } else {
          digitalWrite(RELAY_PIN, LOW);
        }
    } else {
        digitalWrite(RELAY_PIN, LOW);
    }
  }
}

void desenharMatriz(unsigned long nivel) {
  apagarLedsSinalizacao();
  
  if (brancoAtivo) return;

  // O Verde está SEMPRE aceso indicando Vigilância Silenciosa
  digitalWrite(LED_VERDE, HIGH);

  
  // ESTADO AMARELO (Aviso Háptico - Janela de Agência: 1.5s a 4.0s)
  if (nivel >= 1500) digitalWrite(LEDS_AMARELOS[0], HIGH);
  if (nivel >= 2500) digitalWrite(LEDS_AMARELOS[1], HIGH); 

  // ESTADO VERMELHO (Emergência/Pânico - 4.0s a 6.0s)
  if (nivel >= 4000) digitalWrite(LEDS_VERMELHOS[0], HIGH);
  if (nivel >= 5000) digitalWrite(LEDS_VERMELHOS[1], HIGH);
}

void apagarLedsSinalizacao() {
  for(int i = 2; i <= 8; i++) digitalWrite(i, LOW);
}


void processarSistema() {
  unsigned long tempoAtual = millis();
  unsigned long delta = tempoAtual - tempoAnterior;
  tempoAnterior = tempoAtual;

  // GESTÃO DO BOTÃO BRANCO (AGÊNCIA MANUAL)
  bool estadoAgencia = digitalRead(BOTAO_AGENCIA);
  if (estadoAgencia == LOW && ultimoEstadoAgencia == HIGH) {
    brancoAtivo = !brancoAtivo;
    if (brancoAtivo) contadorStress = 0; 
    delay(50); 
  }
  ultimoEstadoAgencia = estadoAgencia;

  // LEITURA DE SOM (AMOSTRAGEM RÁPIDA DE 20ms)
  bool haBarulho = false;
  unsigned long startMillis = millis();
  while (millis() - startMillis < 20) {
    if (analogRead(SENSOR_SOM) < 500) { 
      haBarulho = true;
      break;
    }
  }

  // 3ATUAÇÃO DO BUZZER (O VILÃO / SIMULADOR DO RUÍDO EXTERNO)
  if (!brancoAtivo && digitalRead(BOTAO_SIM) == LOW) {
    digitalWrite(BUZZER, LOW); 
  } else {
    digitalWrite(BUZZER, HIGH); 
  }

  // ACUMULADOR DE STRESS E OVERRIDE AUTOMÁTICO
  if (!brancoAtivo) {
    if (haBarulho) {
      if (contadorStress < 6000) contadorStress += delta; 
    } else {
      if (contadorStress > delta) contadorStress -= (delta / 2); // Acalma se o barulho parar
      else contadorStress = 0;
    }
-
    // Se o stress chegar aos 6 segundos OVERRIDE
    if (contadorStress >= 6000) {
        brancoAtivo = true;      
        contadorStress = 0;      
        Serial.println("!!! AUTO-PROTEÇÃO ATIVADA !!! OVERRIDE DE EMERGENCIA");
    }
  }

  digitalWrite(LED_BRANCO, brancoAtivo ? HIGH : LOW);
  desenharMatriz(contadorStress);
  gerirRelay(contadorStress, brancoAtivo);

  Serial.print("Carga Sensorial (ms): "); Serial.print(contadorStress);
  Serial.print(" | Protecao ANC: "); Serial.println(brancoAtivo ? "ON" : "OFF");
}