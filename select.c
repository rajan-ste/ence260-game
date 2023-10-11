#include <stdio.h>
#include <stdint.h>
#include "select.h"

// Global variable to keep track of the current row.
static uint8_t current_row = 7;  // As initially LEDMAT_ROW7_PIO is set to low


/* initialise selector LED */
void select_led_init(void) 
{
    // Set all columns and rows to high initially
    for (int i = 0; i < NUM_ROWS; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }

    // Set the initial state
    pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_LOW);
    pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_LOW);
}

void move_select_led(void) 
{
   navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        // Turn OFF (high) the current row LED
        pio_config_set(rows[current_row - 1], PIO_OUTPUT_HIGH); 

        // Decrement the current row (with boundary check)
        if (current_row > 1) {
            current_row--;
        }

        // Turn ON (low) the new current row LED
        pio_config_set(rows[current_row - 1], PIO_OUTPUT_LOW); 
    }
}
