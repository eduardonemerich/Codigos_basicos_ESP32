#include "BluetoothSerial.h"  // Biblioteca para comunicação Bluetooth

// Definição dos pinos para controle dos motores
const int motor1A = 2;  // Pino para o motor 1, direção A
const int motor1B = 4;  // Pino para o motor 1, direção B
const int motor2A = 16; // Pino para o motor 2, direção A
const int motor2B = 17; // Pino para o motor 2, direção B

BluetoothSerial SerialBT;  // Criação do objeto para a comunicação Bluetooth

void setup() {
  pinMode(motor1A, OUTPUT); // Define o pino do motor 1, direção A, como saída
  pinMode(motor1B, OUTPUT); // Define o pino do motor 1, direção B, como saída
  pinMode(motor2A, OUTPUT); // Define o pino do motor 2, direção A, como saída
  pinMode(motor2B, OUTPUT); // Define o pino do motor 2, direção B, como saída

  SerialBT.begin("Carrinho_BT"); // Inicializa o Bluetooth com o nome "Carrinho_BT"
}

void loop() {
  if (SerialBT.available()) {  // Verifica se há dados disponíveis via Bluetooth
    char comando = SerialBT.read();  // Lê o comando enviado pelo app RoboRemo

    switch (comando) {  // Verifica o comando recebido e executa a ação correspondente
      case 'F':  // Se o comando for 'F' (frente)
        mover(HIGH, LOW, HIGH, LOW);  // Liga os motores para ir para frente
        break;

      case 'B':  // Se o comando for 'B' (trás)
        mover(LOW, HIGH, LOW, HIGH);  // Liga os motores para ir para trás
        break;

      case 'R':  // Se o comando for 'R' (direita)
        mover(HIGH, LOW, LOW, HIGH);  // Liga os motores para virar à direita
        break;

      case 'L':  // Se o comando for 'L' (esquerda)
        mover(LOW, HIGH, HIGH, LOW);  // Liga os motores para virar à esquerda
        break;

      case 'S':  // Se o comando for 'S' (parar)
        mover(LOW, LOW, LOW, LOW);  // Desliga os motores, parando o carrinho
        break;
    }
  }
}

// Função para controlar os motores
void mover(int m1A, int m1B, int m2A, int m2B) {
  digitalWrite(motor1A, m1A); // Controla a direção do motor 1, pino A
  digitalWrite(motor1B, m1B); // Controla a direção do motor 1, pino B
  digitalWrite(motor2A, m2A); // Controla a direção do motor 2, pino A
  digitalWrite(motor2B, m2B); // Controla a direção do motor 2, pino B
}
