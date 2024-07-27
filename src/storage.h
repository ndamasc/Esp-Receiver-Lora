#include <SPIFFS.h>
#include "firebase.h"

void initSPIFFS() {
  if (!SPIFFS.begin(true)) {
    Serial.println("Erro ao montar SPIFFS");
    return;
  }
}

void salvarDadosLocalmente(String temperature, String valor_ph) {
    File file = SPIFFS.open("/dados.txt", FILE_APPEND);
    if (!file) {
        Serial.println("Falha ao abrir arquivo para escrita");
        return;
    }
    file.print(temperature);
    file.close();
    file.print(valor_ph);
    file.close();
}

void reenviarDados() {
    File file = SPIFFS.open("/dados.txt", FILE_READ);
    if (!file) {
        Serial.println("Nenhum dado local encontrado para reenviar");
        return;
    }

    while (file.available()) {
        String linha = file.readStringUntil('\n');
        linha.trim(); // Remove espaços em branco extras

        if (Firebase.RTDB.pushString(&fbdo, "/Users/4", linha)) {
            Serial.println("Dados reenviados com sucesso!");
        } else {
            Serial.println("Falha ao reenviar dados. Tentará novamente na próxima vez.");
            break; // Sai do loop para tentar novamente mais tarde
        }
    }
    file.close();

    // Se todos os dados forem enviados com sucesso, limpa o arquivo
    if (!file.available()) {
        SPIFFS.remove("/dados.txt");
    }
}

void lerDadosLocais(){
    File file = SPIFFS.open("/dados.txt", FILE_READ);
    if (!file) {
        Serial.println("Nenhum dado local encontrado");
        return;
    }

    Serial.println("Conteúdo:");
    while (file.available()) {
        String linha = file.readStringUntil('\n');
        Serial.println(linha);
    }
    file.close();
}
