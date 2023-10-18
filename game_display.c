/** @file   ledmat.c
    @author M. P. Hayes, UCECE
    @date   23 August 2010
    @brief  LED matrix driver.
*/

#include "game_display.h"


#define DISPLAY_WIDTH LEDMAT_COLS_NUM
#define DISPLAY_HEIGHT LEDMAT_ROWS_NUM


/** Define PIO pins driving LED matrix rows.  */
static const pio_t ledmat_rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t ledmat_cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};



void scroll_text (char* text)
{
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (10);
    tinygl_text (text);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_update();
}


void step_text (char* text)
{
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (10);
    tinygl_text (text);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_STEP);
    tinygl_update();
}


/** Flash a single character onto the screen:
    @param character, the character to display */
void display_character (char character)
{
    char buffer[2];
    tinygl_font_set (&font3x5_1);
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void display_curr_select(uint8_t* curr_select)
{
    if (*curr_select == PAPER) {
        display_character('P');
    } else if (*curr_select == SCISSORS) {
        display_character('S');
    } else {
        display_character('R');
    }
}










