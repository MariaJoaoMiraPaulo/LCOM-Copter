#ifndef __SINGLEPLAYER_H
#define __SINGLEPLAYER_H

#include "Margins.h"
#include "copter.h"
#include "Obstacles.h"


/** @defgroup singleplayer Singleplayer
 * @{
 *
 * Module that create and control everything that is related to singleplayer
 *
 */

/** @name Singleplayer structure */
/** @{
 *
 * Singleplayer structure
 */
typedef struct {
	Copter* copter;  ///< copter in the game
	//	Margin **margins;   ///< array that contains the margins of the game
	//	unsigned short sizeOfArray;   ///< size of the array that contains the margins
	Obstacle* obs;   ///< obs that is being shown on the screen
	int spacePress;
	int LeftButtonPress;
}Singleplayer;
/** @} end of Singleplayer */

/** @name Singleplayer states */
/** @{ */
typedef enum{
	NO_HIT, HIT , WAITING
}SingleplayerState;
/** @} end of Singleplayer states */

/*
 * @brief Functions that will act like a constructor, initializing members of singleplayer struct
 *
 * @param sp struct to be initialized
 */
Singleplayer* singleplayerInit();

/*
 * @brief Functions that deletes struct Singleplayer and all of is members
 *
 * @param sp struct to be deleted
 */
void singleplayerDestructor(Singleplayer* sp);

/*
 * @brief Functions that will run the singleplayer mode
 *
 * @param chooseCopter copter image to be used
 */
int playingGame(char chooseCopter);


/** @} end of Singleplayer */

#endif /* __SINGLEPLAYER_H */
