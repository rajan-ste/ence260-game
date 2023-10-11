#include "system.h"
#include "select.h"
#include "display.h"


void start_state(void) 
{
    led_init();
}

int main (void)
{
    system_init ();


    while (1)
    {
        select_led_init(); // init selector LEDs
        move_select_led(); 

    }
}
