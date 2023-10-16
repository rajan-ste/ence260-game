/** @file   ledmat.h
    @author M. P. Hayes, UCECE
    @date   23 August 2010
    @brief  LED matrix driver.

    @defgroup ledmat LED matrix driver
       
    This module implements a simple hardware abstraction of a LED matrix.
*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include "system.h"
#include "pio.h"
#include "select.h"
#include "../../utils/tinygl.h"
#include "../fonts/font3x5_1.h"
#include "display.h"






void scroll_text (char* text);
void step_text (char* text);
void display_character (char character);
void display_curr_select(uint8_t* curr_select);
void display_update (void);
void ledmat_display_column (uint8_t row_pattern, uint8_t current_column);



#endif