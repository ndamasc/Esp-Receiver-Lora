#ifndef WIFICONNECTION_H
#define WIFICONNECTION_H

#include <WiFi.h>  

void initWiFi() {
  const char* ssid = "S23 FE de Nathalia";       // Nome da rede WiFi      S23 FE de Nathalia     |  Star Link
  const char* password = "nathalia123";  // Senha da rede WiFi     nathalia123    | Visitantes@1234567

  WiFi.begin(ssid, password);  // Inicia a conexão WiFi
  Serial.print("Conectando ao WiFi");

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
