
WebServer server(80);
TaskHandle_t Serveur;


void handleRoot() {
  server.send(200, "text/plain", "Serveur ok");
//  tft.println("Handle Root");
}

void handleNotFound() {
  String message = "Resource inconnue \n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void tskHandleServer (void * pvparameters)
{
  delay(1000);
  for (;;)
  {
  delay(100);
  server.handleClient();
  delay(100);
  }
}

void setupServer()
{
  if (MDNS.begin("neom"))
  {
   tft.println("MDNS responder OK");
  }
  server.on("/", handleRoot);
  server.on("/test", []()
   {
   server.send(200, "text/plain", "Test ok");
    //    tft.println("Test OK");
   });
   server.on("/preferences", []()
   {
    String strZX = "Zero X : "+((String) pref.getInt("zerox",0));
    String strZY = "Zero Y : "+((String) pref.getInt("zeroy",0));
    String strZZ = "Zero Z : "+((String) pref.getInt("zeroz",0));
    String strMX = "Max X : "+((String) pref.getInt("maxx",0));
    String strMY = "Max Y : "+((String) pref.getInt("maxy",0));
    String strMZ = "Max Z : "+((String) pref.getInt("maxz",0));
   String s = "Preferences : \n"+strZX+"\n"+strZY+"\n"+strZZ+"\n"+strMX+"\n"+strMY+"\n"+strMZ;
   server.send(200, "text/plain", s);
   });
     server.on("/reset", []()
   {
    pref.putInt("zerox", 0);
    pref.putInt("zeroy", 0);
    pref.putInt("zeroz", 0);
    pref.putInt("maxx", 0);
    pref.putInt("maxy", 0);
    pref.putInt("maxz", 0);
    initADXL();
   server.send(200, "text/plain", "Reset OK");
   });


//??????????????????????
  server.onNotFound(handleNotFound);
  server.begin();
  tft.println("HTTP OK");
  delay(2000);
  clearScreen();
}
