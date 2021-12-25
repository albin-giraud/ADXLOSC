// ADXL
const int xpin = 36;
const int ypin = 33;
const int zpin = 32;
const int BPpin = 35;   //  JT
int seuil = 300;
int duree = 100;
int x,y,z; //  Mesure temps t
int zx, zy, zz; // Mesure temps zéro
int px, py, pz; // Mesure temps -1
int bx, by, bz; // Mesure brute
int vx,vy,vz; // vitesse 
int mabsx, mabsy, mabsz; // JT trouver les max en valeur absolue pour calibrer
long temps_present; // JT
Preferences pref;
TaskHandle_t Acquisition;
int dureeMEP = 3000; // Durée de mise en place avant le lancement de l'action de calibration
int dureeRAZ = 2000; // Durée de la mise à zéro
int dureeMAX = 6000; // Durée de la calibration max
int dureeINIT = 1000; // Durée de mise à jour des préférences.
boolean calibration = false;
SemaphoreHandle_t mtxCalib;
PeakDetection peakDetectionX;
int fenetreMoyenne = 20;
MovingAverage<int> moyenneX(fenetreMoyenne);
MovingAverage<int> moyenneY(fenetreMoyenne);
MovingAverage<int> moyenneZ(fenetreMoyenne);


void tskAcquisition (void * pvparameters) {
  peakDetectionX.begin();
  long momentpresent, momentpasse;
  momentpresent=millis();
  delay(6); // créer du passé...
  for (;;) {
    momentpasse=momentpresent;
    momentpresent=millis();    
        px = x;
        py = y;
        pz = z;
        bx=analogRead(xpin);
        x=bx-zx;
        delay(1);                 // JT
        x=constrain(map(x,-(mabsx-zx), mabsx-zx, 0, 127),0 , 127);
        vx=abs((x-px)/(momentpresent-momentpasse));
        moyenneX.push(x);
        peakDetectionX.add((double)x);
        int peakx = peakDetectionX.getPeak();
        by=analogRead(ypin);
        y=by-zy; 
        delay(1);                 // JT
        y=constrain(map(y,-(mabsy-zy), mabsy-zy, 0, 127),0 , 127);
        vy=abs((y-py)/(momentpresent-momentpasse));
        moyenneY.push(y);
        bz=analogRead(zpin);
        z=bz-zz; 
        delay(1);                            // JT  
        z=constrain(map(z,-(mabsz-zz), mabsz-zz, 0, 127),0 , 127);    
        vz=abs((z-pz)/(momentpresent-momentpasse));
        moyenneZ.push(z);

      xSemaphoreTake(mtxTFT, portMAX_DELAY);
      tft.fillRect(0, 32, 240, 18, TFT_BLACK);
      int w = map(x, 0, 250, 0, tft.width());
      tft.fillRect(0, 32, w, 18, TFT_YELLOW);
      xSemaphoreGive(mtxTFT);

      OscWiFi.send(host, send_port, "/adxl",(float)momentpresent,(float)x,(float)vx,(float)peakx ,(float) moyenneX.get(),(float)bx,(float)y,(float)vy,(float) moyenneY.get(),(float)by,(float)z,(float)vz,(float) moyenneZ.get(),(float)bz);
  }
}

void calibrationZero() {
  int cx=0;
  int cy=0;
  int cz=0;
  int nbMesure=0;
  zx=0;
  zy=0;
  zz=0;
  printf("%d : Début calibration zéro \n",millis());
  temps_present = millis();
  while (millis() - temps_present < dureeRAZ){
//  for (int i = 0; i < 4; i++) {
    nbMesure=nbMesure+1;
    cx = analogRead(xpin);               // JT
    delay(1);                            // JT
    cy = analogRead(ypin);               // JT
    delay(1);                            // JT
    cz = analogRead(zpin);               // JT
    delay(1);                            // JT
    zx += cx;                             // JT
    zy += cy;                             // JT
    zz += cz;                             // JT
    delay(20);
//   Serial.println("Lecture X = indice "+String(nbMesure)+" valeur cx : "+String(cx)+" valeur cumulée zx : "+String(zx));
//   Serial.println("Lecture Y = indice "+String(nbMesure)+" valeur cy : "+String(cy)+" valeur cumulée zy : "+String(zy));
//   Serial.println("Lecture Z = indice "+String(nbMesure)+" valeur cz : "+String(cz)+" valeur cumulée zz : "+String(zz));
  }
  zx = zx / nbMesure;
  zy = zy / nbMesure;
  zz = zz / nbMesure;
  pref.clear();
  pref.putInt("zerox", zx); //JT
  pref.putInt("zeroy", zy); //JT
  pref.putInt("zeroz", zz); //JT
  printf("%d : Fin calibration zéro \n",millis());
}

void calibrationMaximum() {
  printf("%d : Début calibration max \n",millis());
  temps_present = millis();
  mabsx=0; // On supprime les valeurs actuelles
  mabsy=0;
  mabsz=0;
  int mx;
  int my;
  int mz;
  while ( millis() - temps_present < dureeMAX) //attend 4 secondes pendant qu'on recherche le max
  {
    mx = analogRead(xpin);               // JT
    delay(1);                            // JT
    my = analogRead(ypin);               // JT
    delay(1);                            // JT
    mz = analogRead(zpin);               // JT
    delay(1);                            // JT
    mabsx = max(mabsx, abs(mx));
    mabsy = max(mabsy, abs(my));
    mabsz = max(mabsz, abs(mz));
//   Serial.println("Lecture X = valeur px : "+String(mx)+" valeur zx : "+String(zx)+" valeur mabsx : "+String(mabsx));
//   Serial.println("Lecture Y = valeur py : "+String(my)+" valeur zy : "+String(zy)+" valeur mabsy : "+String(mabsy));
//   Serial.println("Lecture Z = valeur pz : "+String(mz)+" valeur zz : "+String(zz)+" valeur mabsz : "+String(mabsz));

  }
  pref.putInt("maxx", mabsx); //JT
  pref.putInt("maxy", mabsy); //JT
  pref.putInt("maxz", mabsz); //JT
  delay(2);
  printf("%d : Fin calibration max \n",millis());
}

void initADXL() {
printf("%d : Début initialisation de préférences \n",millis());

  mabsx = pref.getInt("maxx", 0); //JT
  mabsy = pref.getInt("maxy", 0); //JT
  mabsz = pref.getInt("maxz", 0); //JT
  zx = pref.getInt("zerox", 0); //JT
  zy = pref.getInt("zeroy", 0); //JT
  zz = pref.getInt("zeroz", 0); //JT
//  px = analogRead(xpin) - zx; // JT
//  delay(1);
//  px = constrain(map(px, -mabsx, mabsx, 0, 127), 0 , 127);
//  py = analogRead(ypin) - zy; // JT
//  delay(1);                 // JT
//  py = constrain(map(py, -mabsy, mabsy, 0, 127), 0 , 127);
//  pz = analogRead(zpin) - zz; // JT
//  delay(1);                            // JT
//  pz = constrain(map(pz, -mabsz, mabsz, 0, 127), 0 , 127);
//  x = px;
//  y = py;
//  z = pz;
printf("%d : Fin initialisation des préférences \n",millis());
}
