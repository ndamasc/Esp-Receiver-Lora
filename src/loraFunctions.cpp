#include "loRaFunctions.h"

void startLoRa(){
    int counter = 0;
    SPI.begin(SCK, MISO, MOSI, SS);
    LoRa.setPins(SS, RST, DIO0);
    while (!LoRa.begin(BAND) && counter < 10) {
        Serial.print(".");
        counter++;
        delay(500);
    }
    if (counter == 10) {
        Serial.println("Starting LoRa failed!");
    } else {
        Serial.println("LoRa Initialization OK!");
    }
    LoRa.setSpreadingFactor(12);
    LoRa.setSignalBandwidth(125E3);  
    LoRa.setCodingRate4(5); 
}

void getLoRaData() {

    Serial.print("LoRa packet received: ");
    while (LoRa.available()) {
        String LoRaData = LoRa.readString();
        Serial.print(LoRaData);
        int pos1 = LoRaData.indexOf('/');
        //int pos2 = LoRaData.indexOf('&');
        //int pos3 = LoRaData.indexOf('#');
        readingID = LoRaData.substring(0, pos1).toInt();
        temperature = LoRaData.substring(pos1 + 1, LoRaData.length());
        
    }

    if(readingID!=pacotesRecebidos){
        perdas = (readingID - pacotesRecebidos);
        perdas = (perdas/readingID)*100;
    }
    else{
        
    }

    rssi = LoRa.packetRssi();
    snr = LoRa.packetSnr();
    Serial.print(" with RSSI ");
    Serial.print(rssi);
    Serial.print(" e perda de pacote: ");
    Serial.print(perdas);
    Serial.print(" And SNR ");
    Serial.print(snr);
}
