/*
  Este código está configurado para conectar um ESP32 à rede Wi-Fi 
  e enviar dados de um sensor analógico para o broker MQTT HiveMQ. 

  **Configurações Importantes:**
  1. O código está configurado para usar o broker público HiveMQ, com o endereço "broker.mqtt-dashboard.com". 
     Se você for usar um broker diferente, altere a variável `mqtt_server` com o endereço do seu broker MQTT.
  
  2. O código está configurado para se conectar à rede Wi-Fi do "Wokwi-GUEST", sem senha (rede utilizada pelo https://wokwi.com/). 
     Caso você queira usar uma rede Wi-Fi diferente, altere as variáveis `ssid` (nome da rede) e `password` (senha da rede).

  3. O código lê um valor do pino analógico 34 (sensor) e envia esses dados para o tópico MQTT "emerich/sensor/analog". 
     Caso queira usar outro pino ou tópico, basta modificar a constante `SENSOR` e `topic_sensor`.   
*/

#include <WiFi.h>             // Biblioteca para conectar o ESP ao Wi-Fi
#include <PubSubClient.h>     // Biblioteca para comunicação MQTT

const char* ssid = "Wokwi-GUEST";        // SSID da rede Wi-Fi
const char* password = "";               // Senha da rede Wi-Fi (vazio no caso de rede sem senha)
const char* mqtt_server = "broker.mqtt-dashboard.com";  // Endereço do broker MQTT (HiveMQ)
const char* topic_sensor = "emerich/sensor/analog";     // Tópico onde os dados do sensor serão publicados no MQTT

WiFiClient espClient;            // Objeto para comunicação com o Wi-Fi
PubSubClient client(espClient);  // Objeto para comunicação com o broker MQTT
unsigned long lastMsg = 0;       // Variável para armazenar o tempo da última mensagem publicada

#define SENSOR 34   // Definindo o pino do sensor analógico (pino 34 no caso)

// Função para conectar o ESP à rede Wi-Fi
void setup_wifi() {
  Serial.print("Conectando a ");           // Mensagem de status para o Serial Monitor
  Serial.println(ssid);                    // Exibe o nome da rede Wi-Fi no Serial Monitor
  WiFi.mode(WIFI_STA);                     // Configura o ESP para o modo Station (conectar-se a um ponto de acesso)
  WiFi.begin(ssid, password);              // Inicia a conexão com o Wi-Fi usando SSID e senha fornecidos
  while (WiFi.status() != WL_CONNECTED) {  // Enquanto o ESP não estiver conectado ao Wi-Fi
    delay(500);                            // Atraso de 500 ms entre tentativas
    Serial.print(".");                     // Exibe um ponto no Serial Monitor a cada tentativa
  }
  Serial.println("\nWiFi conectado");      // Mensagem indicando que o Wi-Fi foi conectado com sucesso
  Serial.print("IP address: ");            // Exibe o IP do ESP no monitor serial
  Serial.println(WiFi.localIP());          // Exibe o endereço IP do ESP
}

// Função para reconectar ao broker MQTT caso a conexão tenha sido perdida
void reconnect() {
  while (!client.connected()) {  // Enquanto não estiver conectado ao broker MQTT
    Serial.print("Tentando conexão MQTT...");  // Mensagem no Serial Monitor indicando a tentativa de conexão
    String clientId = "ESP32Client-";  // Prefixo do ID do cliente
    clientId += String(random(0xffff), HEX);  // Adiciona um sufixo aleatório em hexadecimal para garantir que o ID seja único
    if (client.connect(clientId.c_str())) {  // Tenta conectar ao broker com o ID gerado
      Serial.println("Conectado ao MQTT");  // Mensagem indicando que a conexão foi bem-sucedida
    } else {  // Se a conexão falhar
      Serial.print("Falha, rc=");       // Exibe o código de falha da tentativa de conexão
      Serial.print(client.state());     // Exibe o estado de erro (código de erro) retornado pelo MQTT
      Serial.println(" tentando novamente em 5 segundos");  // Mensagem indicando que a tentativa será feita novamente após 5 segundos
      delay(5000);  // Espera 5 segundos antes de tentar novamente
    }
  }
}

// Função setup que é chamada uma única vez quando o dispositivo é inicializado
void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial com uma taxa de transmissão de 115200 bauds
  setup_wifi();          // Chama a função para conectar-se à rede Wi-Fi
  client.setServer(mqtt_server, 1883);  // Define o broker MQTT e a porta (1883 é a porta padrão para MQTT)
}

// Função loop que executa repetidamente enquanto o dispositivo está ligado
void loop() {
  if (!client.connected()) {  // Verifica se o cliente MQTT está conectado
    reconnect();  // Se não estiver conectado, chama a função de reconexão
  }
  client.loop();  // Mantém a comunicação com o broker MQTT ativa
 
  unsigned long now = millis();  // Captura o tempo atual (em ms desde o início)
  if (now - lastMsg > 2000) {  // Se passaram mais de 2000 ms (2 segundos) desde a última publicação
    lastMsg = now;  // Atualiza a última vez que a mensagem foi enviada
    
    int sensor_analog = analogRead(SENSOR);  // Lê o valor do sensor analógico no pino 34
    Serial.println("Valor lido: " + String(sensor_analog));  // Exibe o valor lido do sensor no Serial Monitor
    client.publish(topic_sensor, String(sensor_analog).c_str());  // Publica o valor do sensor no tópico MQTT
  }
}
