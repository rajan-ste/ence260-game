/** @file board.h
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief compares actions and select winner
    last edited 19/10/2023
*/


#include <stdint.h>


#ifndef BOARD_H
#define BOARD_H


#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'


/** Checks to see who won
    @param player1, the current microcontrollers symbol
    @param player2, the sending microcontrollers symbol */
int8_t check_winner(char player1, char player2); 


/** Recieves action from microcontroller
    @param player2, recieves action from other micontroller */
uint8_t get_player2_action(char* player2);


#endif
