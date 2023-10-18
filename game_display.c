/** @file   game_display.c
    @author Rajan Stephens, Katie Ryan
    @date   19/10/2023
    @brief  Display module
*/


#include "game_display.h"


/* Sets text mode to Scroll 
    @param text, the text to display */
void scroll_text (char* text)
{
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (10);
    tinygl_text (text);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_update();
}


/* Sets text mode to Step 
    @param text, the text to display */
void step_text (char* text)
{
    tinygl_font_set (&font3x5_1);
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











