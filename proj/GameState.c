#include "GameState.h"
#include "video_gr.h"
#include "Obstacles.c"
#include "KBD.h"
#include "bitmap.h"

int hit(Copter* copter){
	int i;
	for (i = copter->x; i < copter->width + copter->x; i++) {
		if(color(i,copter->y-1)==MARGINS_COLOR)
			return 1;
		if(color(i,copter->y+ copter->height+1)==MARGINS_COLOR)
			return 1;
	}

	for (i = copter->y; i < copter->height + copter->y; i++) {
		if(color(copter->x-1,i)==MARGINS_COLOR)
			return 1;
		if(color(copter->x+copter->width +1,i)==MARGINS_COLOR)
			return 1;
	}


	return 0;
}


int updateGame(Copter* copter, Margin** margins, unsigned short *sizeOfArray, unsigned int time,Obstacle* obs){

	Bitmap* teste;
	teste=loadBitmap("/home/lcom/repos/proj/images/abcp.bmp");

	if(hit(copter)==HIT){
		return 1;
	}

	if(time>=5){
		drawObstacle(obs);
		obsPullToTheLeft(obs);
		if(obs->x+WIDTH<0)
			setObstacle(obs,margins[*sizeOfArray-1]);
	}

	draw_copter(copter);
	draw_margin(margins,sizeOfArray,time);
	incrementDistance(copter);
	draw_distance(copter->distance,teste);
	update_screen();
	pullToTheLeft(margins,sizeOfArray,time);


	return 0;
}
