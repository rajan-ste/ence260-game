#include "system.h"
#include "pio.h"
#include "select.h"




int main (void)
{
    system_init ();


    while (1)
    {
        select_led_init();
        navswitch_update();



    }
}
