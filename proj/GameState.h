#ifndef __GAMESTATE_H
#define __GAMESTATE_H

#include "copter.h"
#include "Margins.h"
#include "Obstacles.h"

#define HIT 1

int updateGame(Copter* copter, Margin** margins,unsigned short *sizeOfArray,unsigned int time,Obstacle* obs);

int hit(Copter* copter);





















#endif /* __GAMESTATE_H */
