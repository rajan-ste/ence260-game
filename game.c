#include "system.h"
#include "select.h"
#include "game_display.h"

#define START 0

typedef struct {
    uint8_t mode;
} state_t;

    state_t state = {
        START
    };

static void start_menu(state_t state) 
{   
    if (state.mode == START) {
        scroll_text("PRESS TO START \0");
        state.mode = 2;
    }

    
}


int main (void)
{
  
    system_init();
    pacer_init(500);
    tinygl_init (500);




    while (1)
    {
        pacer_wait();
        tinygl_update();
        switch(state.mode) {
            case START :
                start_menu(state);
                
                break;
        }
    }
}
