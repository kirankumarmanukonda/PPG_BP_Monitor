#ifndef BUTTONS_H
#define BUTTONS_H

// Button initializations
#define OK_BUTTON_PIN 14  // GPIO pin for Button 1
#define LEFT_BUTTON_PIN 12  // GPIO pin for Button 2
#define RIGHT_BUTTON_PIN 13  // GPIO pin for Button 3

volatile bool OK_DoubleClicked = false;

volatile bool OK_Pressed = false;
volatile bool OK_LongPressed = false; // Flag for OK button long press
unsigned long lastDebounceTimeOK = 0; // Last debounce time
unsigned long pressStartTimeOK = 0;   // Time when button press started
bool buttonPressed = false;           // State of the button


volatile bool LEFT_Pressed = false;
volatile bool RIGHT_Pressed = false;
volatile bool checkForSingleClick = false; 

#define LONG_PRESS_DELAY 1000
#define DOUBLE_CLICK_DELAY 400 // Max delay between clicks for double click
const unsigned long debounceDelay = 200;  // Debounce time in milliseconds


volatile unsigned long lastDebounceTimeLEFT = 0;
volatile unsigned long lastDebounceTimeRIGHT = 0;

unsigned long lastPressTimeOK = 0; 

// function continously validate the single click and double click if interrupt occured
void IRAM_ATTR validate_singleClick()
{
    if (checkForSingleClick)
    {
        if((millis() - lastPressTimeOK) > DOUBLE_CLICK_DELAY)
        {
            OK_Pressed = true;
            checkForSingleClick = false;
        }
    }
}


void IRAM_ATTR handleOKPress() {
    unsigned long currentTime = millis();
    
    // Debounce logic
    if ((currentTime - lastDebounceTimeOK) > debounceDelay) {
        // Button is pressed down
        if (!buttonPressed) {
            buttonPressed = true;
            pressStartTimeOK = currentTime;
        } 
        // Button is released
        else {
            buttonPressed = false;
            unsigned long pressDuration = currentTime - pressStartTimeOK;
            
            if (pressDuration >= LONG_PRESS_DELAY) {
                OK_LongPressed = true;
            } else {
                OK_Pressed = true;
            }
        }
        lastDebounceTimeOK = currentTime;
    }
}

/*
void IRAM_ATTR handleOKPress() 
{
    unsigned long currentTime = millis();
    
    if ((currentTime - lastDebounceTimeOK) > debounceDelay) 
    {
        if (checkForSingleClick) 
        {
            if ((currentTime - lastPressTimeOK) < DOUBLE_CLICK_DELAY) 
            {
                OK_DoubleClicked = true; // Double click detected
                checkForSingleClick = false; // Cancel single click check
            }
        } 
        else 
        {
            checkForSingleClick = true;
            lastPressTimeOK = currentTime;
        }
        lastDebounceTimeOK = currentTime;
    }
}
*/
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

/************************************************
   for rotary encoder
   count              -> to count the movements
   aState, aLastState -> states of the A signal
 ************************************************/
#define A 0
#define B 1

int count = 1;
int aState;
int aLastState;

void rot()
{
  aState = digitalRead(A);
  if (aState != aLastState)
  {
    if (digitalRead(B) != aState)
    {
      count ++;
      //Serial.println(count);
    }
    else
    {
      count --;
    }

  }
  aLastState = aState;
}

ICACHE_RAM_ATTR void intt()
{
    rot();
    //Serial.println("interruption");
}

#endif