#include <MovingAverage.h>
#include "PeakDetection.h"
#include <Preferences.h>
#include "hlp_preferences.h"
#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>
#include <ArduinoOSC.h>
#include "hlp_wifi.h"
#include "hlp_osc.h"
#include "hlp_adxl.h"

void setup()
{
Serial.begin(115200);  // JT
delay(1000);
Serial.println("Début Setup");

pref.begin("sauve", false);
// Paramétrage des services
setupWifi();
setupOSC();

// Création des tâches
xTaskCreatePinnedToCore(tskAcquisition,"Acquisition",10000,NULL,8,&Acquisition,0);
//xTaskCreatePinnedToCore(tskParseOSC,"OSC",10000,NULL,8,&OSC,1);

}

void loop()
{
  delay(100);
}
