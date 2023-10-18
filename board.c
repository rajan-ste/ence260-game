/** @file board.c
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief display board
    last edited 19/10/23
*/


#include "board.h"



/* Checks to see who won 
    @param the current microcontrollers symbol
    @param the sending microcontrollers symbol */
int8_t check_winner(char player1, char player2) 
{
    // Check for draw
    if (player1 == player2) {
        return 0;
    }

    // Player 1 chooses ROCK
    if (player1 == 'R') {
        if (player2 == 'S') {
            return 1;  // Player 1 wins
        } else if (player2 == 'P') {
            return -1; // Player 2 wins
        }
    }

    // Player 1 chooses PAPER
    if (player1 == 'P') {
        if (player2 == 'R') {
            return 1;  // Player 1 wins
        } else if (player2 == 'S') {
            return -1; // Player 2 wins
        }
    }

    // Player 1 chooses SCISSORS
    if (player1 == 'S') {
        if (player2 == 'P') {
            return 1;  // Player 1 wins
        } else if (player2 == 'R') {
            return -1; // Player 2 wins
        }
    }

    // Default return (for unexpected inputs)
    return 3; 
}



/* 
    @param player2, */
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
