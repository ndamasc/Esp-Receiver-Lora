#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#include "wifiConnection.h"
#include "loraFunctions.h"
#include "firebase.h"
#include "storage.h"

// Variáveis para os dados recebidos via LoRa
String loRaMessage;
String temperature;
String valor_ph;


int readingID;
int pacote; 
int rssi;
float snr;
float perdas; 
int pacotesRecebidos;
int total;

// Função para imprimir os valores recebidos
void print_values() {
    Serial.println(pacotesRecebidos);
    Serial.print("temp agua: ");
    Serial.println(temperature);
}

void setup() {
    Serial.begin(115200);
    initWiFi();
    initFirebase();
    initSPIFFS();
    startLoRa();
}

void loop() {
    if(readingID<101){
        int packetSize = LoRa.parsePacket();
        if (packetSize) {
            pacotesRecebidos++;
            getLoRaData();
            send_data();
            if (!Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json)) {
                Serial.println("Falha ao enviar dados. Salvando localmente...");
                salvarDadosLocalmente(temperature);
                lerDadosLocais();
                delay(5000);
                reenviarDados();
            }
            print_values();
        }
    } 
  else{
    pacotesRecebidos = 1;
  }
}
