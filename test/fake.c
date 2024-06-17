
/*#include <Arduino_GFX_Library.h>
#include <math.h>  // Include math library to use sin function

// Define pin connections
#define TFT_DC 2
#define TFT_RST 4  // You can also connect this to the Arduino reset in which case, set this #define pin to -1!
#define TFT_CS 15

#define TFT_SCK 18
#define TFT_MOSI 23
#define TFT_MISO 19


// Create display object
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 tft = Arduino_ILI9341(&bus, TFT_RST);

void setup(void)
{

  tft.begin();
  tft.fillScreen(WHITE);
  tft.setCursor(20, 20);
  tft.setTextSize(2);
  tft.setTextColor(BLUE);

}

void loop(){}
*/