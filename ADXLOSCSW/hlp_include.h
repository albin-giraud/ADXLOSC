#include <MovingAverage.h>
#include <ArduinoOSC.h>
#include "PeakDetection.h"
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoOTA.h>
#include <Preferences.h>
#include "Button2.h"

// spécifique au projet
//#include "hlp_freertos.h"
#include "hlp_tft.h"
#include "hlp_wifi.h"
#include "hlp_OTA.h"
#include "hlp_osc.h"
#include "hlp_midi.h"
#include "hlp_adxl.h"
#include "hlp_web.h"
#include "hlp_bouton.h"
