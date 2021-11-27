#define BUTTON_1            35
#define BUTTON_2            0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);
MidiNote noteC5 = {1,72,80,dureeRAZ}; // Durée de mise à zéro
MidiNote noteC4 = {1,60,80,dureeMAX}; //  Durée de recherche du max
MidiNote noteG4 = {1,67,80,dureeINIT}; // Réinit ADXL

void button_init()
{
    btn1.setLongClickHandler([](Button2 & b) {
    Serial.println("Click long Bouton 1 ==> Appel calibration");
    xTaskCreatePinnedToCore(playMidiNote,"Click long bouton 1 ==> Calibration zéro",10000,&noteC4,8,NULL,0);
    calibrationZero();
    delay(10);    
    xTaskCreatePinnedToCore(playMidiNote,"Click long bouton 1 ==> Recherche maximum",10000,&noteG4,8,NULL,0);
    delay(100);
    Serial.println("Click long Bouton 1 ==> Appel calibration max");
    calibrationMaximum();
    xTaskCreatePinnedToCore(playMidiNote,"Click long bouton 1 ==> InitADXL",10000,&noteC5,8,NULL,0);
    Serial.println("Click long Bouton 1 ==> Init ADXL");
    initADXL();
    });
    btn1.setPressedHandler([](Button2 & b) {
    Serial.println("Click court Bouton 1");
    });
    btn2.setLongClickHandler([](Button2 & b) {
    Serial.println("Click  court Bouton 2");
    });
}

void button_loop()
{
    btn1.loop();
    btn2.loop();
}
