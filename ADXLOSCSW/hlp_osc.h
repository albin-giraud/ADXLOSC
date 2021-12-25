// OSC
const char* host = "192.168.1.16";
const char* interne = "192.168.1.31";
const int port_interne = 11999;
//const char* host = "192.168.43.224";
const int send_port = 6448;
const int receive_port = 12000;

int zx, zy, zz; // Mesure temps zéro
int px, py, pz; // Mesure temps -1
int x, y, z; // Mesure calibrée
int vx,vy,vz; // vitesse 
int rx,ry,rz;
int peakx,peaky,peakz; // pic
int mabsx, mabsy, mabsz; // JT trouver les max en valeur absolue pour calibrer
PeakDetection peakDetectionX,peakDetectionY,peakDetectionZ;
int fenetreMoyenne = 10;
MovingAverage<int> moyenneX(fenetreMoyenne);
MovingAverage<int> moyenneY(fenetreMoyenne);
MovingAverage<int> moyenneZ(fenetreMoyenne);



TaskHandle_t OSC;

void tskParseOSC (void * pvparameters) {
  Serial.print("Début tâche OSC");
  for (;;) {
    delay(10);
    OscWiFi.parse();
  }
}


void setupOSC(){
OscWiFi.subscribe(receive_port, "/statut",[](const OscMessage& m){
        Serial.println(m.remoteIP());
        Serial.println(m.remotePort());
        Serial.println(m.address());
        Serial.println(" adresse ADLX ");
        Serial.print(WiFi.localIP());
}
 ); 


peakDetectionX.begin(); // A tuner
peakDetectionY.begin(); // A tuner
peakDetectionZ.begin(); // A tuner



/*
 * Traitement des données brutes et envoi à l'extérieur
 */
OscWiFi.subscribe(port_interne, "/interne",[](const OscMessage& m){


// On traite l'axe X         
        px = x; // On sauvegarder la valeur n-1
        rx = m.arg<int>(1); // On actualise la valeur n
        x=rx-zx; // On ajoute le zéro de référence
        x=constrain(map(x,-(mabsx-zx), mabsx-zx, 0, 127),0 , 127); // On mappe sur 0/127
//        vx=abs((x-px)/(momentpresent-momentpasse)); // On calcule la vitesse
//        vx=abs(x-px); // On calcule la vitesse
//        moyenneX.push(x); // On met à jour la moyenne glissante
//        peakDetectionX.add((double)x); // On met à jour la pile pour la détection du pic.
//        peakx = peakDetectionX.getPeak(); // On tente une détection

// On refait la même chose pour l'axe Y
        py = y; // On sauvegarder la valeur n-1
        ry = m.arg<int>(2); // On actualise la valeur n
        y=ry-zy; // On ajoute le zéro de référence
        y=constrain(map(y,-(mabsy-zy), mabsy-zy, 0, 127),0 , 127); // On mappe sur 0/127
//        vy=abs((y-py)/(momentpresent-momentpasse)); // On calcule la vitesse
//        vy=abs(y-py); // On calcule la vitesse
//        moyenneY.push(y); // On met à jour la moyenne glissante
//        peakDetectionY.add((double)y); // On met à jour la pile pour la détection du pic.
//        peaky = peakDetectionY.getPeak(); // On tente une détection

// On refait la même chose pour l'axe Z
        pz = z; // On sauvegarder la valeur n-1
        rz = m.arg<int>(3); // On actualise la valeur n
        z=rz-zz; // On ajoute le zéro de référence
        z=constrain(map(z,-(mabsz-zz), mabsz-zz, 0, 127),0 , 127); // On mappe sur 0/127
//        vz=abs((z-pz)/(momentpresent-momentpasse)); // On calcule la vitesse
//        vz=abs(z-pz); // On calcule la vitesse
//        moyenneZ.push(z); // On met à jour la moyenne glissante
//        peakDetectionZ.add((double)z); // On met à jour la pile pour la détection du pic.
//        peakz = peakDetectionZ.getPeak(); // On tente une détection

// On compose et envoie le message OSC
        OscWiFi.send(host, send_port, "/adxl",(float)millis(),(float)x,(float)y,(float)z);

//        OscWiFi.send(host, send_port, "/adxl",(float)millis(),(float)x,(float)vx,(float)peakx ,(float) moyenneX.get(),(float)rx,(float)y,(float)vy,(float) moyenneY.get(),(float)ry,(float)z,(float)vz,(float) moyenneZ.get(),(float)rz);
        }

 ); 

 
}
