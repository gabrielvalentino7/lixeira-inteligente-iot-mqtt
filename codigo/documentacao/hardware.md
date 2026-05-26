# Documentação do Hardware

Este documento apresenta a descrição dos componentes de hardware utilizados no projeto **Sistema Inteligente de Monitoramento de Lixeiras Urbanas utilizando IoT**.

## Plataforma de desenvolvimento

### ESP32 DevKit

O ESP32 foi utilizado como plataforma principal do projeto por possuir conectividade Wi-Fi integrada, portas digitais suficientes para conexão com sensores e atuadores, além de compatibilidade com programação no ambiente Arduino.

No projeto, o ESP32 é responsável por:

- realizar a leitura do sensor ultrassônico;
- calcular o nível de ocupação da lixeira;
- acionar o LED vermelho quando o nível for crítico;
- conectar-se à rede Wi-Fi;
- publicar os dados no broker MQTT.

## Sensor utilizado

### Sensor ultrassônico HC-SR04

Na simulação do Wokwi foi utilizado o sensor ultrassônico HC-SR04, responsável por medir a distância entre a parte superior da lixeira e o nível dos resíduos.

Quanto maior a distância medida, menor é o nível de ocupação da lixeira.  
Quanto menor a distância medida, maior é o nível de ocupação.

A altura útil simulada da lixeira foi definida como 100 cm.

Exemplo:

| Distância medida | Nível estimado |
|---|---|
| 100 cm | 0% |
| 70 cm | 30% |
| 35 cm | 65% |
| 20 cm | 80% |
| 10 cm | 90% |

## Observação sobre o sensor real

Na proposta original do artigo, foi previsto o uso do sensor ultrassônico A02YYUW, por ser mais adequado para aplicações reais em ambientes urbanos, devido à sua maior robustez.

Na simulação, foi utilizado o HC-SR04 como equivalente funcional, pois ambos realizam medição de distância. Essa adaptação foi necessária para viabilizar a demonstração no Wokwi.

## Atuador utilizado

### LED vermelho

O LED vermelho foi utilizado como atuador visual do sistema.

Ele permanece desligado quando a lixeira está nos estados NORMAL ou ATENÇÃO. Quando o nível de ocupação atinge 80% ou mais, o sistema classifica a lixeira como CRÍTICA e aciona o LED vermelho.

## Resistor

Foi utilizado um resistor de 220 ohms em série com o LED vermelho para limitar a corrente elétrica e proteger o componente.

## Ligações do circuito

| Componente | Pino do componente | Pino no ESP32 |
|---|---|---|
| HC-SR04 | VCC | 5V |
| HC-SR04 | GND | GND |
| HC-SR04 | TRIG | GPIO 5 |
| HC-SR04 | ECHO | GPIO 18 |
| LED vermelho | Ânodo | GPIO 2, com resistor de 220 ohms |
| LED vermelho | Cátodo | GND |

## Funcionamento físico esperado

Em uma implementação física, o sensor ultrassônico seria instalado na parte superior interna da lixeira, voltado para baixo. O sensor mediria a distância entre a tampa e a superfície dos resíduos.

O ESP32 processaria essa distância e enviaria os dados pela internet via MQTT. Caso o nível de ocupação chegasse ao estado crítico, o LED vermelho seria acionado como alerta visual local.

## Componentes principais

| Componente | Função |
|---|---|
| ESP32 DevKit | Processamento, Wi-Fi e MQTT |
| Sensor ultrassônico HC-SR04 | Medição da distância na simulação |
| Sensor ultrassônico A02YYUW | Sensor previsto para aplicação física |
| LED vermelho | Atuador visual de alerta |
| Resistor de 220 ohms | Proteção do LED |
| Jumpers | Conexões elétricas |
| Protoboard | Montagem provisória do circuito |
