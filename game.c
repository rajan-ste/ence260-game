/** @file game.c
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief run the game
    last edited 19/10/2023
*/


#include "game_display.h"
#include "ir_uart.h"
#include "compare.h"
#include "navswitch.h"
#include "pacer.h"


#define START 0
#define SELECT 1
#define PROCESS 8
#define READ 9
#define END 6
#define PACER_RATE 1000
#define TINYGL_RATE 1000
#define DEFAULT 7
#define LOSER 'L'
#define WINNER 'W'
#define DRAW 'D'


typedef struct {
    uint8_t mode; // mode the game is in
    uint8_t p1_action; // the current microcontrollers action
    uint8_t p2_action; // the other microctrollers action
} state_t;


state_t state = {
    START, // game starts in start mode
    PAPER, // player 1 defaults to paper
    DEFAULT, // dont set player2 action to anything yet
};


/** Scrolls the start menu text until the player presses start
    @param state points to state object */
static void start_menu(state_t* state) 
{   
    // scroll the start menu display text
    tinygl_update();

    // checking for navswitch press
    navswitch_update();
   
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        // change mode to select
        state->mode = SELECT;
        // change tinygl to step
        step_text(""); 
        tinygl_clear();
    }
}


/** choose your action, first person to press
    the navswitch sends their symbol to the other
    controller.
    @param state a pointer to the game state */
static void move_selector(state_t* state)
{
    navswitch_update();
    tinygl_update();

    // static to display P before someting is pressed
    static uint8_t count = 0;

    // display P and set current action to PAPER
    if (navswitch_push_event_p((NAVSWITCH_NORTH)) || count == 0) {
        state->p1_action = PAPER;
        count++;
        display_character(PAPER);
    }

     // display S and set current action to SCISSORS
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        state->p1_action = SCISSORS;
        display_character(SCISSORS);
    }

    // display R and set current action to ROCK
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        state->p1_action = ROCK;
        display_character(ROCK);
    }

    // if other player hasn't sent symbol and button has been pushed
    if (navswitch_push_event_p(NAVSWITCH_PUSH) && !ir_uart_read_ready_p()) {
        if (state->p1_action == ROCK) { 
            // send current action
            ir_uart_putc(ROCK);
            state->mode = READ;
            tinygl_clear();
        }
        if (state->p1_action == PAPER) {
            ir_uart_putc(PAPER);
            state->mode = READ;
            tinygl_clear();
        }
        if (state->p1_action == SCISSORS) {
            ir_uart_putc(SCISSORS);
            state->mode = READ;
            tinygl_clear();
        }
    }

    // if other player has sent symbol and button has been pushed
     if (ir_uart_read_ready_p() && navswitch_push_event_p(NAVSWITCH_PUSH)) {
        char player2;
        // receive what action the other controller sent
        char player2_recv = ir_uart_getc();
        player2 = player2_recv;

        // error checks
        if (player2 == PAPER) {
            state->p2_action = PAPER;
            tinygl_clear();
            state->mode = PROCESS;

        } else if (player2 == SCISSORS) {
            state->p2_action = SCISSORS;
            tinygl_clear();
            state->mode = PROCESS;
           
        } else if (player2 == ROCK) {
            state->p2_action = ROCK;
            tinygl_clear();
            state->mode = PROCESS;
        }
    }
}


/** determine who won and send result to other 
    controller and display it
    @param state pointer to game state */
void process_mode(state_t* state)
{
    tinygl_update();

    if (check_winner(state->p1_action, state->p2_action) == 1) {
        ir_uart_putc(LOSER); // tell the other controller they lost
        scroll_text("WINNER");

    } else if (check_winner(state->p1_action, state->p2_action) == -1) {
        ir_uart_putc(WINNER); // tell the other microcontroller they won
        scroll_text("LOSER");

    } else if (check_winner(state->p1_action, state->p2_action) == 0) {
        ir_uart_putc(DRAW); // tell the other microcontroller they drew
        scroll_text("DRAW");
    } 

    state->mode = END;    
}


/** Receive the result of the game from
    the other controller and display it
    @param state pointer to game state */
void read_mode(state_t* state)
{
    tinygl_update();

    // read in the result to a char
    char result; 

    if (ir_uart_read_ready_p()) {
        char result_recv = ir_uart_getc();
        result = result_recv;

        if (result == LOSER) {
            scroll_text("LOSER");
        }

        if (result == WINNER) {
            scroll_text("WINNER");
        } 

        if (result == DRAW) {
            scroll_text("DRAW");
        }

        state->mode = END;
    }
}


int main (void)
{
    // initialise everything
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

            case END :
                tinygl_update();
                break;
        }
    }
}
