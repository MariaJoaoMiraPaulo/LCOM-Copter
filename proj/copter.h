#ifndef __COPTER__H
#define __COPTER__H

//#define NULL 0


typedef struct {

	int x, y, width, height, distance;
	//imagem

}Copter;

Copter* newCopter(int x, int y, int width, int height);

void draw_copter(Copter* copter);

void delete_copter(Copter* copter);

void update_copter(Copter* copter, int upOrDown);

#endif /* __COPTER_H */
