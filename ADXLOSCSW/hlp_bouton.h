#define BUTTON_1            35
#define BUTTON_2            0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
MidiNote noteINIT = {1,72,110,dureeINIT}; // Réinit préférences
MidiNote noteRAZ = {1,60,110,dureeRAZ}; //  Durée de mise à zéro
MidiNote noteMAX = {1,67,110,dureeMAX}; //  Durée de recherche du max
MidiNote noteMEP = {1,55,110,dureeMEP}; //  Durée de mise en place avant l'action de calibration

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
      /*
       * Action de calibration zéro
       */
    printf("%d : Procédure Zéro \n",millis());
    printf("%d : Début MEP \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"MEP",10000,&noteMEP,8,NULL,1);
    delay(dureeMEP);
    printf("%d : Fin MEP \n",millis());
    printf("%d : Début Calibration Zéro \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"Calibration zéro",10000,&noteRAZ,8,NULL,0);
    xSemaphoreTake(mtxCalib, portMAX_DELAY);    
    calibrationZero();
    xSemaphoreGive(mtxCalib);
    printf("%d : Fin calibration Zéro \n",millis());
    delay(20);
    printf("%d : Appel init pref \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"InitADXL",10000,&noteINIT,8,NULL,1);
    printf("%d : Retour task Appel init pref \n",millis());
    initADXL();
    printf("%d : Fin init pref \n",millis());
    });
    btn2.setLongClickHandler([](Button2 & b) {
        /*
       * Action de calibration max
       */ 
    printf("%d : Procédure Max \n",millis());
    printf("%d : Début MEP \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"MEP",10000,&noteMEP,8,NULL,1);
    delay(dureeMEP);
    printf("%d : Fin MEP \n",millis());
    printf("%d : Appel calibration max \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"Recherche maximum",10000,&noteMAX,8,NULL,0);
    xSemaphoreTake(mtxCalib, portMAX_DELAY);    
    calibrationMaximum();
    xSemaphoreGive(mtxCalib);
    printf("%d : Fin Appel calibration max \n",millis());
    delay(100);
    printf("%d : Appel init pref \n",millis());
    xTaskCreatePinnedToCore(playMidiNote,"InitADXL",10000,&noteINIT,8,NULL,1);
    printf("%d : Retour task Appel init pref \n",millis());
    initADXL();
    printf("%d : Fin init pref \n",millis());   
    });
}
