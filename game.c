#include "../../drivers/avr/system.h"
#include "select.h"
#include "game_display.h"
#include "ir_uart.h"
#include "../../drivers/display.h"


#define START 0
#define SELECT 1
#define PACER_RATE 500
#define TINYGL_RATE 500


static uint8_t curr_select = PAPER;

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
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                state->mode = SELECT;
            }
        }
    }
}





static void move_selector(state_t* state, uint8_t* curr_select)
{
    navswitch_update();
    tinygl_update ();
    
    
    

    // change to wait state after turn taken
    /* if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
        
    } */

    // move selecter right
    if(navswitch_push_event_p(NAVSWITCH_EAST)) {
        char test = 'P'
        display_character(test);
        select_move_right(curr_select);
       
    }

    // move selecter left
    if(navswitch_push_event_p(NAVSWITCH_WEST)) {
        display_character('R');
        select_move_left(curr_select);
       
    }
}


int main (void)
{
  
    system_init();
    pacer_init(PACER_RATE);
    tinygl_init (TINYGL_RATE);
    ir_uart_init();
    navswitch_init();
    


    // start menu display text
    scroll_text("PRESS TO START \0");

    while (1)
    {
        pacer_wait();
        switch(state.mode) {
            case START :
                start_menu(&state);
                break;
            case SELECT :
                tinygl_clear();
                move_selector(&state, &curr_select);
                break;
        }
    }
}
