#include "system.h"
#include "system.c"
#include "select.c"



void select_led_init(void) 
{
   pio_config_set(cols[1], PIO_OUTPUT_HIGH);

   for (size_t i=0; i<7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
   }

   pio_config_set(rows[1], PIO_OUTPUT_HIGH);
}


int main (void)
{
    system_init ();


    while (1)
    {
        select_led_init();


    }
}
