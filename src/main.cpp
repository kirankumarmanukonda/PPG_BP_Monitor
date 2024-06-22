#include <main.h>

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Pressure Reading box
#define BP_BOX_X 70
#define BP_BOX_Y 5
#define PPG_BOX_X  BP_BOX_X + 100
#define PPG_BOX_Y BP_BOX_Y

int ppg_data[MAX_POINTS]; // Array to hold ppg_data points
int sample, sensor_value;

void initialize_BP_PPG_display()
{
  // Draw the BP value and a Box
  tft.setCursor(BP_BOX_X, BP_BOX_Y);  // Set position (x,y)
  tft.setTextColor(0x07FF);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("     BP ");
  //tft.drawRoundRect(BP_BOX_X, BP_BOX_Y + 20, 45, 45, 8, 0x07FF);

  tft.setCursor(BP_BOX_X + 5, BP_BOX_Y + 15);
  tft.setTextSize(3); 
  tft.println("---");

  // Draw the PPG value and a Box
  tft.setCursor(PPG_BOX_X, PPG_BOX_Y);  // Set position (x,y)
  tft.setTextColor(ILI9341_DARKGREEN);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("   PPG");
  //tft.drawRoundRect(PPG_BOX_X, PPG_BOX_Y + 20, 45, 45, 8, ILI9341_DARKGREEN);

  tft.setCursor(PPG_BOX_X + 5, PPG_BOX_Y + 15);
  tft.setTextSize(3); 
  tft.println("---");
}

int selected = 1;
void menu()
{
  //tft.drawLine(0, SCREEN_HEIGHT - 39 , SCREEN_WIDTH, SCREEN_HEIGHT - 39, ILI9341_WHITE);
  
  //tft.drawRoundRect(0, SCREEN_HEIGHT - 40, 50, 40, 5, ILI9341_BLUE);
  int gap = 10;
  int menu_x = 20;
  int menu_width = 50;
  int menu_height = 40;
  for(int i = 0; i < 5; i++)
  {
    if(selected == i)
      tft.fillRoundRect(i*menu_width + i*gap + menu_x, SCREEN_HEIGHT - menu_height, menu_width, menu_height, 10, ILI9341_BLUE);
    else
      tft.fillRoundRect(i*menu_width + i*gap + menu_x, SCREEN_HEIGHT - menu_height, menu_width, menu_height, 10, ILI9341_DARKGREY);
  }
  //tft.drawBitmap();
  //tft.drawRGBBitmap();

}



void setup() 
{
  Serial.begin(115200);

  //Turn on the LED
  pinMode(32, OUTPUT);
  digitalWrite(32, 1);

  // For PPG sensor GND
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);

  // For PPG sensor VCC
  pinMode(27, OUTPUT);
  digitalWrite(27, 1);
  
  // For PPG sensor Signal
  pinMode(26, INPUT);

  //Initialize the display
  tft.begin();
  tft.setRotation(1); // Set display rotation
  tft.fillScreen(ILI9341_BLACK); // Fill screen with black
  
  initialize_BP_PPG_display();
  menu();

  // Draw initial axes
  drawAxes();
}


void loop()
{
  sensor_value = analogRead(26);
  
  if(sample % 5 == 1)
  {
    tft.fillRoundRect(PPG_BOX_X, PPG_BOX_Y + 10, 80, 35, 0, ILI9341_BLACK);
    tft.setCursor(PPG_BOX_X + 5, PPG_BOX_Y + 15);
    tft.setTextSize(3); 
    tft.println(sensor_value);
  }
  
  draw_graph(tft, sensor_value);

  delay(10);
}

