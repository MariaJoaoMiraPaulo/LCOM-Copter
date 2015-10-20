#ifndef __KEYBOARD_H
#define __KEYBOARD_H

/** @defgroup keyboard
 * @{
 *
 * Functions for use the kbd
 */

/**
 *
 */
char keyboard_subscribe_char(void );

void keyboard_print(int scancode);

int keyboard_int_handler();

void keyboard_scan();



#endif /* __KEYBOARD_H */
