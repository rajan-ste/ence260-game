/** @file select.h
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief select and shoot behaviour module
    last edited 
*/

#include "system.h"
#include "pio.h"
#include "navswitch.h"
#include "pacer.h"
#include "display.h"


#ifndef SELECT_H
#define SELECT_H

#include "system.h"

#define LEFT -1
#define RIGHT 1
#define LEFT_WALL 1
#define RIGHT_WALL 7
#define NUM_ROWS 7

#define PACER_RATE 100


// Array of rows for easy manipulation
static const pio_t rows[NUM_ROWS] = {
    LEDMAT_ROW1_PIO,
    LEDMAT_ROW2_PIO,
    LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO,
    LEDMAT_ROW5_PIO,
    LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


void select_led_init(void);
// void check_select_edge(void);
void move_select_led(void);
void turn_select_off(void); 

#endif
