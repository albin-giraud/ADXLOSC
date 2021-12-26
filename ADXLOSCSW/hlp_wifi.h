#include "acces.h"

void setupWifi(){
    WiFi.disconnect(true, true);
    delay(1000);
    WiFi.mode(WIFI_STA);   
    WiFi.begin(ssid, mdp);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}
