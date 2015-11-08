#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

/** @defgroup test4 test4
 * @{
 *
 * Functions for testing the kbd code
 */

/**
 * @brief To subscribe mouse/keyboard controller
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_subscribe_int();

/**
 * @brief To unsubscribe mouse/keyboard controller
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_unsubscribe_int();

/**
 * @brief To deal with the interrupts from the mouse
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_handler();

/**
 * @brief To print the packet
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int mouse_print_packet();

#endif /* _LCOM_MOUSE_H */
