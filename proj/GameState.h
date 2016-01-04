#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "copter.h"
#include "Margins.h"
#include "Obstacles.h"
#include "Singleplayer.h"

#define HIT 1


/** @defgroup GameState GameState
 * @{
 *
 * Module that create and control everything that is related to updating the screen
 *
 */

/*
 * @brief loads alphabet image used on copter's distance
 */
void loadImagem();

/*
 * @brief deletes images used in game state
 */
void deleteGameStateImage();

/**
 * @brief checks if copter hits a margins or a obstacle
 *
 * @param copter pointer to copter
 */
int hit(Copter* copter);

/**
 * @brief updates all game, distance, coordinates of copter,atual time,margins,obstacles
 *
 * @param sp pointer to singleplayer
 * @param time to be used in obstacles
 * @param chooseImage to know the "copter" image to be used
 * @param state to know the stage on the game
 */
int updateGame(Singleplayer *sp,unsigned int time, char chooseImage,int state);

/*
 *@brief draws everything on the screen when the copter hits something
 *
 *@param sp struct singleplayer that have the info of the game
 *@param time time of the game
 */
int hitDraws(Singleplayer *sp,char chooseCopter, int time);



/** @} end of GameState */

#endif /* __GAMESTATE_H */
