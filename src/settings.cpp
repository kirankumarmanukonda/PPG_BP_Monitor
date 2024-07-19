#include <gui.h>
#include <tft.h>
#include <Preferences.h> // To read and write from flash

extern uint8_t wifi_connected_logo PROGMEM [];

Preferences preferences;

// The maximum bp upto system can go
int max_bp;

// To load the saved settings from flash
void load_settings()
{
    //Create a namespace called "settings"
    preferences.begin("settings", false);

    max_bp = preferences.getInt("bpMax", 250);
    
}

// To save settings to the flash
void save_settings()
{
    max_bp = rot_count;
    preferences.putInt("bpMax", max_bp);
    preferences.end();
}

// to change the max bp parameter in settings page
void change_max_bp()
{
    tft.setTextSize(2);
    tft.fillRoundRect(175, 65, 48, 24, 10, ILI9341_CYAN);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(180, 70);
    tft.print(rot_count);
    
}

// Settings Home screen
void setting_screen()
{
    tft.setTextColor(ILI9341_BLUE);
    tft.setTextSize(2);
    tft.setCursor(112, 20);
    tft.print("Settings");

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(60, 70);
    tft.print("Max BP  :  ");

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(60, 100);
    tft.print("Nothing :  ");

    tft.fillRoundRect(175, 65, 48, 24, 10, ILI9341_CYAN);
    tft.setTextColor(ILI9341_BLACK);
    tft.setCursor(180, 70);
    tft.print(max_bp);

    tft.setTextColor(ILI9341_CYAN);
    tft.setCursor(180, 100);
    tft.print("--");

    //save_settings();
}


// To show settings menu selection
void settings_menu()
{
    tft.setTextSize(2);
    if(rot_count == 0)
    {
        tft.fillRoundRect(175, 65, 48, 24, 10, ILI9341_CYAN);
        tft.setTextColor(ILI9341_BLACK);
        tft.setCursor(180, 70);
        tft.print(max_bp);

        tft.fillRoundRect(175, 95, 48, 24, 10, ILI9341_BLACK);
        tft.setTextColor(ILI9341_CYAN);
        tft.setCursor(180, 100);
        tft.print(123);
    }
    else
    {
        tft.fillRoundRect(175, 65, 48, 24, 10, ILI9341_BLACK);
        tft.setTextColor(ILI9341_CYAN);
        tft.setCursor(180, 70);
        tft.print(max_bp);

        tft.fillRoundRect(175, 95, 48, 24, 10, ILI9341_CYAN);
        tft.setTextColor(ILI9341_BLACK);
        tft.setCursor(180, 100);
        tft.print(123);
    }

}

// Report Home screen
void report_screen()
{
    tft.setTextColor(ILI9341_BLUE);
    tft.setTextSize(2);
    tft.setCursor(124, 20);
    tft.print("Report");

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(28, 60);
    tft.print("Please Connect Wifi !!");

    tft.setTextSize(2);
    tft.setCursor(28, 90);
    tft.print("SSID :");
    tft.setCursor(28, 116);
    tft.print("PSWD :");
    
    tft.setTextColor(ILI9341_CYAN);
    tft.setCursor(112, 90);
    tft.print("TOE BP-0001");
    tft.setCursor(112, 116);
    tft.print("1234567890");
    
    tft.drawBitmap(270, 100, wifi_connected_logo, 40, 40, ILI9341_BLACK, ILI9341_GREEN);
    tft.setTextSize(1);
    tft.setTextColor(ILI9341_GREEN);
    tft.setCursor(260, 150);
    tft.print("Connected");
    

    //ESP.deepSleep(1000000);
    //tft.println(max_val);

}