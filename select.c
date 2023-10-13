#include <stdio.h>
#include <stdint.h>
#include "select.h"

// Global variable to keep track of the current row.
uint8_t current_row = 7;  // As initially LEDMAT_ROW7_PIO is set to low

/* initialise selector LED */
void select_led_init(void) 
{
    // Set the initial state
    pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_LOW);
    pio_config_set(LEDMAT_ROW7_PIO, PIO_OUTPUT_LOW);
}

void move_select_led(void) 
{
    // initialise pacer
    pacer_init (500);
    


    // check for button press, end selecting mode when button pressed
    while (!navswitch_push_event_p(NAVSWITCH_PUSH)) {

        pacer_wait();
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
            // Turn OFF (high) the current row LED
            pio_config_set(rows[current_row - 1], PIO_OUTPUT_HIGH); 

            // Decrement the current row (with boundary check)
            if (current_row > LEFT_WALL) {
                current_row--;
            }

            pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_LOW);
            pacer_wait();
            // Turn ON (low) the new current row LED
            pio_config_set(rows[current_row - 1], PIO_OUTPUT_LOW); 
        }

        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            // Turn OFF (high) the current row LED
            pio_config_set(rows[current_row-1], PIO_OUTPUT_HIGH); 
        
            // Decrement the current row (with boundary check)
            if (current_row < RIGHT_WALL) {
                current_row++;
            }

            pio_config_set(LEDMAT_COL1_PIO, PIO_OUTPUT_LOW);
            pacer_wait();
            // Turn ON (low) the new current row LED
            pio_config_set(rows[current_row-1], PIO_OUTPUT_LOW); 

        
        }
    }
    ledmat_display_column(0x00, 0);
}


