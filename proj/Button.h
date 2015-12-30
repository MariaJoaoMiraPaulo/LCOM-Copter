#ifndef _LCOM_BUTTON_H_
#define _LCOM_BUTTON_H_

#include <minix/drivers.h>
#include <minix/com.h>

#include "mouse.h"

typedef	struct{
	unsigned short x,y;
	unsigned short height, weight;
} Button;

/**
 * @brief draws a button on the screen
 *
 * @param b button to be draw
 */
void drawButton(Button *b);

/*
 * @brief checks if the click of the mouse left button was on the button
 *
 * @param b button were we checks if he click on
 * @param mouse info of the mouse
 *
 * @return return 0 if wasnt click on the button 1 otherwise
 */
int hasClickedOnButton(Button *b, MouseInfo *mouse);




#endif /* _LCOM_BUTTON_H */
