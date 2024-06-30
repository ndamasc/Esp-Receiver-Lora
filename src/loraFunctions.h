#ifndef loRaFunctions_h
#define loRaFunctions_h

#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

extern String loRaMessage;
extern String temperature;
extern String valor_ph;
extern String turbidez;
extern int readingID;
extern int pacotesRecebidos;
extern int rssi;
extern float snr;
extern float perdas;

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

#define BAND 915E6

void startLoRa();
void getLoRaData();

#endif
