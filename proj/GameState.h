#ifndef __GAMESTATE__H
#define __GAMESTATE__H

#include "copter.h"
#include "Margins.h"

#define HIT 1

int updateGame(Copter* copter, Margin** margin,unsigned short *sizeOfArray,unsigned int time);

int hit(Copter* copter);





















#endif /* __GAMESTATE_H */
