// Ecran
TFT_eSPI tft = TFT_eSPI();
SemaphoreHandle_t mtxTFT;


void clearScreen()
{
 tft.fillScreen(TFT_BLACK);
 tft.setCursor(0, 0);
 tft.setTextColor(TFT_GREEN); 
 tft.setTextSize(2);
 tft.println(en_tete);
}

void setupTFT()
{
 tft.init();
 tft.setRotation(1);
 clearScreen();
}
