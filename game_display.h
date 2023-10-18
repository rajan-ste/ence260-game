/** @file   game_display.h
    @author Rajan Stephens, Katie Ryan
    @date   11/10/23
    @brief  LED matrix driver.
    last edited 19/10/23     
*/

#ifndef DISPLAY_H
#define DISPLAY_H


#include "system.h"
#include "pio.h"
#include "../../utils/tinygl.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "display.h"


void scroll_text (char* text);
void step_text (char* text);
void display_character (char character);


#endif
