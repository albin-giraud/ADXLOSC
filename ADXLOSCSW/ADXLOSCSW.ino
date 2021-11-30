
String en_tete = "30/11/2021-1";

#include "hlp_include.h"


void setup()
{
Serial.begin(115200);  // JT
delay(1000);
Serial.println("Début Setup");

pinMode(BPpin, INPUT_PULLUP);
pref.begin("sauve", false);  //JT
//mabsx=pref.getInt("maxx",0);  //JT
//mabsy=pref.getInt("maxy",0);  //JT
//mabsz=pref.getInt("maxz",0);  //JT
//zx=pref.getInt("zerox",0);  //JT
//zy=pref.getInt("zeroy",0);  //JT
//zz=pref.getInt("zeroz",0);  //JT
initADXL();
Serial.println ("zz =   "+ (String)zz);

// Mutex
mtxTing = xSemaphoreCreateMutex();
mtxTFT = xSemaphoreCreateMutex();
mtxOTA = xSemaphoreCreateMutex();

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
