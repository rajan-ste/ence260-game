#include "../../drivers/avr/system.h"
#include "select.h"
#include "game_display.h"
#include "ir_uart.h"
#include "../../drivers/display.h"
#include "board.h"


#define START 0
#define SELECT 1
#define FINAL 2
#define IDLE 3
#define WAITING 4
#define PACER_RATE 500
#define TINYGL_RATE 500
#define DEFAULT 7




typedef struct {
    uint8_t mode;
    uint8_t p1_action;
    uint8_t p2_action;
    uint8_t comms;
} state_t;

state_t state = {
    START,
    PAPER,
    DEFAULT,
    IDLE
};

static void start_menu(state_t* state) 
{   
    // scroll the start menu display text
    tinygl_update();
    // checking for navswitch press
    navswitch_update();
   

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        ir_uart_putc(100); 
        state->mode = SELECT; // change mode to select
        step_text(""); // change tinygl to step
        tinygl_clear();
    }

    if (ir_uart_read_ready_p()) {
        char newchar = ir_uart_getc();
        if (newchar == 100) {
            if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
                state->mode = SELECT;
                step_text("");
                tinygl_clear();
            }
        }
    }
}





static void move_selector(state_t* state)
{
    navswitch_update();
    tinygl_update();
   


    // display P and set current action to PAPER
    if (navswitch_push_event_p((NAVSWITCH_NORTH)) && state->comms == IDLE) {
        state->p1_action = PAPER;
        display_character(state->p1_action);
        
    }

     // display S and set current action to SCISSORS
    if (navswitch_push_event_p(NAVSWITCH_EAST) && state->comms == IDLE) {
        state->p1_action = SCISSORS;
        display_character(state->p1_action);
    }


    // display R and set current action to ROCK
    if (navswitch_push_event_p(NAVSWITCH_SOUTH) && state->comms == IDLE) {
        state->p1_action = ROCK;
        display_character(state->p1_action);
    }


    if (navswitch_push_event_p(NAVSWITCH_PUSH) && state->comms == IDLE) {
        if (state->p1_action == ROCK) { 
            ir_uart_putc('R');
        }
        if (state->p1_action == PAPER) {
            ir_uart_putc('P');
        }
        if (state->p1_action == SCISSORS) {
            ir_uart_putc('S');
        }

        state->mode = FINAL;
        tinygl_clear();
        
    }


    
}

void result_mode(state_t* state)
{

    tinygl_update();
    char player2 = 'Z';
    

    if (ir_uart_read_ready_p()) {

        char player2_recv = ir_uart_getc();
        player2 = player2_recv;

        if (player2 == 'P') {
            state->p2_action = PAPER;
            

        } else if (player2 == 'S') {
            state->p2_action = SCISSORS;
           

        } else if (player2 == 'R') {
            state->p2_action = ROCK;

        }

       // display_character(state->p2_action);

        if (check_winner(state->p1_action, state->p2_action) == 1) {
            scroll_text("WINNER");
            // display_character('W');
            

        } else if (check_winner(state->p1_action, state->p2_action) == -1) {
            scroll_text("LOSER");
            // display_character('L');
            

        } else if (check_winner(state->p1_action, state->p2_action) == 0) {
            scroll_text("DRAW");
            // display_character('D');

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
                move_selector(&state);
                break;
            case FINAL :
                result_mode(&state);
                break;   
        }
    }
}
