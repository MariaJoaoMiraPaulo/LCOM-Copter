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


#endif /* _LCOM_KEYBOARD_H */
