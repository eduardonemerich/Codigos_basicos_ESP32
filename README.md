# Códigos básicos para ESP32 
![Badge em Desenvolvimento](http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=GREEN&style=for-the-badge)

Repositório com códigos básicos de uso recorrente com o ESP32, criados e comentados para servir de base para projetos mais complexos.

Embora os códigos tenham sido desenvolvidos no PlatformIO (VS Code), eles são totalmente compatíveis com a **IDE do Arduino**.

## Como usar com a IDE do Arduino

1. **Copie o código**:
   - Os arquivos de código estão na pasta `src` e em formato `.cpp`.
   - Abra o arquivo `.cpp` desejado na pasta `src` e copie o conteúdo.

2. **Cole na IDE do Arduino**:
   - Crie um novo esboço na IDE do Arduino (Arquivo > Novo) e cole o código copiado nele.

3. **Procedimento normal**:
   - A partir daqui, siga o procedimento normal que você já utiliza na IDE do Arduino para carregar o código no ESP32.

---

## Índice dos códigos deste repositório 

1. [Bluetooth Relé](#bluetooth-rele)
2. [Bluetooth Veículo](#bluetooth-veiculo)
3. [MQTT com analogRead](#mqtt-com-analogread)

## Bluetooth Relé

Código de controle de um relé via Bluetooth. Este código permite ligar ou desligar um relé usando comandos enviados por um aplicativo via Bluetooth (utilizo o aplicativo RoboRemo), facilitando o controle remoto de dispositivos conectados ao relé.

---

## Bluetooth Veículo

Este código controla um carrinho usando uma ponte H via Bluetooth. Ele permite mover o carrinho para frente, para trás, para a esquerda e para a direita, além de parar, com comandos enviados pelo aplicativo.

---

## MQTT com analogRead

Este código conecta o ESP32 a uma rede MQTT e lê os dados de um sensor analógico. Os dados são enviados para um broker MQTT, permitindo o monitoramento remoto pelo openHAB.

---


