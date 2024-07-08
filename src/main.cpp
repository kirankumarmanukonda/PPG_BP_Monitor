#include <main.h>

void setup() 
{
  Serial.begin(115200);

  // Setup Button OK
  pinMode(OK_BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(OK_BUTTON_PIN), handleOKPress, CHANGE);

  //Setup Rotary Encoder A
  pinMode(ROT_A, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROT_A), rotary_handler, CHANGE);

  // Setup Rotary Encoder B
  pinMode(ROT_B, INPUT);
  attachInterrupt(digitalPinToInterrupt(ROT_B), rotary_handler, CHANGE);
  aLastState = digitalRead(ROT_A);
  
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

// A varible to count recorded samples
int record_sample = 0;

// Total number of sample recorded
int total_record_samples;

// screen for the total_record_samples ranges from 1 to n
int record_screens;

// current showing screen
int current_screen;

uint32_t bp_value;
float pressure_hPa;
void loop()
{
  if (OK_LongPressed)
  {
    OK_LongPressed = false;
    if(history_flag)
    {
      // history_flag = 0;
      
      // rot_count = 1;
      // clear_graph();
      // menu();
    }
    //Serial.println("Long press");
  }

  if(rot_flag)
  {
    rot_flag = false;
    
    if(history_flag)
    {
      // adjust the counter in a range 0 to MAX_POINTS
      if (rot_count > MAX_POINTS)
      {
        if(current_screen <= record_screens)
        {
          if(current_screen != record_screens)
            current_screen++;
          
          rot_count = 0;
          clear_graph();
          draw_graph_screen(current_screen, ppg_bp_data, total_record_samples);

        }
      }

      else if (rot_count < 0)
      {
        if(current_screen >= 1)
        {
          if(current_screen != 1)
          {
            current_screen--;
            rot_count = MAX_POINTS;
          }
          
          clear_graph();
          draw_graph_screen(current_screen, ppg_bp_data, total_record_samples);
        }
        
      }
      
      // show the indicator, graph and bp value at the particular index
      int index = rot_count + (current_screen - 1) * MAX_POINTS;

      // To constrain the index in a range 0 to total max points
      if(index <= total_record_samples && index > 0)
      {
        draw_indicator_line(rot_count, 1);
        show_ppg_bp(rot_count, ppg_bp_data[0][index], ppg_bp_data[1][index]);
      }
      else if(index == total_record_samples + 1)
      {
        rot_count = rot_count - 1;
        draw_indicator_line(rot_count, 1);
      }
      else if(index <= 0)
      {
        rot_count = 0;
        draw_indicator_line(rot_count, 1);
      }
    }
    else
    {
      // adjust the counter in a range 1 to 3
      if (rot_count > 3)
        rot_count = 1;
      else if (rot_count < 1)
        rot_count = 3;
      
      menu();
    }
  }
  
  if(OK_Pressed)
  {
    OK_Pressed = false;
    if(rot_count == 1)
    {
      clear_graph();

      ppg_record = 0;
      sample = 0;
      record_sample = 0;
      history_flag = 0;
    }
    else if(rot_count == 2)
    {
      if(ppg_record)
      {
        store_extreme();

        ppg_record = 0;
        history_flag = 1;

        total_record_samples = record_sample;
        sample = 0;
        record_sample = 0;
        
        record_screens = ceil((double)total_record_samples/MAX_POINTS);

        // assign last screen to current screen
        current_screen = record_screens;

        clear_graph();
        draw_graph_screen(current_screen, ppg_bp_data, total_record_samples);
        show_ppg_bp(sample, ppg_bp_data[0][total_record_samples], ppg_bp_data[1][total_record_samples]);

      }
      else
        ppg_record = 1;
    }
    else if(rot_count == 3)
    {
      Serial.println("Report is generated..!");
    }
    menu();
  }

  if(!history_flag)
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
    draw_graph(tft, ppg_value, 1);
    
    // only show for each 5 samples to make is visible on screen
    if (sample % 5 == 1)
      show_ppg_bp(sample, ppg_value, bp_value);

    delay(10);    
  }

}

