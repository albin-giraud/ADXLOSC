#include "PeakDetection.h"
#include "hlp_wifi.h"
#include "hlp_osc.h"
#include "hlp_adxl.h"

void setup()
{
Serial.begin(115200);  // JT
delay(1000);
Serial.println("Début Setup");

pinMode(BPpin, INPUT_PULLUP);
pref.begin("sauve", false);

// Mutex


// Paramétrage des services
setupWifi();

// Création des tâches
xTaskCreatePinnedToCore(tskAcquisition,"Acquisition",10000,NULL,8,&Acquisition,0);
}

void loop()

{
  
}
