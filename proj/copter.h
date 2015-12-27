#ifndef __COPTER__H
#define __COPTER__H

//#define NULL 0
#include "bitmap.h"


typedef struct {

	unsigned short x, y, width, height;
	int distance;
	Bitmap* image_copter;

}Copter;

Copter* newCopter(unsigned short x, unsigned short y, unsigned short width, unsigned short height);

void draw_copter(Copter* copter);

void delete_copter(Copter* copter);

void update_copter(Copter* copter, int upOrDown);

#endif /* __COPTER_H */
