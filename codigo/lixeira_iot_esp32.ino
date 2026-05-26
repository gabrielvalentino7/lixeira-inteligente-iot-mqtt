#include <WiFi.h>
#include <PubSubClient.h>

// Projeto: Sistema Inteligente de Monitoramento de Lixeiras Urbanas utilizando IoT
// Autor: Gabriel Valentino
// Plataforma: ESP32 + Wokwi
// Comunicação: Wi-Fi + MQTT

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;

const char* topicoNivel = "mackenzie/gabriel/lixeira01/nivel";
const char* topicoStatus = "mackenzie/gabriel/lixeira01/status";
const char* topicoDistancia = "mackenzie/gabriel/lixeira01/distancia";
const char* topicoResumo = "mackenzie/gabriel/lixeira01/resumo";

const int trigPin = 5;
const int echoPin = 18;
const int ledPin = 2;

const float alturaLixeira = 100.0;

unsigned long ultimaPublicacao = 0;
const unsigned long intervaloPublicacao = 3000;

WiFiClient espClient;
PubSubClient client(espClient);

void conectarWiFi() {
  Serial.println("Conectando ao Wi-Fi do Wokwi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi conectado com sucesso!");
  Serial.print("Endereco IP do ESP32: ");
  Serial.println(WiFi.localIP());
}

void conectarMQTT() {
  while (!client.connected()) {
    Serial.println("Conectando ao broker MQTT...");

    String clientId = "esp32_lixeira_gabriel_";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado ao broker MQTT com sucesso!");
    } else {
      Serial.print("Falha na conexao MQTT. Codigo: ");
      Serial.println(client.state());
      Serial.println("Tentando novamente em 2 segundos...");
      delay(2000);
    }
  }
}

float medirDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracao = pulseIn(echoPin, HIGH, 30000);
  float distancia = duracao * 0.034 / 2;

  if (distancia <= 0 || distancia > alturaLixeira) {
    distancia = alturaLixeira;
  }

  return distancia;
}

int calcularNivel(float distancia) {
  float ocupacao = ((alturaLixeira - distancia) / alturaLixeira) * 100.0;

  if (ocupacao < 0) {
    ocupacao = 0;
  }

  if (ocupacao > 100) {
    ocupacao = 100;
  }

  return (int)ocupacao;
}

String definirStatus(int nivel) {
  if (nivel < 60) {
    return "NORMAL";
  } else if (nivel >= 60 && nivel < 80) {
    return "ATENCAO";
  } else {
    return "CRITICO";
  }
}

void publicarDados(float distancia, int nivel, String statusLixeira) {
  char msgNivel[10];
  char msgDistancia[20];
  char msgResumo[180];

  sprintf(msgNivel, "%d", nivel);
  sprintf(msgDistancia, "%.1f cm", distancia);

  sprintf(
    msgResumo,
    "{\"lixeira\":\"lixeira01\",\"distancia_cm\":%.1f,\"nivel_percentual\":%d,\"status\":\"%s\"}",
    distancia,
    nivel,
    statusLixeira.c_str()
  );

  client.publish(topicoNivel, msgNivel);
  client.publish(topicoDistancia, msgDistancia);
  client.publish(topicoStatus, statusLixeira.c_str());
  client.publish(topicoResumo, msgResumo);

  Serial.println("---------------------------------------");
  Serial.print("Distancia medida pelo sensor: ");
  Serial.print(distancia);
  Serial.println(" cm");

  Serial.print("Nivel estimado de ocupacao: ");
  Serial.print(nivel);
  Serial.println("%");

  Serial.print("Status atual da lixeira: ");
  Serial.println(statusLixeira);

  Serial.println("Mensagem enviada ao MQTT:");
  Serial.println(msgResumo);
  Serial.println("---------------------------------------");
}

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(ledPin, LOW);

  conectarWiFi();

  client.setServer(mqttServer, mqttPort);

  conectarMQTT();

  Serial.println("Sistema de monitoramento de lixeira iniciado.");
}

void loop() {
  if (!client.connected()) {
    conectarMQTT();
  }

  client.loop();

  unsigned long agora = millis();

  if (agora - ultimaPublicacao >= intervaloPublicacao) {
    ultimaPublicacao = agora;

    float distancia = medirDistancia();
    int nivel = calcularNivel(distancia);
    String statusLixeira = definirStatus(nivel);

    if (statusLixeira == "CRITICO") {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }

    publicarDados(distancia, nivel, statusLixeira);
  }
}
