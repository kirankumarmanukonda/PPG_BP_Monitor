#include <main.h>
#include <gui.h>
#include <Wire.h>
#include "Adafruit_MPRLS.h"

//Pressure sensor Configurations
// You dont *need* a reset and EOC pin for most uses, so we set to -1 and don't connect
#define RESET_PIN -1  // set to any GPIO pin # to hard-reset on begin()
#define EOC_PIN -1    // set to any GPIO pin to read end-of-conversion by pin
#define BP_SDA 21     // GPIO of SDA for I2C
#define BP_SCL 22     // GPIO of SCL for I2C

Adafruit_MPRLS mpr = Adafruit_MPRLS(RESET_PIN, EOC_PIN);

#define PPG_PIN 26

// PPG , BP
int ppg_data[2][MAX_POINTS]; // Array to hold ppg_data points
int sample, ppg_value;

void setup() 
{
  // Setup Button OK
  pinMode(OK_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(OK_BUTTON_PIN), handleOKPress, FALLING);

  // Setup Button LEFT
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(LEFT_BUTTON_PIN), handleLEFTPress, FALLING);

  // Setup Button RIGHT
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(RIGHT_BUTTON_PIN), handleRIGHTPress, FALLING);

  //Turn on the LED of Display
  pinMode(32, OUTPUT);
  digitalWrite(32, 1);
  
  //Initialize the display
  tft.begin();
  tft.setRotation(1); // Set display rotation
  tft.fillScreen(ILI9341_BLACK); // Fill screen with black to clear Screen

  loading_screen();
  
  //Initialize the Pressure sensor
  while (!mpr.begin()) 
  {
    tft.setTextColor(ILI9341_CYAN);
    tft.setCursor(BP_BOX_X + 10, BP_BOX_Y + 15); 
    tft.println("BP Sensor is Failed !");
    delay(1000);
  }
  
  // For PPG sensor Signal
  pinMode(PPG_PIN, INPUT);
  
  menu();
  
  initialize_BP_PPG_display();
  
  // Draw initial axes
  //drawAxes();

  // for BP and PPG readings
  tft.setTextSize(3);
}


uint32_t bp;
float pressure_hPa;
void loop()
{
  if(OK_Pressed)
  {
    OK_Pressed = false;
    if(selected == 1)
    {
      ppg_record = 0;

    }
    else if(selected == 2)
    {
      if(ppg_record)
        ppg_record = 0;
      else
        ppg_record = 1;
    }
    menu();
    //delay(200);
  }
  if(RIGHT_Pressed)
  {
    RIGHT_Pressed = false;
    selected++;
    
    if(selected == 3)
      selected = 1;
    
    menu();
    //delay(50);
  }
  if(LEFT_Pressed)
  {
    LEFT_Pressed = false;
    selected--;
    
    if(selected == 0)
      selected = 2;
    
    menu();
    //delay(1000);
  }
  
  ppg_value = analogRead(PPG_PIN);
  pressure_hPa = mpr.readPressure();
  bp = -6.6417940048614935e+002 + 7.3911993532291342e-001 * pressure_hPa + 8.9635671910610964e-007 * pressure_hPa * pressure_hPa;
  
  //if(ppg_record)
  //  ppg_data[sample] = ppg_value;
  
  draw_graph(tft, ppg_value);

    if(sample % 5 == 1)
  {
    tft.setTextColor(ILI9341_DARKGREEN);
    tft.fillRoundRect(PPG_BOX_X, PPG_BOX_Y + 10, 80, 35, 0, ILI9341_BLACK);
    tft.setCursor(PPG_BOX_X + 5, PPG_BOX_Y + 15); 
    tft.println(ppg_value);

    tft.setTextColor(ILI9341_CYAN);
    tft.fillRoundRect(BP_BOX_X, BP_BOX_Y + 10, 80, 35, 0, ILI9341_BLACK);
    tft.setCursor(BP_BOX_X + 10, BP_BOX_Y + 15); 
    tft.println(bp);
  }

  delay(10);
}

