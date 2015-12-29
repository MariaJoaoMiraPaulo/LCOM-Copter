#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "copter.h"
#include "Margins.h"
#include "Obstacles.h"
#include "Singleplayer.h"

#define HIT 1


int hit(Copter* copter);

int updateGame(Singleplayer *sp,unsigned int time);
//int updateGame(Copter* copter, Margin** margins,unsigned short *sizeOfArray,unsigned int time,Obstacle* obs);





















#endif /* __GAMESTATE_H */
