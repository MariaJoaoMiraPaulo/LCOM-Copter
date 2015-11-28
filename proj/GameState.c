#include "GameState.h"
#include "video_gr.h"

int hit(Copter* copter){
	int i;
	for (i = copter->x; i < copter->width + copter->x; i++) {
		if(color(i,copter->y-1)==18)
			return 1;;
		if(color(i,copter->y+copter->height+1)==18)
			return 1;
	}

	for (i = copter->y; i < copter->height + copter->y; i++) {
		if(color(copter->x-1,i))
			return 1;
		if(color(copter->x+copter->width+1,i))
			return 1;
	}

	return 0;
}

int updateGame(Copter* copter, Margin** margin, unsigned short *sizeOfArray){

	if(hit(copter)==HIT){
		return 1;
	}

	draw_copter(copter);
	draw_margin(margin);
	update_screen();
	//pullToTheLeft(margin,sizeOfArray);

	return 0;
}
