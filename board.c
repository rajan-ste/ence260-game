/** @file board.c
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief display board
    last edited 
*/

#include "board.h"




uint8_t find_empty_row_in_column(uint8_t* col, uint8_t board[COLS][ROWS]) 
{
    for (int row = ROWS - 1; row >= 0; row--) {  // Start from the bottom of the column
        if (board[*col][row] == 0) {
            return row;  // This row is empty and can accept a piece
        }
    }
    return -1;  // No empty spot found in the column
}

bool is_column_free(uint8_t* col, uint8_t board[COLS][ROWS]) 
{
    return find_empty_row_in_column(*col, board) != -1;
}

void insert_board(uint8_t* col, uint8_t row, uint8_t board[COLS][ROWS])
{
    board[*col][row] = 1;
}


uint8_t row_to_bitmap(uint8_t row[ROWS]) 
{
    uint8_t bitmap = 0;

    for (int i = 0; i < ROWS; i++) {
        if (row[i] == 1 || row[i] == 2) {  // Check for both 1 and 2
            bitmap |= (1 << i);
        }
    }

    return bitmap;
}

