String en_tete = "24/12/2021-4";

#include "hlp_include.h"

void setup()
{
Serial.begin(115200);  // JT
delay(1000);
Serial.println("Début Setup");

pinMode(BPpin, INPUT_PULLUP);
pref.begin("sauve", false);
initADXL();
Serial.println ("zz =   "+ (String)zz);

// Mutex
mtxTing = xSemaphoreCreateMutex();
mtxTFT = xSemaphoreCreateMutex();
mtxOTA = xSemaphoreCreateMutex();
mtxOSC = xSemaphoreCreateMutex();
mtxCalib = xSemaphoreCreateMutex();


// Paramétrage des services
setupTFT(); 
setupWifi();
setupServer();
setupOTA();
button_init();

// Création des tâches
xTaskCreatePinnedToCore(tskHandleServer,"Serveur",10000,NULL,1,&Serveur,1);
xTaskCreatePinnedToCore(tskAcquisition,"Acquisition",10000,NULL,8,&Acquisition,0);
xTaskCreatePinnedToCore(tskButtonLoop,"Bouton",10000,NULL,8,&Bouton,0);
}

void loop()

{
//  button_loop();
  ArduinoOTA.handle();
}
