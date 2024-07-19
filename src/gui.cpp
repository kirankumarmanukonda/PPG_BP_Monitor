#include <gui.h>
#include <tft.h>
#include <bitmaps.h>

// 1  -> storing ppg and bp
// 0  -> Not storing
int ppg_record;

void initialize_BP_PPG_display()
{
  // Draw the BP value and a Box
  tft.setCursor(BP_BOX_X, BP_BOX_Y);  // Set position (x,y)
  tft.setTextColor(ILI9341_YELLOW);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("     BP ");
  //tft.drawRoundRect(BP_BOX_X, BP_BOX_Y + 20, 45, 45, 8, 0x07FF);

  tft.setCursor(BP_BOX_X + 5, BP_BOX_Y + 15);
  tft.setTextSize(3); 
  tft.println("---");

  // Draw the Max BP value
  tft.setCursor(PPG_BOX_X, PPG_BOX_Y);  // Set position (x,y)
  tft.setTextColor(ILI9341_CYAN);
  tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("Max BP Limit");

  tft.setCursor(PPG_BOX_X + 5, PPG_BOX_Y + 15);
  tft.setTextSize(3); 
  tft.println(max_bp);

/*
  // Draw the PPG value and a Box
  tft.setCursor(PPG_BOX_X, PPG_BOX_Y);  // Set position (x,y)
  tft.setTextColor(ILI9341_DARKGREEN);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(1);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("   PPG");

  tft.setCursor(PPG_BOX_X + 5, PPG_BOX_Y + 15);
  tft.setTextSize(3); 
  tft.println("---");
*/
}

void menu()
{
  //tft.drawLine(0, SCREEN_HEIGHT - 39 , SCREEN_WIDTH, SCREEN_HEIGHT - 39, ILI9341_WHITE);
  
  //tft.drawRoundRect(0, SCREEN_HEIGHT - 40, 50, 40, 5, ILI9341_BLUE);
  int gap = 10;
  int menu_x = 45;
  int menu_width = 50;
  int menu_height = 40;

  int x, y;
  for(int i = 0; i < 4; i++)
  {
    x = i*menu_width + i*gap + menu_x;
    y = SCREEN_HEIGHT - menu_height;

    if(rot_count == i)
        tft.fillRoundRect(x, y, menu_width, menu_height, 10, ILI9341_CYAN);
    else
        tft.fillRoundRect(x, y, menu_width, menu_height, 10, ILI9341_DARKGREY);
    
    if(i == 0)
    {
        if(rot_count == i)
            tft.drawBitmap(x + 8, y + 3, home, 35, 35, ILI9341_CYAN, ILI9341_BLUE);
        else 
            tft.drawBitmap(x + 8, y + 3, home, 35, 35, ILI9341_DARKGREY, ILI9341_BLUE);
    }
    else if(i == 1)
    {
        if(!ppg_record)
        {
            tft.fillCircle(x + 25, y + 20, 17, ILI9341_RED);
            //tft.fillCircle(x + 25, y + 20, 17, ILI9341_RED);
            tft.setTextColor(ILI9341_BLUE);
            tft.setTextSize(1);
            tft.setCursor(x + 17 , y + 17);
            tft.print("REC");
        }
        else
        {
            if(rot_count == i)
                tft.drawBitmap(x + 8, y + 3, stop_logo, 35, 35, ILI9341_CYAN, ILI9341_RED);
            else 
                tft.drawBitmap(x + 8, y + 3, stop_logo, 35, 35, ILI9341_DARKGREY, ILI9341_RED);
        }
    }
    else if(i == 2)
    {
        if(rot_count == i)
            tft.drawBitmap(x + 8, y + 3, report_logo, 35, 35, ILI9341_CYAN, ILI9341_MAROON);
        else 
            tft.drawBitmap(x + 8, y + 3, report_logo, 35, 35, ILI9341_DARKGREY, ILI9341_MAROON);
    }
    else if(i == 3)
    {
        if(rot_count == i)
            tft.drawBitmap(x + 8, y + 3, settings_logo, 35, 35, ILI9341_CYAN, ILI9341_BLUE);
        else 
            tft.drawBitmap(x + 8, y + 3, settings_logo, 35, 35, ILI9341_DARKGREY, ILI9341_BLUE);

    }
    
  }
  
  // for BP and PPG readings
  tft.setTextSize(3);

}

void loading_screen()
{
    int x = 85; int y = 30;
    tft.drawBitmap(x, y, ayati_devices_logo, 150, 150, ILI9341_BLACK, 0x21ae);

    tft.setTextColor(ILI9341_BLUE);
    tft.setTextSize(1);

    for(int i = 0; i <= 5; i++)
    {
        tft.fillRect(x, y + 150, 30*i, 8, 0x21ae);
        
        tft.setCursor(x + 70 , y + 150 + 20);
        tft.print(i*20);
        tft.println("%");
        delay(200);

        if(i != 5)
            tft.fillRect(x + 70, y + 150 + 20, 30, 10, ILI9341_BLACK);
    }

    delay(1000);
    
    tft.fillScreen(ILI9341_BLACK);
}

void show_ppg_bp(int sample, int ppg_value, int bp)
{
    /*
    tft.setTextColor(ILI9341_DARKGREEN);
    tft.fillRoundRect(PPG_BOX_X, PPG_BOX_Y + 10, 80, 30, 0, ILI9341_BLACK);
    tft.setCursor(PPG_BOX_X + 5, PPG_BOX_Y + 15);
    tft.println(ppg_value);
    */

    tft.setTextColor(ILI9341_YELLOW);
    tft.fillRoundRect(BP_BOX_X, BP_BOX_Y + 10, 80, 30, 0, ILI9341_BLACK);
    tft.setCursor(BP_BOX_X + 10, BP_BOX_Y + 15);
    tft.println(bp);
}

