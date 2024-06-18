#include <main.h>

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Graph dimensions and position
#define GRAPH_X 50
#define GRAPH_Y 100
#define GRAPH_WIDTH 270
#define GRAPH_HEIGHT 140

// Define the maximum number of ppg_data points to display on the screen
#define MAX_POINTS GRAPH_WIDTH

// Pressure Reading box
#define BP_BOX_X 0
#define BP_BOX_Y 0

int ppg_data[MAX_POINTS]; // Array to hold ppg_data points

// Function declarations
void drawAxes();
void plotGraph(int);
void initialize_plot();
int newValue;
void setup() 
{
  Serial.begin(115200);

  //Turn on the LED
  pinMode(32, OUTPUT);
  digitalWrite(32, 1);

  // For PPG sensor
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);

  pinMode(27, OUTPUT);
  digitalWrite(27, 1);
  
  pinMode(26, INPUT);

  initialize_plot();

  //Initialize the display
  tft.begin();
  tft.setRotation(1); // Set display rotation
  tft.fillScreen(ILI9341_BLACK); // Fill screen with black
  
  // Draw the BP value and a Box
  tft.setCursor(BP_BOX_X, BP_BOX_Y);  // Set position (x,y)
  tft.setTextColor(0x07FF);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(2);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println(" BP ");
  tft.drawRoundRect(BP_BOX_X, BP_BOX_Y + 20, 50, 50, 8, 0x07FF);

  tft.setCursor(BP_BOX_X + 10, BP_BOX_Y + 40);
  tft.setTextSize(2); 
  tft.println("900");
  
  // Draw initial axes
  //drawAxes();
}

void loop() 
{
  //static float angle = 90.0; // Initial angle for sine wave
  // Generate a new sine wave value
  //int newValue = GRAPH_Y + GRAPH_HEIGHT / 2 + (sin(angle) * (GRAPH_HEIGHT / 2)); // Sine wave mapped to graph height
  //angle += 0.1; // Increment angle for next point

  newValue = map(analogRead(26), 0, 4096, GRAPH_HEIGHT + GRAPH_Y, GRAPH_Y);

  // Erase the previous graph by drawing it in black
  plotGraph(1);

  // Shift the previous ppg_data points to the left
  for (int i = 0; i < MAX_POINTS - 1; i++) 
    ppg_data[i] = ppg_data[i + 1];

  // Add the new value to the array
  ppg_data[MAX_POINTS - 1] = newValue;

  // Plot the new graph
  plotGraph(0);
  

}

void drawAxes() 
{
  //tft.drawLine(GRAPH_X, GRAPH_Y + GRAPH_HEIGHT, GRAPH_X + GRAPH_WIDTH, GRAPH_Y + GRAPH_HEIGHT, ILI9341_WHITE); // X-axis
  //tft.drawLine(GRAPH_X, GRAPH_Y + GRAPH_HEIGHT, GRAPH_X, GRAPH_Y, ILI9341_WHITE);  // Y-axis
}

void plotGraph(int clear) 
{
  for (int i = 0; i < MAX_POINTS - 1; i++) 
  {
    int x0 = GRAPH_X + i;
    int y0 = ppg_data[i];
    int x1 = GRAPH_X + (i + 1);
    int y1 = ppg_data[i + 1];
    
    if(clear)
      tft.drawLine(x0, y0, x1, y1, ILI9341_BLACK); // Erase the previous graph with black color
    else
      tft.drawLine(x0, y0, x1, y1, ILI9341_RED); // Red color
  }
}

void initialize_plot()
{
  for(int i = 0; i < MAX_POINTS; i++)
  {
    ppg_data[i] = GRAPH_HEIGHT + GRAPH_Y;
  }
}