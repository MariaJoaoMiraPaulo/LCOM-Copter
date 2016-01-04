#ifndef __SINGLEPLAYER_H
#define __SINGLEPLAYER_H

#include "Margins.h"
#include "copter.h"
#include "Obstacles.h"

typedef struct {
	Copter* copter;  ///< copter in the game
	//	Margin **margins;   ///< array that contains the margins of the game
	//	unsigned short sizeOfArray;   ///< size of the array that contains the margins
	Obstacle* obs;   ///< obs that is being shown on the screen
	int spacePress;
	int LeftButtonPress;
}Singleplayer;

typedef enum{
	NO_HIT, HIT , WAITING
}SingleplayerState;

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










#endif /* __SINGLEPLAYER_H */
