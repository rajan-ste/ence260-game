#include "../../drivers/avr/system.h"
#include "select.h"
#include "game_display.h"
#include "ir_uart.h"
#include "../../drivers/display.h"


#define START 0
#define SELECT 1
#define FINAL 2
#define PACER_RATE 500
#define TINYGL_RATE 500


static uint8_t curr_select = PAPER;

typedef struct {
    uint8_t mode;
    uint8_t action;
} state_t;

state_t state = {
    START,
    PAPER
};

static void start_menu(state_t* state) 
{   
    // scroll the start menu display text
    tinygl_update();
    // checking for navswitch press
    navswitch_update();
   

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc('R'); 
        state->mode = SELECT; // change mode to select
        step_text(""); // change tinygl to step
        tinygl_clear();
    }

    if (ir_uart_read_ready_p()) {
        char newchar = ir_uart_getc();
        if (newchar == 'R') {
            display_character (newchar);
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                state->mode = SELECT;
                step_text("");
                tinygl_clear();
            }
        }
    }
}





static void move_selector(state_t* state, uint8_t* curr_select)
{
    navswitch_update();
    tinygl_update();
   

    static uint8_t count = 0;
    static char curr_state = 'P';

    // display P and set current action to PAPER
    if (navswitch_push_event_p(NAVSWITCH_NORTH) || count == 0) {
        curr_state = 'P';
        state->action = PAPER;
        display_character(curr_state);
        count++;
    }

     // display S and set current action to SCISSORS
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        curr_state = 'S';
        state->action = SCISSORS;
        display_character(curr_state);
    }


    // display R and set current action to ROCK
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        curr_state = 'R';
        state->action = ROCK;
        display_character(curr_state);
    }


    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc(curr_state);
        state->mode = FINAL;
    }
}

void result_mode(state_t* state)
{
     if (ir_uart_read_ready_p ())
        {
            char newchar = ir_uart_getc();
            if (newchar == 'P' || newchar == 'S' || newchar == 'R') {
	            check who won() ;
            }
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
                move_selector(&state, &curr_select);
                break;
            case FINAL :
                display_character('W');
                break;    
        }
    }
}
