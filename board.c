/** @file board.c
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief display board
    last edited 
*/

#include "board.h"



int8_t check_winner(char player1, char player2) 
{
    if (player1 == player2) {
        return 0;  // Draw
    }

    if (player1 == 'R') {
        return (player2 == 'S') ? 1 : -1;
    }

    if (player1 == 'P') {
        return (player2 == 'R') ? 1 : -1;
    }

    if (player1 == 'S') {
        return (player2 == 'P') ? 1 : -1;
    }

    return 0;  
}

uint8_t get_player2_action(char* player2)
{
    if (*player2 == 'P') {
        return PAPER;

    } else if (*player2 == 'S') {
        return SCISSORS;

    } else if (*player2 == 'R') {
        return ROCK;

    }
    return 0;
}

