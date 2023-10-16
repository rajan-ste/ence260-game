#include <stdio.h>
#include <stdint.h>
#include "select.h"


void select_move_right(uint8_t* curr_select)
{
    if (*curr_select == PAPER) {
        *curr_select = SCISSORS;
    } else if (*curr_select == SCISSORS) {
        *curr_select = ROCK;
    } else {
        *curr_select = PAPER;
    }
}

void select_move_left(uint8_t* curr_select)
{
    if (*curr_select == PAPER) {
        *curr_select = ROCK;
    } else if (*curr_select == SCISSORS) {
        *curr_select = PAPER;
    } else {
        *curr_select = SCISSORS;
    }
}
    





