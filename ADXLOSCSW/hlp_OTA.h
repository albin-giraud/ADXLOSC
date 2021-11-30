SemaphoreHandle_t mtxOTA;
boolean maj=false;

void setupOTA()
{
   ArduinoOTA
    .onStart([]() 
    {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
      else // U_SPIFFS
      type = "filesystem";
      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      xSemaphoreTake(mtxOTA, portMAX_DELAY); 
      maj=true;
      xSemaphoreGive(mtxOTA);
      xSemaphoreTake(mtxTFT, portMAX_DELAY);
      tft.setCursor(0,32);
      tft.fillCircle(40,100,30,TFT_GREEN);
      xSemaphoreGive(mtxTFT);
      Serial.println("Start updating " + type);
    })
//???????????????????????
    .onEnd([]() 
    {
      Serial.println("\nEnd");
      xSemaphoreTake(mtxOTA, portMAX_DELAY); 
      maj=false;
      xSemaphoreGive(mtxOTA);
    })
//???????????????
  .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));

    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("OTA prêt");
  Serial.print("adresse IP : ");
  Serial.println(WiFi.localIP());
}
