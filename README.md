# Sistema Inteligente de Monitoramento de Lixeiras Urbanas utilizando IoT

Projeto desenvolvido para a disciplina de Objetos Inteligentes, com o objetivo de demonstrar uma solução de Internet das Coisas (IoT) aplicada ao monitoramento de lixeiras urbanas.

A proposta consiste em utilizar um microcontrolador ESP32, um sensor ultrassônico para medir o nível de preenchimento da lixeira, um LED vermelho como atuador visual de alerta e comunicação via protocolo MQTT para envio dos dados em tempo real.

## Autor

Gabriel dos Santos Valentino  
Universidade Presbiteriana Mackenzie

## Objetivo do projeto

O objetivo do projeto é monitorar o nível de ocupação de uma lixeira urbana e enviar os dados para uma plataforma MQTT. Quando o nível de preenchimento atinge uma faixa crítica, o sistema aciona um LED vermelho como alerta local e publica o estado da lixeira em tópicos MQTT.

## Funcionamento

O funcionamento do protótipo ocorre da seguinte forma:

1. O ESP32 conecta-se à rede Wi-Fi simulada do Wokwi.
2. O sensor ultrassônico HC-SR04 realiza a medição da distância entre a parte superior da lixeira e o nível de resíduos.
3. O código calcula o percentual estimado de ocupação da lixeira.
4. O sistema classifica a situação da lixeira em três estados:
   - NORMAL: até 59% de ocupação;
   - ATENÇÃO: de 60% até 79% de ocupação;
   - CRÍTICO: a partir de 80% de ocupação.
5. Quando o estado é CRÍTICO, o LED vermelho é acionado.
6. O ESP32 publica os dados no broker MQTT.
7. Um cliente MQTT, como o HiveMQ WebSocket Client, recebe as mensagens em tempo real.

## Link da simulação no Wokwi

A simulação do projeto pode ser acessada pelo link abaixo:

https://wokwi.com/projects/465118464055185409

## Componentes utilizados

| Componente | Função |
|---|---|
| ESP32 DevKit | Microcontrolador responsável pelo processamento, conexão Wi-Fi e comunicação MQTT |
| Sensor ultrassônico HC-SR04 | Sensor utilizado na simulação para medir a distância e estimar o nível da lixeira |
| LED vermelho | Atuador visual acionado quando a lixeira atinge estado crítico |
| Resistor de 220 ohms | Componente utilizado para limitar a corrente elétrica do LED |
| Broker MQTT HiveMQ | Serviço utilizado para receber as mensagens publicadas pelo ESP32 |
| Wokwi | Plataforma utilizada para simulação do circuito e do código |

## Observação sobre o sensor

Na proposta original do artigo foi previsto o uso do sensor ultrassônico A02YYUW, adequado para aplicações reais em ambientes urbanos por possuir proteção e maior robustez. Na simulação do Wokwi, foi utilizado o sensor HC-SR04 como equivalente funcional, pois ambos realizam medição de distância. Essa adaptação foi feita para viabilizar a demonstração do funcionamento do protótipo em ambiente simulado.

## Ligações do circuito

| Componente | Pino do componente | Pino no ESP32 |
|---|---|---|
| HC-SR04 | VCC | 5V |
| HC-SR04 | GND | GND |
| HC-SR04 | TRIG | GPIO 5 |
| HC-SR04 | ECHO | GPIO 18 |
| LED vermelho | Ânodo | GPIO 2, com resistor de 220 ohms |
| LED vermelho | Cátodo | GND |

## Comunicação MQTT

O projeto utiliza o protocolo MQTT para envio dos dados da lixeira em tempo real.

Broker utilizado:

```text
broker.hivemq.com
