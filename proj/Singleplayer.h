#ifndef __SINGLEPLAYER_H
#define __SINGLEPLAYER_H

#include "Margins.h"
#include "copter.h"
#include "Obstacles.h"

typedef struct {
	Copter* copter;
	Margin **margins;
	unsigned short sizeOfArray;
	Obstacle* obs;
}Singleplayer;


//Copter* c=newCopter(200,400,80,44);
//	Margin* m1=newMargin(0,0,800,50);
//	Margin* m2=newMargin(0,550,800,50);
//	Margin **margins;
//	//	margins=(Margin **) malloc(2*sizeof(Margin *));
//	margins=(Margin **) malloc(20*sizeof(Margin *));
//	margins[0]=m1;
//	margins[1]=m2;
//	unsigned short sizeOfArray=2;
//	Obstacle* obs;

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
 */
int playingGame();










#endif /* __SINGLEPLAYER_H */
