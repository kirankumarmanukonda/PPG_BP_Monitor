#ifndef TFT_H
#define TFT_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Define pin connections
#define TFT_DC 2
#define TFT_RST 4  // You can also connect this to the Arduino reset in which case, set this #define pin to -1!
#define TFT_CS 15

// Create display object
extern Adafruit_ILI9341 tft;

/*
 * ESP32 with the ILI9341 display
 * 
 * Pin Configuration
 * LED =   32
 * SCK =   18
 * SDI =   23
 * D/C =   2
 * RESET = 4 or RST or 3.3V
 * CS =    15
 * GND =   GND
 * VCC =   5V or 3.3V (the display has it's own 3.3V regulator)
 *
 *  Common colors:
 * BLACK    0x0000
 * BLUE     0x001F
 * RED      0xF800
 * GREEN    0x07E0
 * CYAN     0x07FF
 * MAGENTA  0xF81F
 * YELLOW   0xFFE0
 * WHITE    0xFFFF
 * 
 * 
*/

#endif