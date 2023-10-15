/** @file communications.c
    @author Katie Ryan, Rajan Stephens
    @date 11/10/2023
    @brief IR communications
    last edited 
*/

#include "communications.h"

void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}

void send(void)
{
    if (ir_uart_read_ready_p ())
        {
            char newchar = ir_uart_getc();
            if ((newchar >= 'A') && (newchar<= 'Z')) {
                character = newchar;
            }
        }
}
