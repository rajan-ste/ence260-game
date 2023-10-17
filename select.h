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
#include "game_display.h"


#ifndef SELECT_H
#define SELECT_H



#define LEFT_WALL 1
#define RIGHT_WALL 64
#define NUM_ROWS 7
#define COL 0
#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'

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

void select_move_right(uint8_t *curr_select);
void select_move_left(uint8_t *curr_select);

#endif
