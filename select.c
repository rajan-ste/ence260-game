#include <stdio.h>
#include <stdint.h>
#include "select.h"




/* moves the selector left, takes a hexadecimal as argument */
void move_select_left(uint8_t *bitmap) {
    if (*bitmap != LEFT_WALL) { // boundary check
        uint8_t map_shifted = *bitmap >> 1;
        ledmat_display_column(0x00, COL);
        ledmat_display_column(map_shifted, COL);
        *bitmap = map_shifted; // update the current LED
    } else {
    ledmat_display_column(*bitmap, COL);
    }
}

/* moves the selector left, takes a hexadecimal as argument */
void move_select_right(uint8_t *bitmap) {
    if (*bitmap != RIGHT_WALL) { // boundary check
        uint8_t map_shifted = *bitmap << 1;
        ledmat_display_column(0x00, COL);
        ledmat_display_column(map_shifted, COL);
        *bitmap = map_shifted;
    } else {
        ledmat_display_column(*bitmap, COL);
    }
    
}




