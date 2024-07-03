#ifndef GUI_H
#define GUI_H

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

// BP & PPG Reading box
#define BP_BOX_X 70
#define BP_BOX_Y 5
#define PPG_BOX_X  BP_BOX_X + 100
#define PPG_BOX_Y BP_BOX_Y

extern int selected;
extern int ppg_record;

// Function declations
void initialize_BP_PPG_display();
void menu();
void loading_screen();
void show_ppg_bp(int sample, int ppg_value, int bp);

#endif