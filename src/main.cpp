#include <main.h>

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// Graph dimensions and position
#define GRAPH_WIDTH 300
#define GRAPH_HEIGHT 200
#define GRAPH_X 10
#define GRAPH_Y 20

// Define the maximum number of data points to display on the screen
#define MAX_POINTS GRAPH_WIDTH

int data[MAX_POINTS]; // Array to hold data points

// Function declarations
void drawAxes();
void plotGraph(int);

void setup() 
{
  pinMode(32, OUTPUT);
  digitalWrite(32, 1);

  //Initialize the display
  tft.begin();
  tft.setRotation(1); // Set display rotation
  tft.fillScreen(ILI9341_BLACK); // Fill screen with black
  
  // Draw initial axes
  drawAxes();
}

void loop() 
{
  static float angle = 0.0; // Initial angle for sine wave

  // Generate a new sine wave value
  int newValue = GRAPH_Y + GRAPH_HEIGHT / 2 + (sin(angle) * (GRAPH_HEIGHT / 2)); // Sine wave mapped to graph height
  angle += 0.1; // Increment angle for next point

  // Erase the previous graph by drawing it in black
  plotGraph(1);

  // Shift the previous data points to the left
  for (int i = 0; i < MAX_POINTS - 1; i++) 
  {
    data[i] = data[i + 1];
  }

  // Add the new value to the array
  data[MAX_POINTS - 1] = newValue;

  // Plot the new graph
  plotGraph(0);

  // Delay for demonstration (adjust based on your requirements)
  delay(50);
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
    int y0 = data[i];
    int x1 = GRAPH_X + (i + 1);
    int y1 = data[i + 1];

    if(clear)
        tft.drawLine(x0, y0, x1, y1, ILI9341_BLACK); // Erase the previous graph with black color
    else
    tft.drawLine(x0, y0, x1, y1, ILI9341_RED); // Red color
  }
}
