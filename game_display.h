/** @file   game_display.h
    @author Rajan Stephens, Katie Ryan
    @date   11/10/23
    @brief  Display Text & Character
    last edited 19/10/23     
*/


#ifndef DISPLAY_H
#define DISPLAY_H


#include "system.h"
#include "pio.h"
#include "../../utils/tinygl.h"
#include "../fonts/font3x5_1.h"
#include "display.h"


/** Scroll text across the screen using tinygl
    @param text, the text to scroll */
void scroll_text (char* text);


/** Step text on the screen
    @param text, text to step */
void step_text (char* text);


/** Flash a single character onto the screen:
    @param character, the character to display */
void display_character (char character);


#endif
