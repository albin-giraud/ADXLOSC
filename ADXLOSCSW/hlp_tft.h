// Ecran
TFT_eSPI tft = TFT_eSPI();

void clearScreen()
{
 tft.fillScreen(TFT_BLACK);
 tft.setTextColor(TFT_GREENYELLOW); 
 tft.setTextSize(2);
 tft.drawString(en_tete,0,0);
}

void setupTFT()
{
 tft.init();
 tft.setRotation(1);
 clearScreen();
}
