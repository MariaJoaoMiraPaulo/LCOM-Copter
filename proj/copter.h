#ifndef __COPTER_H
#define __COPTER_H

//#define NULL 0
#include "bitmap.h"

/** @defgroup copter Copter
 * @{
 *
 * Module that create and control everything that is related to copters
 *
 */

/** @name Copter structure */
/** @{
 *
 * Copter structure
 */
typedef struct {

	unsigned short x, y, width, height;
	int distance;
	Bitmap* image_copter;

}Copter;
/** @} end of Copter */

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
 *
 * @return a copter pointer
 */
Copter* newCopter(unsigned short x, unsigned short y, unsigned short width, unsigned short height);

/**
 * @brief draws copter's image
 *
 * @param copter pointer to copter
 * @param chooseImage to choose the "copter"
 */
void draw_copter(Copter* copter, char chooseImage);

/**
 * @brief delets copter's object
 *
 * @param copter pointer to copter
 */
void deleteCopter(Copter* copter);

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
/**
 * @brief reads a file and refreshes highscore
 *
 * @param copter pointer to copter
 */
void loadHighScore();

/**
 *@brief checks if player reaches high score
 */
void refreshHighScore(Copter* copter);
/**
 * @brief save best score
 */
void saveHighScore();

/**
 * @brief shows on screen new high score
 *
 * @param copter pointer to copter
 */
void highScore(Copter* copter);

/** @} end of copter */

#endif /* __COPTER_H */
