#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <WiFi.h>  // Inclui a biblioteca WiFi

// Declaração e implementação da função de conexão ao WiFi
void initWiFi() {
  const char* ssid = "Star Link";       // Nome da rede WiFi
  const char* password = "Visitantes@1234567";  // Senha da rede WiFi

  WiFi.begin(ssid, password);  // Inicia a conexão WiFi
  Serial.print("Conectando ao WiFi");

  // Espera até que a conexão seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Conectado ao WiFi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());  // Imprime o endereço IP
}

#endif
