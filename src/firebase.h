#ifndef firebase_h
#define firebase_h

#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "loRaFunctions.h"

#define API_KEY "AIzaSyBfo80E3UuaXzFiWthF07QVcGrqLD7cwr8"
#define USER_EMAIL "ncolares@gmail.com"
#define USER_PASSWORD "123456"
#define DATABASE_URL "https://sist-react-default-rtdb.firebaseio.com"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;
String uid, databasePath, parentPath;
String tempAguaPath = "/tempAgua";
//String turbPath = "/turb";
//String phPath = "/ph";
String timePath = "/timestamp";
String rssiPath = "/rssi";
String packlossPath = "/packloss";
String snrPath = "/snr";
const char* ntpServer = "pool.ntp.org";

void initFirebase() {
    configTime(-4 * 3600, 0, ntpServer);
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    Firebase.reconnectWiFi(true);
    fbdo.setResponseSize(4096);
    config.token_status_callback = tokenStatusCallback;
    config.max_token_generation_retry = 5;
    Firebase.begin(&config, &auth);
    Serial.println("Getting User UID");
    while ((auth.token.uid) == "") {
        Serial.print('.');
        delay(1000);
    }
    uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid);
    databasePath = "/Users/4";
}

unsigned long getTime() {
    time_t now;
    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return (0);
    }
    time(&now);
    return now;
}


void send_data() {
    if (Firebase.ready()) {
        unsigned long timestamp = getTime();
        Serial.print("time: ");
        Serial.println(timestamp);
        
        struct tm timeinfo;
        localtime_r((const time_t *)&timestamp, &timeinfo);
        
        // Formatar a data e a hora
        char datetime_buf[32];
        strftime(datetime_buf, sizeof(datetime_buf), "%d-%m-%Y_%H:%M", &timeinfo);
        
        // Construir o caminho apenas com a data
        parentPath = databasePath + "/" + String(datetime_buf);

        // Supondo que as variáveis abaixo sejam globais ou definidas em outro lugar acessível
        json.set(tempAguaPath.c_str(), temperature);
        //json.set(phPath.c_str(), valor_ph);
        //json.set(turbPath.c_str(), turbidez);
        json.set(rssiPath.c_str(), rssi);
        json.set(packlossPath.c_str(), perdas);
        json.set(snrPath.c_str(), snr);
        json.set(timePath, String(timestamp));
        
        Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
    }
}

#endif
