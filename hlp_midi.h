// Midi
boolean ting;
SemaphoreHandle_t mtxTing;
TaskHandle_t Midi;


typedef struct MidiNote
{
    int canal;
    int note;
    int vel;
    long duree;
} MidiNote;

void midiNotePrint(void *xStruct)
{
    MidiNote * data = (MidiNote *) xStruct;
    printf("canal : %d\n", data->canal);
    printf("note : %d\n", data->note);
    printf("vel : %d\n", data->vel);
    printf("duree : %d\n", data->duree);
}

void playMidiNote(void *xStruct){
   MidiNote * note = (MidiNote *) xStruct;
   const TickType_t xDelay = note->duree;
   midiNotePrint(note);
  Serial.println("Début Note");
   OscWiFi.send(host, send_port, "/midi/noteon", note->canal  , note->note, note->vel);
   vTaskDelay(note->duree);
   OscWiFi.send(host, send_port, "/midi/noteoff", note->canal  , note->note, note->vel);
   Serial.println("Fin Note");
   vTaskDelete(NULL);
   Serial.println("Fin Tâche");
}


void tskMidi (void * pvparameters){
  for (;;){
      //   Serial.println("tskMidi");
     if (ting) {
      xSemaphoreTake(mtxTFT, portMAX_DELAY);
      tft.setCursor(0,32);
      tft.fillCircle(40,100,30,TFT_GREEN);
      xSemaphoreGive(mtxTFT);

      xSemaphoreTake(mtxTing, portMAX_DELAY); 
      ting=false;
      xSemaphoreGive(mtxTing);
 //     Serial.println("OSC SEND NOTE ON");
 //     OscWiFi.send(host, send_port, "/midi/noteon",   1, 64, 120);
 //     delay(100);
 //     Serial.println("OSC SEND NOTE OFF");
 //     OscWiFi.send(host, send_port, "/midi/noteoff",   1, 64, 120);
  
      xSemaphoreTake(mtxTFT, portMAX_DELAY);
      tft.setCursor(0,32);
      tft.fillCircle(40,100,30,TFT_RED);
      xSemaphoreGive(mtxTFT);
     }
     delay(1);
}
}
