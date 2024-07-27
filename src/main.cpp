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

const int led = 2;

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
    Serial.print("ph: ");
    Serial.println(valor_ph);
}

void setup() {
    Serial.begin(115200);
    pinMode(led, OUTPUT);
    initWiFi();
    initFirebase();
    initSPIFFS();
    startLoRa();
}

void loop() {

    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        pacotesRecebidos++;
        getLoRaData();
        send_data();
        if (!Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json)) {
            Serial.println("Falha ao enviar dados. Salvando localmente...");
            salvarDadosLocalmente(temperature, valor_ph);
            lerDadosLocais();
            delay(5000);
            reenviarDados();
            
        }
        print_values();
        digitalWrite(led, HIGH);
        delay(2000);
        digitalWrite(led, LOW);
        }
    if(readingID==100){
        pacotesRecebidos = 1;
    }

  }

