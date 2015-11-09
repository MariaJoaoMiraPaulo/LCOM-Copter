#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <minix/drivers.h>
#include <minix/com.h>
#include "mouse.h"
#include "KBD.h"

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
 * @return Return 1 when the info is printed to decrement cnt
 */
int mouse_handler();

/**
 *
 * @brief To print the packet
 *
 */
void mouse_print_packet();

/**
 *
 * @brief To enable mouse and enable sending data packets
 *
 */
void configure_environment();

#endif /* _LCOM_MOUSE_H */
