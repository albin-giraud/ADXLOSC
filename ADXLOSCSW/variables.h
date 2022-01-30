Preferences pref;
String en_tete= "30/01/2022-2";
//const char* host = "192.168.1.16";
String ipcible = "192.168.1.18";
//String ipcible = "192.168.43.224";
const char* interne = "192.168.1.23";
//const char* interne = "192.168.43.253";
const int port_interne = 11999;
//const char* host = "192.168.43.224";
const int send_port = 6448;
const int receive_port = 12000;
int zx, zy, zz; // Mesure temps zéro
int px, py, pz; // Mesure temps -1
int x, y, z; // Mesure calibrée
int vx, vy, vz; // vitesse
int rx, ry, rz; // ???
int peakx, peaky, peakz; // pic
int mabsx, mabsy, mabsz; // JT trouver les max en valeur absolue pour calibrer
PeakDetection peakDetectionX, peakDetectionY, peakDetectionZ;
TaskHandle_t OSC;
const int xpin = 36;
const int ypin = 33;
const int zpin = 32;
int bx,by,bz; //  Mesure temps t
TaskHandle_t Acquisition;
