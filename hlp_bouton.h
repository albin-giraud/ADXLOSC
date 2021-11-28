#define BUTTON_1            35
#define BUTTON_2            0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
MidiNote noteC5 = {1,72,110,dureeINIT}; // Durée de mise à zéro
MidiNote noteC4 = {1,60,110,dureeRAZ}; //  Durée de recherche du max
MidiNote noteG4 = {1,67,110,dureeMAX}; // Réinit ADXL

TaskHandle_t Bouton;

void tskButtonLoop (void * pvparameters){
for (;;){
   btn1.loop();
   btn2.loop();
   vTaskDelay(100);
}
}


void button_init()
{
    btn1.setLongClickHandler([](Button2 & b) {
    printf("%d : Appel calibration \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"Calibration zéro",10000,&noteC4,8,NULL,0);
    calibrationZero();
    printf("%d : Fin Appel calibration Zéro \n",millis());
//    delay(100);    
    printf("%d : Appel calibration max \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"Recherche maximum",10000,&noteG4,8,NULL,0);
    calibrationMaximum();
    printf("%d : Fin Appel calibration max \n",millis());
    delay(100);
    printf("%d : Appel init pref",millis());
    xTaskCreatePinnedToCore(playMidiNote,"InitADXL",10000,&noteC5,8,NULL,0);
    printf("%d : Retour task Appel init pref \n",millis());
    initADXL();
    printf("%d : Fin init pref \n",millis());
    });
    btn1.setPressedHandler([](Button2 & b) {
    Serial.println("Click court Bouton 1");
    });
    btn2.setLongClickHandler([](Button2 & b) {
    Serial.println("Click  court Bouton 2");
    });
}
