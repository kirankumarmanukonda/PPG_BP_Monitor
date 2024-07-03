#include <graph.h>

extern int sample;
extern int history_flag;

// calculated in the MAX_POINTS
int max_value; int max_graph_value = 4096;

// implemented in the graph
int min_value = 4096; int min_graph_value = 0;

// Coordinates for drawing line (X0, Y0) and (X1, Y1)
int X0 = GRAPH_X;
int Y0 = GRAPH_HEIGHT + GRAPH_Y;
int X1, Y1;

// Mapped ppg value according to Graph
int newValue;

void drawAxes() 
{
    tft.drawRect(GRAPH_X, GRAPH_Y-1, GRAPH_WIDTH, GRAPH_HEIGHT + 5, ILI9341_BLUE);
  //tft.drawLine(GRAPH_X, GRAPH_Y + GRAPH_HEIGHT, GRAPH_X + GRAPH_WIDTH, GRAPH_Y + GRAPH_HEIGHT, ILI9341_WHITE); // X-axis
  //tft.drawLine(GRAPH_X, GRAPH_Y + GRAPH_HEIGHT, GRAPH_X, GRAPH_Y, ILI9341_WHITE);  // Y-axis
}

// To plot the PPG Graph
void draw_graph(Adafruit_ILI9341 tft, int sensor_value)
{
    // clear the small Screen before plotin the new point
    tft.drawFastVLine(X0 + 2, GRAPH_Y, GRAPH_HEIGHT + 1, ILI9341_BLACK);
    
    // Map the sensor value to the Graph pixels in screen
    newValue = map(sensor_value, min_graph_value, max_graph_value, GRAPH_HEIGHT + GRAPH_Y, GRAPH_Y);

    // Assgining the peak values if it crossed in scaling
    if (newValue < GRAPH_Y)
        newValue = GRAPH_Y;

    if (newValue > GRAPH_HEIGHT + GRAPH_Y)
        newValue = GRAPH_HEIGHT + GRAPH_Y;

    // Drawing the line based on previous and current point
    X1 = sample + GRAPH_X;
    Y1 = newValue;
    tft.drawLine(X0, Y0, X1, Y1, ILI9341_DARKGREEN);
    X0 = X1;
    Y0 = Y1;

    // finding the Max and Min values for the graph scaling
    if (sensor_value > max_value)
        max_value = sensor_value;

    if (sensor_value < min_value)
        min_value = sensor_value;

    // if(!history_flag)
        sample++;

    if (sample == MAX_POINTS)
    {
        // reseting the sample counter and x position
        sample = 0;
        X0 = GRAPH_X;
        tft.drawRect(X0, GRAPH_Y, 5, GRAPH_HEIGHT, ILI9341_BLACK);

        // Setting the upper scale for graph
        max_graph_value = max_value + 50;
        if (max_graph_value > 4096)
            max_graph_value = 4096;

        // Setting lower scale for graph
        min_graph_value = min_value - 50;
        if (min_graph_value < 0)
            min_graph_value = 0;

        // resetting the max and min values for next screen
        max_value = 0;
        min_value = 4096;
    }
}


void draw_graph_screen(int screen_no, int ppg_bp_data[2][MAX_POINTS * MAX_REC_SCREENS], int total_samples)
{
    sample = 0;
    int index, indicator_sample;
    for(int i = 0; i < MAX_POINTS; i++)
    {
        index = i*screen_no;
        if(index < total_samples)
        {
            draw_graph(tft, ppg_bp_data[0][index]);
        }
        else if(index == total_samples)
            indicator_sample = i;
    }

    draw_indicator_line(indicator_sample);
    Serial.print("Scren graph printed !");

}

void clear_graph()
{
    tft.fillRect(GRAPH_X, GRAPH_Y, GRAPH_WIDTH, GRAPH_HEIGHT + 2, ILI9341_BLACK);
    X0 = GRAPH_X;
    Y0 = GRAPH_HEIGHT + GRAPH_Y;
    X1 = 0; Y1 = 0;
    delay(1000);
}

int old_sample;
void draw_indicator_line(int sample)
{
    tft.drawFastVLine(old_sample, GRAPH_Y, GRAPH_HEIGHT, ILI9341_BLACK);
    tft.drawFastVLine(sample, GRAPH_Y, GRAPH_HEIGHT, ILI9341_WHITE);
    old_sample = sample;
}