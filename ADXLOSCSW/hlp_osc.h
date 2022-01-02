int fenetreMoyenne = pref.getInt("PopMoyenne",10);
MovingAverage<int> moyenneX(fenetreMoyenne);
MovingAverage<int> moyenneY(fenetreMoyenne);
MovingAverage<int> moyenneZ(fenetreMoyenne);

void tskParseOSC (void * pvparameters) {
  Serial.print("Début tâche OSC");
  for (;;) {
    OscWiFi.parse();
  }
}



void cbParam(const OscMessage& m) {
  String param = m.arg<String>(0);
  Serial.println(m.address());
  Serial.println(param);

  if (param == "ZeroX") {
    pref.putInt("ZeroX", m.arg<int>(1));
  }
  else if (param == "ZeroY") {
    pref.putInt("ZeroY", m.arg<int>(1));
  }
  else if (param == "ZeroZ") {
    pref.putInt("ZeroZ", m.arg<int>(1));
  }
  else if (param == "MaxX") {
    pref.putInt("MaxX", m.arg<int>(1));
  }
  else if (param == "MaxY") {
    pref.putInt("MaxY", m.arg<int>(1));
  }
  else if (param == "MaxZ") {
    pref.putInt("MaxZ", m.arg<int>(1));
  }
   else if (param == "PeakDetectLag") {
    pref.putInt("PeakDetectLag", m.arg<int>(1));
  }
   else if (param == "PeakDetectThrs") {
    pref.putInt("PeakDetectThrs", m.arg<int>(1));
  }
   else if (param == "PeakDetectInfluence") {
    pref.putDouble("PeakDetectInfluence", m.arg<double>(1));
  }
   else if (param == "PopMoyenne") {
    pref.putInt("PopMoyenne", m.arg<int>(1));
  }

}

void afficherParam(){
  clearScreen();
  int hauteur = 17;
  int largeur = 122;
  tft.setTextSize(2);
  // X
  tft.setCursor(0, hauteur);
  tft.setTextColor(TFT_CYAN); 
  tft.printf("ZX : %i XM : %i",zx, mabsx);

  // Y
  tft.setTextColor(TFT_MAGENTA); 
  tft.setCursor(0, hauteur*2);
  tft.printf("ZY : %i YM : %i",zy, mabsy);
  
  // Z
  tft.setTextColor(TFT_YELLOW); 
  tft.setCursor(0, hauteur*3);
  tft.printf("ZZ : %i ZM : %i",zz, mabsz);
  
  // PeakDetection
  tft.setTextColor(TFT_ORANGE); 
  tft.setCursor(0, hauteur*5);
  tft.printf("L %i - T %i - I %.2f",peakDetectionX.lag,peakDetectionX.threshold,peakDetectionX.influence);
  
}

void cbStatut(const OscMessage& m) {
  afficherParam();
  Serial.println(m.remoteIP());
  Serial.println(m.remotePort());
  Serial.println(m.address());
  Serial.println(" adresse ADLX ");
  Serial.println(WiFi.localIP());
  Serial.println(pref.getInt("ZeroX", 0));
  Serial.println(pref.getInt("ZeroY", 0));
  Serial.println(pref.getInt("ZeroZ", 0));
  Serial.println(pref.getInt("MaxX", 0));
  Serial.println(pref.getInt("MaxY", 0));
  Serial.println(pref.getInt("MaxZ", 0));
  Serial.println(pref.getInt("PeakDetectLag", 0));
  Serial.println(pref.getInt("PeakDetectThrs", 0));
  Serial.println(pref.getDouble("PeakDetectInfluence", 0));
  Serial.println(pref.getInt("PopMoyenne", 0));
}

void cbCalcul(const OscMessage& m) {
  // On traite l'axe X
  px = x; // On sauvegarder la valeur n-1
  rx = m.arg<int>(1); // On actualise la valeur n
  x = rx - zx; // On ajoute le zéro de référence
  x = constrain(map(x, -(mabsx - zx), mabsx - zx, 0, 127), 0 , 127); // On mappe sur 0/127
  vx = abs(x - px); // On calcule la vitesse
  moyenneX.push(x); // On met à jour la moyenne glissante
  peakDetectionX.add((double)x); // On met à jour la pile pour la détection du pic.
  peakx = peakDetectionX.getPeak(); // On tente une détection

  // On refait la même chose pour l'axe Y
  py = y; // On sauvegarder la valeur n-1
  ry = m.arg<int>(2); // On actualise la valeur n
  y = ry - zy; // On ajoute le zéro de référence
  y = constrain(map(y, -(mabsy - zy), mabsy - zy, 0, 127), 0 , 127); // On mappe sur 0/127
  vy = abs(y - py); // On calcule la vitesse
  moyenneY.push(y); // On met à jour la moyenne glissante
  peakDetectionY.add((double)y); // On met à jour la pile pour la détection du pic.
  peaky = peakDetectionY.getPeak(); // On tente une détection

  // On refait la même chose pour l'axe Z
  pz = z; // On sauvegarder la valeur n-1
  rz = m.arg<int>(3); // On actualise la valeur n
  z = rz - zz; // On ajoute le zéro de référence
  z = constrain(map(z, -(mabsz - zz), mabsz - zz, 0, 127), 0 , 127); // On mappe sur 0/127
  vz = abs(z - pz); // On calcule la vitesse
  moyenneZ.push(z); // On met à jour la moyenne glissante
  peakDetectionZ.add((double)z); // On met à jour la pile pour la détection du pic.
  peakz = peakDetectionZ.getPeak(); // On tente une détection

  // On compose et envoie le message OSC
  //OscWiFi.send(ipcible, send_port, "/adxl", (float)millis(), (float)x, (float)y, (float)z);

  OscWiFi.send(ipcible, send_port, "/adxl", (float)millis(), (float)x, (float)vx, (float)peakx , (float) moyenneX.get(), (float)rx, (float)y, (float)vy, (float)peaky , (float) moyenneY.get(), (float)ry, (float)z, (float)vz, (float)peakz , (float) moyenneZ.get(), (float)rz);
}

void initPeakDetection(){
  peakDetectionX.begin(pref.getInt("PeakDetectLag",24),pref.getInt("PeakDetectThrs",2),pref.getDouble("PeakDetectInfluence",0.5)); // A tuner
  peakDetectionY.begin(pref.getInt("PeakDetectLag",24),pref.getInt("PeakDetectThrs",2),pref.getDouble("PeakDetectInfluence",0.5)); // A tuner
  peakDetectionZ.begin(pref.getInt("PeakDetectLag",24),pref.getInt("PeakDetectThrs",2),pref.getDouble("PeakDetectInfluence",0.5)); // A tuner
}

void cbRaz(){
  clearScreen();
  tft.drawString("RAZ",0,20);
  ESP.restart();
}


void setupOSC() {

 initPeakDetection();

  OscWiFi.subscribe(receive_port, "/statut", cbStatut);
  OscWiFi.subscribe(receive_port, "/param", cbParam);
  OscWiFi.subscribe(port_interne, "/interne", cbCalcul);
  OscWiFi.subscribe(receive_port, "/razpique", initPeakDetection);
  OscWiFi.subscribe(receive_port, "/raz", cbRaz);
  
}
