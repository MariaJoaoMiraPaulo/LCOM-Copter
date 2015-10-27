#ifndef _LCOM_KEYBOARD_H_
#define _LCOM_KEYBOARD_H_

/**keyboard
 *
 *
 * Functions for use the kbd
 */

int keyboard_subscribe_int();

int keyboard_unsubscribe_int();

void keyboard_print(int scancode);

int keyboard_c_handler();

unsigned long keyboard_create_command(int ledToChange); //creates command to send to in_buffer of keyboard

int keyboard_notify_controller();  //sends the command 0xED before sends command to change leds

int keyboard_change_led(unsigned long cmd);  //sends command to output buffer

void keyboard_print_ledInfo(int ledToPrint);  //prints info about leds, if they are turn on or off

int keyboard_ass_handler();

//int start_at_zero();

#endif /* _LCOM_KEYBOARD_H */
