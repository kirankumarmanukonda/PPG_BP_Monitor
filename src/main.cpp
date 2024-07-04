#include <main.h>

void setup() 
{
  Serial.begin(115200);

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
  
  // Draw initial axes or boundaries
  drawAxes();


}

int record_sample = 0;

// Total number of sample recorded
int total_record_samples;

// screen for the total_record_samples
int record_screens;

uint32_t bp_value;
float pressure_hPa;
void loop()
{
  validate_singleClick();

  if (OK_LongPressed)
  {
    OK_LongPressed = false;
    Serial.println("Long press detected");
    // Perform action for long press
   }
  if(OK_Pressed)
  {
    Serial.println("single ");
    OK_Pressed = false;
    if(selected == 1)
    {
      clear_graph();

      ppg_record = 0;
      sample = 0;
      record_sample = 0;
      history_flag = 0;
    }
    else if(selected == 2)
    {
      if(ppg_record)
      {
        ppg_record = 0;
        history_flag = 1;

        total_record_samples = record_sample;
        sample = 0;
        record_sample = 0;
        
        record_screens = ceil((double)total_record_samples/MAX_POINTS);
        
        clear_graph();
        draw_graph_screen(record_screens, ppg_bp_data, total_record_samples);
        show_ppg_bp(sample, ppg_bp_data[0][total_record_samples], ppg_bp_data[1][total_record_samples]);

      }
      else
        ppg_record = 1;
    }
    menu();
  }
  if(OK_DoubleClicked)
  {
    OK_DoubleClicked = false;

    selected = 1;
    menu();

    /*
    clear_graph();

    ppg_record = 0;
    sample = 0;
    record_sample = 0;
    history_flag = 0;
      
    */

    Serial.println("double ");
  }
  if(RIGHT_Pressed)
  {
    RIGHT_Pressed = false;
    
    if(history_flag)
    {
      sample++;
      //draw_indicator_line(sample);
      draw_graph(tft, ppg_bp_data[0][sample]);
      show_ppg_bp(sample, ppg_bp_data[0][sample], ppg_bp_data[1][sample]);
    }
    else
    {
      selected++;

      if (selected == 4)
        selected = 1;

      menu();
    }
  }
  if(LEFT_Pressed)
  {
    LEFT_Pressed = false;
    
    if(history_flag)
    {
      sample--;
      //draw_indicator_line(sample);
      draw_graph(tft, ppg_bp_data[0][sample]);
      show_ppg_bp(sample, ppg_bp_data[0][sample], ppg_bp_data[1][sample]);

    }
    else
    {
      selected--;

      if (selected == 0)
        selected = 3;

      menu();
    }
  }
  
  if(history_flag)
  {
    
    /*
    if(record_sample < total_record_samples)
    {
      draw_graph(tft, ppg_bp_data[0][sample]);
      show_ppg_bp(sample, ppg_bp_data[0][sample], ppg_bp_data[1][sample]);
      record_sample++;
    }
    else if(record_sample == total_record_samples)
    {
      sample = 0;
      draw_indicator_line(sample);
      record_sample++;
      
    }
    */
    
  }
  else
  {
    ppg_value = analogRead(PPG_PIN);
    pressure_hPa = mpr.readPressure();
    bp_value = -6.6417940048614935e+002 + 7.3911993532291342e-001 * pressure_hPa + 8.9635671910610964e-007 * pressure_hPa * pressure_hPa;

    if(ppg_record)
    {
      ppg_bp_data[0][record_sample] = ppg_value;
      ppg_bp_data[1][record_sample] = bp_value;
      record_sample++;
    }
    draw_graph(tft, ppg_value);
    
    // only show for each 5 samples to make is visible on screen
    if (sample % 5 == 1)
      show_ppg_bp(sample, ppg_value, bp_value);

    delay(10);
  }
}

