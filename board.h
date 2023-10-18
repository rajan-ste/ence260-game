/** @file board.h
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief display board
    last edited 
*/


#include <stdint.h>

#ifndef BOARD_H
#define BOARD_H


#define PAPER 'P'
#define SCISSORS 'S'
#define ROCK 'R'


int8_t check_winner(char player1, char player2); 
uint8_t get_player2_action(char* player2);







#endif
