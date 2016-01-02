#ifndef __COPTER_H
#define __COPTER_H

//#define NULL 0
#include "bitmap.h"


typedef struct {

	unsigned short x, y, width, height;
	int distance;
	Bitmap* image_copter;

}Copter;
/**
 *@brief Function that loads Copter's image
 */
void loadCopterImage();

/**
 *@brief Function that delets Copter's image
 */
void deleteCopterImage();

/**
 * @brief creates a new copter
 *
 * @param x coordinate x of copter
 * @param y coordinate y of copter
 * @param width copter 's width
 * @param height copter's height
 */
Copter* newCopter(unsigned short x, unsigned short y, unsigned short width, unsigned short height);

/**
 * @brief draws copter's image
 *
 * @param copter pointer to copter
 */
void draw_copter(Copter* copter);

/**
 * @brief delets copter's object
 *
 * @param copter pointer to copter
 */
void delete_copter(Copter* copter);

/**
 * @brief updates coordinates of copter
 *
 * @param copter pointer to copter
 * @param upOrDown, equals to 0 if is moving up, different than 0 if is moving down
 */

void update_copter(Copter* copter, int upOrDown);

/**
 * @brief increment Copter's distance
 *
 * @param copter pointer to copter
 */
void incrementDistance(Copter* copter);

#endif /* __COPTER_H */
