/** @file compare.h
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief compares actions and select winner
    last edited 19/10/2023
*/


#include <stdint.h>


#ifndef COMPARE_H
#define COMPARE_H


#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'


/** Checks to see who won
    @param player1, the current microcontrollers symbol
    @param player2, the sending microcontrollers symbol */
int8_t check_winner(char player1, char player2); 


#endif
