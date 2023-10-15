/** @file board.h
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief display board
    last edited 
*/

#include <stdbool.h>
#include <stdint.h>

#ifndef BOARD_H
#define BOARD_H

#define COLS 4
#define ROWS 7

uint8_t find_empty_row_in_column(uint8_t* col, uint8_t board[COLS][ROWS]); 
bool is_column_free(uint8_t* col, uint8_t board[COLS][ROWS]); 
void insert_board(uint8_t* col, uint8_t row, uint8_t board[COLS][ROWS]);
uint8_t row_to_bitmap(uint8_t row[ROWS]); 





#endif
