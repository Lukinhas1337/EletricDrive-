#include <ArduinoJson.h>

#define POTENCIOMETRO_BATERIA_PIN A0
#define POTENCIOMETRO_VIDA_UTIL_PIN A1
#define POTENCIOMETRO_TEMPERATURA_PIN A2  
#define POTENCIOMETRO_UMIDADE_PIN A3      

#define BATERIA_MINIMA 0
#define BATERIA_MAXIMA 100
#define VIDA_UTIL_MINIMA 0
#define VIDA_UTIL_MAXIMA 100
#define TEMPERATURA_MINIMA 16
#define TEMPERATURA_MAXIMA 33
#define UMIDADE_MINIMA 0
#define UMIDADE_MAXIMA 100

#define BATERIA_LIMITE_MINIMA 35
#define BATERIA_LIMITE_MEDIA 70
#define BATERIA_LIMITE_ALTA 85
#define VIDA_UTIL_LIMITE_CRITICA 25
#define VIDA_UTIL_LIMITE_REVISAO 50
#define VIDA_UTIL_LIMITE_BOA 75

void setup() {
  Serial.begin(9600);
}

void loop() {
  int leituraPotenciaBateria = analogRead(POTENCIOMETRO_BATERIA_PIN);
  int leituraPotenciaVidaUtil = analogRead(POTENCIOMETRO_VIDA_UTIL_PIN);
  int leituraPotenciaTemperatura = analogRead(POTENCIOMETRO_TEMPERATURA_PIN);
  int leituraPotenciaUmidade = analogRead(POTENCIOMETRO_UMIDADE_PIN);

  int porcentagemBateria = map(leituraPotenciaBateria, 0, 1023, BATERIA_MINIMA, BATERIA_MAXIMA);
  int vidaUtilBateria = map(leituraPotenciaVidaUtil, 0, 1023, VIDA_UTIL_MINIMA, VIDA_UTIL_MAXIMA);
  int temperaturaCarro = map(leituraPotenciaTemperatura, 0, 1023, TEMPERATURA_MINIMA, TEMPERATURA_MAXIMA);
  int umidadeCarro = map(leituraPotenciaUmidade, 0, 1023, UMIDADE_MINIMA, UMIDADE_MAXIMA);

  StaticJsonDocument<200> json;

  json["porcentagemBateria"] = porcentagemBateria;
  json["cargaBateria"] = getCargaBateria(porcentagemBateria);
  json["vidaUtilBateria"] = vidaUtilBateria;
  json["estadoVidaUtil"] = getEstadoVidaUtil(vidaUtilBateria);
  json["temperaturaCarro"] = temperaturaCarro;
  json["umidadeCarro"] = umidadeCarro;

  String jsonString;
  serializeJson(json, jsonString);

  Serial.println(jsonString);

  delay(2000);
}

String getCargaBateria(int porcentagem) {
  if (porcentagem <= BATERIA_LIMITE_MINIMA) {
    return "Baixa";
  } else if (porcentagem <= BATERIA_LIMITE_MEDIA) {
    return "Média";
  } else if (porcentagem <= BATERIA_LIMITE_ALTA) {
    return "Alta";
  } else {
    return "Cheia";
  }
}

String getEstadoVidaUtil(int vidaUtil) {
  if (vidaUtil <= VIDA_UTIL_LIMITE_CRITICA) {
    return "Crítica";
  } else if (vidaUtil <= VIDA_UTIL_LIMITE_REVISAO) {
    return "Revisão";
  } else if (vidaUtil <= VIDA_UTIL_LIMITE_BOA) {
    return "Boa";
  } else {
    return "Saudável";
  }
}
