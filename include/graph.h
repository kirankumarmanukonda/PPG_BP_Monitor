#ifndef GRAPH_H
#define GRAPH_H

#include <tft.h>

// Graph dimensions and position
#define GRAPH_X 0
#define GRAPH_Y 50
#define GRAPH_WIDTH 320
#define GRAPH_HEIGHT 140

// Define the maximum number of ppg_data points to display on the screen
#define MAX_POINTS GRAPH_WIDTH

#define MAX_REC_SCREENS 5

// Function declarations
void drawAxes();
void draw_graph(Adafruit_ILI9341 tft, int sensor_value, int inc_flag);
void clear_graph();
void draw_indicator_line(int sample, int start);
void draw_graph_screen(int screen_no, int ppg_bp_data[2][MAX_POINTS * MAX_REC_SCREENS], int total_samples);
void store_extreme();
#endif

