// ADXL
const int xpin = 36;
const int ypin = 33;
const int zpin = 32;
int bx,by,bz; //  Mesure temps t
TaskHandle_t Acquisition;

void tskAcquisition (void * pvparameters) {
  for (;;) {    
       bx=analogRead(xpin);
       by=analogRead(ypin);
       bz=analogRead(zpin);
        OscWiFi.send(interne, port_interne, "/interne",(long)millis(),(int)bx,(int)by,(int)bz);
//        OscWiFi.send(host, send_port, "/adxl",(float)millis(),(float)bx,(float)by,(float)bz);
  }
}
