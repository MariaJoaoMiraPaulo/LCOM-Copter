#include "GameState.h"
#include "video_gr.h"
#include "Obstacles.c"
#include "KBD.h"
#include "bitmap.h"

Bitmap* teste;
Bitmap* hitImage;

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

void loadGameStateImage(){

	teste=loadBitmap("/home/lcom/repos/proj/images/abcp.bmp");
	hitImage=loadBitmap("/home/lcom/repos/proj/images/hit.bmp");
}

void deleteGameStateImage(){

	deleteBitmap(teste);
	deleteBitmap(hitImage);
}

//int updateGame(Copter* copter, Margin** margins, unsigned short *sizeOfArray, unsigned int time,Obstacle* obs){
int updateGame(Singleplayer *sp,unsigned int time,char chooseImage,int state){

	switch(state){
	case 0:
		drawMargin(1);
		draw_copter(sp->copter, chooseImage);
	//	draw_distance(sp->copter->distance,teste);
	//	refreshHighScore(sp->copter);
		rtc_test_date();
		update_screen();
		break;
	case 1:

		if(hit(sp->copter)==HIT){
			return 1;
		}

		if(time>=3){
			drawObstacle(sp->obs);
			obsPullToTheLeft(sp->obs);
			if(sp->obs->x+WIDTH<0)
				setObstacle(sp->obs);
		}

		drawMargin(0);
		draw_copter(sp->copter, chooseImage);
		incrementDistance(sp->copter);
		draw_distance(sp->copter->distance,teste);


		if(time%2==0)
			highScore(sp->copter);

		refreshHighScore(sp->copter);
		rtc_test_date();
		update_screen();
		break;
	}
	return 0;
}

int hitDraws(Singleplayer *sp,char chooseCopter, int time){
	drawMargin(1);
	if(time>=3)
		drawObstacle(sp->obs);
	draw_copter(sp->copter, chooseCopter);
	draw_distance(sp->copter->distance,teste);
	refreshHighScore(sp->copter);
	rtc_test_date();
	drawBitmapWithoutBackground(hitImage,sp->copter->x-150,sp->copter->y-90);
	update_screen();
}
