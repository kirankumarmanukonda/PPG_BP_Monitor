#ifndef MAIN_H
#define MAIN_H
#include <graph.h>
#include <buttons.h>
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

// Array to hold ppg and bp data points
int ppg_bp_data[2][MAX_POINTS * MAX_REC_SCREENS]; // PPG , BP

// count the number of samples on screen
int sample;

// temporary varble to store the ppg value
int ppg_value;


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// 1  -> history mode 
// 0  -> normal mode
int history_flag = 0;


#endif