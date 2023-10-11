/** @file select.h
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief select and shoot behaviour module
    last edited 
*/

#include "system.h"
#include "pio.h"
#include "navswitch.h"


#ifndef SELECT_H
#define SELECT_H

#include "system.h"

#define LEFT -1
#define RIGHT 1
#define LEFT_WALL 0
#define RIGHT_WALL 6


void select_led_init(void);
void check_select_edge(void);
void move_select_led(void);

#endif
