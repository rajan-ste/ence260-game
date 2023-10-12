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
#include "../../utils/tinygl.h"
#include "../fonts/font3x5_1.h"

/** Initialise PIO pins to drive LED matrix.  */
void ledmat_init (void);


/** Display pattern on specified column.
    @param pattern bit pattern to display for selected column
    @param col selected column.  */
void ledmat_display_column (uint8_t pattern, uint8_t col);

void scroll_text (char* text);
void display_character (char character);



#endif