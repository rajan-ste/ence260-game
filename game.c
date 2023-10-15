#include "system.h"
#include "select.h"
#include "game_display.h"
#include "ir_uart.h"


#define START 0
#define SELECT 1
#define WAIT 2
#define PACER_RATE 500
#define TINYGL_RATE 500

static uint8_t curr_select = 0x40;

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



// if you turn change to select state
static void wait_mode(state_t* state)
{
    if (ir_uart_read_ready_p()) {
        char newchar = ir_uart_getc();
        if (newchar == 'S') {
            state->mode = SELECT;
        }
    }
}

static void move_selector(state_t* state, uint8_t* curr_select)
{
    navswitch_update();

    // change to wait state after turn taken
    if(navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ledmat_display_column(0x00, COL);
        ir_uart_putc('S'); 
        state->mode = WAIT;
    }

    // move selecter right
    if(navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        move_select_right(curr_select);
    }

    // move selecter left
    if(navswitch_push_event_p(NAVSWITCH_NORTH)) {
        move_select_left(curr_select);
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
            case WAIT :
                wait_mode(&state);
                break;
        }
    }
}
