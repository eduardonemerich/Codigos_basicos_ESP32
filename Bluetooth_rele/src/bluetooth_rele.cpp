#include "BluetoothSerial.h" // Inclui a biblioteca para comunicação Bluetooth com o ESP32

BluetoothSerial SerialBT; // Cria um objeto para gerenciar a comunicação Bluetooth
const int pinRele = 26;    // Define o pino do ESP32 conectado ao relé

void setup() {
  SerialBT.begin("ESP32_RoboRemo"); // Inicializa o Bluetooth com o nome "ESP32_RoboRemo"
  pinMode(pinRele, OUTPUT);         // Configura o pino do relé como saída digital
  digitalWrite(pinRele, LOW);       // Garante que o relé esteja desligado ao iniciar
}

void loop() {
  if (SerialBT.available()) {       // Verifica se há dados disponíveis no Bluetooth
    char comando = SerialBT.read(); // Lê um caractere do buffer Bluetooth
    if (comando == '1') {           // Se o comando recebido for '1'
      digitalWrite(pinRele, HIGH);  // Liga o relé (ativa o pino com nível lógico alto)
    } else if (comando == '0') {    // Se o comando recebido for '0'
      digitalWrite(pinRele, LOW);   // Desliga o relé (ativa o pino com nível lógico baixo)
    }
    // Qualquer outro comando recebido será ignorado
  }
}
