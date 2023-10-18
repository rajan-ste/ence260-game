/** @file   l
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
#include "../fonts/font5x7_1.h"
#include "display.h"






void scroll_text (char* text);
void step_text (char* text);
void display_character (char character);




#endif