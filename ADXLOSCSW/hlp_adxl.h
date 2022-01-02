void tskAcquisition (void * pvparameters) {
  const TickType_t xDelay = 1 / portTICK_PERIOD_MS;
  for (;;) {    
       bx=analogRead(xpin);
       vTaskDelay( xDelay );
       by=analogRead(ypin);
       vTaskDelay( xDelay );
       bz=analogRead(zpin);
       vTaskDelay( xDelay );
       OscWiFi.send(interne, port_interne, "/interne",(long)millis(),(int)bx,(int)by,(int)bz);
       vTaskDelay( xDelay );
  }
}
