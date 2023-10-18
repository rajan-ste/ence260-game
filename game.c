#include "../../drivers/avr/system.h"
#include "select.h"
#include "game_display.h"
#include "ir_uart.h"
#include "../../drivers/display.h"
#include "board.h"


#define START 0
#define SELECT 1
#define PROCESS 8
#define READ 9
#define PACER_RATE 500
#define TINYGL_RATE 500
#define DEFAULT 7




typedef struct {
    uint8_t mode;
    uint8_t p1_action;
    uint8_t p2_action;
} state_t;

state_t state = {
    START,
    PAPER,
    DEFAULT,
};

static void start_menu(state_t* state) 
{   
    // scroll the start menu display text
    tinygl_update();
    // checking for navswitch press
    navswitch_update();
   

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        state->mode = SELECT; // change mode to select
        step_text(""); // change tinygl to step
        tinygl_clear();
    }

}





static void move_selector(state_t* state)
{
    navswitch_update();
    tinygl_update();
   
   

    // display P and set current action to PAPER
    if (navswitch_push_event_p((NAVSWITCH_NORTH))) {
        state->p1_action = PAPER;
        display_character('P');

    }

     // display S and set current action to SCISSORS
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        state->p1_action = SCISSORS;
        display_character('S');
    }


    // display R and set current action to ROCK
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        state->p1_action = ROCK;
        display_character('R');
    }


    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        if (state->p1_action == ROCK) { 
            ir_uart_putc('R');
            state->mode = READ;
            tinygl_clear();
        }
        if (state->p1_action == PAPER) {
            ir_uart_putc('P');
            state->mode = READ;
            tinygl_clear();
        }
        if (state->p1_action == SCISSORS) {
            ir_uart_putc('S');
            state->mode = READ;
            tinygl_clear();
        }

       
    }

     if (ir_uart_read_ready_p()) {
        char player2 = 'Z';
        char player2_recv = ir_uart_getc();
        player2 = player2_recv;

        if (player2 == 'P') {
            state->p2_action = PAPER;
            tinygl_clear();
            state->mode = PROCESS;
            

        } else if (player2 == 'S') {
            state->p2_action = SCISSORS;
            tinygl_clear();
            state->mode = PROCESS;
           

        } else if (player2 == 'R') {
            state->p2_action = ROCK;
            tinygl_clear();
            state->mode = PROCESS;

        }
        
    
    }

}

void process_mode(state_t* state)
{

    tinygl_update();
    static uint8_t count = 0;
    
    if (count == 0) {

        if (check_winner(state->p1_action, state->p2_action) == 1) {
            ir_uart_putc('L'); // tell the other controller they lost
            // scroll_text("WINNER");
            display_character('W');
            count++;
           

        } else if (check_winner(state->p1_action, state->p2_action) == -1) {
            ir_uart_putc('W'); // tell the other microcontroller they won
            // scroll_text("LOSER");
            display_character('L');
            count++;
            

        } else if (check_winner(state->p1_action, state->p2_action) == 0) {
            ir_uart_putc('D'); // tell the other microcontroller they drew
            // scroll_text("DRAW");
            display_character('D');
            count++;
        } 

        count++;
    }

}
    


void read_mode(state_t* state)
{

    tinygl_update();
    char result = 'R';

    if (ir_uart_read_ready_p()) {
        char result_recv = ir_uart_getc();
        result = result_recv;

        if (result == 'L') {
            // scroll_text("LOSER");
            display_character('L');
        }

        if (result == 'W') {
            // scroll_text("WINNER");
            display_character('W');
        } 

        if (result == 'D') {
            // scroll_text("DRAW");
            display_character('D');
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
            case PROCESS :
                process_mode(&state);
                break;  
            case READ :
                read_mode(&state);
                break; 
        }
    }
}
