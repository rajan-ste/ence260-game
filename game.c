#include "system.h"
#include "select.h"
#include "game_display.h"
#include "ir_uart.h"


#define START 0
#define SELECT 1
#define WAIT 2
#define PACER_RATE 500
#define TINYGL_RATE 500



typedef struct {
    uint8_t mode;
} state_t;

state_t state = {
    START
};

static void start_menu(state_t* state) 
{   
    // scroll the start menu display text
    tinygl_update();
    // checking for navswitch press
    navswitch_update();

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc('W'); 
        state->mode = SELECT;
    }

    if (ir_uart_read_ready_p()) {
        char newchar = ir_uart_getc();
        if (newchar == 'W') {
            display_character (newchar);
            state->mode = WAIT;
        }
    }
}


int main (void)
{
  
    system_init();
    pacer_init(PACER_RATE);
    tinygl_init (TINYGL_RATE);
    ir_uart_init();

    // start menu display text
    scroll_text("PRESS TO START \0");

    while (1)
    {
        pacer_wait();
        tinygl_update();
        switch(state.mode) {
            case START :
                start_menu(&state);
                
                break;
        }
    }
}
