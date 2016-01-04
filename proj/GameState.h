#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "copter.h"
#include "Margins.h"
#include "Obstacles.h"
#include "Singleplayer.h"

#define HIT 1

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
 * @param time
 */
int updateGame(Singleplayer *sp,unsigned int time, char chooseImage,int state);
//int updateGame(Copter* copter, Margin** margins,unsigned short *sizeOfArray,unsigned int time,Obstacle* obs);

/*
 *@brief draws everything on the screen when the copter hits something
 */
int hitDraws(Singleplayer *sp,char chooseCopter, int time);


















#endif /* __GAMESTATE_H */
