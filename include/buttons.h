#ifndef BUTTONS_H
#define BUTTONS_H

// Button initializations
#define OK_BUTTON_PIN 14  // GPIO pin for Button

volatile bool OK_Pressed = false; // Flag for OK button pressed
volatile bool OK_LongPressed = false; // Flag for OK button long press
unsigned long lastDebounceTimeOK = 0; // Last debounce time
bool buttonPressed = false;           // State of the button

#define LONG_PRESS_DELAY 1000 // Min delay for long press
#define DEBOUNCE_DELAY  100  // Debounce time in milliseconds

void IRAM_ATTR handleOKPress() 
{
    unsigned long currentTime = millis();
    
    // Debounce logic
    if ((currentTime - lastDebounceTimeOK) > DEBOUNCE_DELAY) 
    {
        //Serial.print("change\n");
        if (!buttonPressed) 
        {
            buttonPressed = true;
        }
        else
        {
            if((currentTime - lastDebounceTimeOK) > LONG_PRESS_DELAY )
            {
                OK_LongPressed = true;
                //Serial.print("long");
            }
            else
            {
                OK_Pressed = true;
                //Serial.print("short");
            }
            
            buttonPressed = false;
        }
        lastDebounceTimeOK = currentTime;
    }
}


// Rotary encoder Initialization
#define ROT_A 13 // GPIO pin for Rotary Encoder A
#define ROT_B 35 // GPIO pin for Rotary Encoder B

int rot_count = 1;  // To count the movements of rotary encoder

// To get the status of the rot (movement is detected)
volatile bool rot_flag = false;

//aState, aLastState -> states of the A signal
int aState, aLastState;

// Decode the rotations in the rotary Knob
ICACHE_RAM_ATTR void rotary_handler()
{
    aState = digitalRead(ROT_A);
    if (aState != aLastState)
    {
        if (digitalRead(ROT_B) != aState)
        {
            rot_count++;
        }
        else
        {
            rot_count--;
        }

        rot_flag = true;
    }
    aLastState = aState;
}

#endif