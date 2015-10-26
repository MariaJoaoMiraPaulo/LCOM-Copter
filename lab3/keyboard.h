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

int keyboard_int_handler();

void keyboard_scan();

unsigned long keyboard_create_command(int ledToChange);

int keyboard_notify_controller();

int keyboard_change_led(unsigned long cmd);

void keyboard_print_ledInfo(int ledToPrint);

#endif /* _LCOM_KEYBOARD_H */
