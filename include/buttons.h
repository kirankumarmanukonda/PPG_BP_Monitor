#ifndef BUTTONS_H
#define BUTTONS_H

// Button initializations
#define OK_BUTTON_PIN 14  // GPIO pin for Button 1
#define LEFT_BUTTON_PIN 12  // GPIO pin for Button 2
#define RIGHT_BUTTON_PIN 13  // GPIO pin for Button 3

volatile bool OK_Pressed = false;
volatile bool LEFT_Pressed = false;
volatile bool RIGHT_Pressed = false;

const unsigned long debounceDelay = 300;  // Debounce time in milliseconds

volatile unsigned long lastDebounceTimeOK = 0;
volatile unsigned long lastDebounceTimeLEFT = 0;
volatile unsigned long lastDebounceTimeRIGHT = 0;

void IRAM_ATTR handleOKPress() {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTimeOK) > debounceDelay) {
        OK_Pressed = true;
        lastDebounceTimeOK = currentTime;
    }
}

void IRAM_ATTR handleLEFTPress() {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTimeLEFT) > debounceDelay) {
        LEFT_Pressed = true;
        lastDebounceTimeLEFT = currentTime;
    }
}

void IRAM_ATTR handleRIGHTPress() {
    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTimeRIGHT) > debounceDelay) {
        RIGHT_Pressed = true;
        lastDebounceTimeRIGHT = currentTime;
    }
}

#endif