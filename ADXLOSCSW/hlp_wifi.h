

// WIFI
const char* ssid     = "DjiDji";
const char* password = "agaralca";
//const char* ssid     = "Noknok";
//const char* password = "431f4a027cf7";
//const char* ssid       = "Numericable-2ef0";  //  JT
//const char* password   = "";  //  JT



void setupWifi(){
    WiFi.disconnect(true, true);
    delay(1000);
    WiFi.mode(WIFI_STA);   
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
}
