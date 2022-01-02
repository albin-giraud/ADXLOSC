#include <ArduinoOSCWiFi.h>
#include <TFT_eSPI.h>
#include <MovingAverage.h>
#include "PeakDetection.h"
#include <Preferences.h>
#include "variables.h"
#include "hlp_tft.h"
#include "hlp_preferences.h"
#include "hlp_wifi.h"
#include "hlp_osc.h"
#include "hlp_adxl.h"


void setup()
{
Serial.begin(115200);  
delay(1000);
Serial.println("Début Setup");

// Paramétrage
initPreferences();
chargerCalibration();
setupWifi();
setupOSC();
setupTFT();
afficherParam();

// Création des tâches
xTaskCreatePinnedToCore(tskAcquisition,"Acquisition",10000,NULL,8,&Acquisition,0);
xTaskCreatePinnedToCore(tskParseOSC,"OSC",10000,NULL,7,&OSC,1);

}

void loop()
{
  int dummy=1;
}
