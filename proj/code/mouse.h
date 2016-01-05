#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include <minix/drivers.h>
#include <minix/com.h>
#include "mouse.h"
#include "KBD.h"
#include "bitmap.h"

/** @defgroup mouse Mouse
 * @{
 *
 * Module that create and control everything that is related to mouse
 *
 */

/** @name MouseInfo structure */
/** @{
 *
 * MouseInfo structure
 */
typedef struct{
	short x,y;
	char lButton,rButton,mButton;
	Bitmap* mouseImage;
} MouseInfo;
/** @} end of MouseInfo */

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
/**
 *
 * @brief receive byte a byte of config of the mouse
 *
 * @return return 1 when config of the mouse is printed
 *
 */
int mouse_config_handler();
/**
 *
 * @brief Prints mouse configuration
 *
 */
void mouse_print_config();

/**
 *
 * @brief Execute while out buffer is full
 *
 */
void while_out_buf_full();

/**
 *
 * @brief Prints mouse configuration
 *
 * @return Return 1 when the delta_y is bigger than length and delta_x lower than tolerance
 */
int mouse_is_over(unsigned short tolerance,short length);
/**
 *@brief checks if mouse left button is pressed or not
 */
int mouse_left_button_press();

/**
 *@brief gives mouse atual position
 *
 *@param mouse pointer to MouseInfo
 */
void atualMousePosition(MouseInfo* mouse);

/**
 * @brief draws mouse on the screen
 *
 * @param mouse pointer to MouseInfo
 */
void drawMouse(MouseInfo* mouse);

/** @} end of mouse */

#endif /* _LCOM_MOUSE_H */
