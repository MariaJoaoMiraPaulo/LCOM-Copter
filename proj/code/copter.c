#include "copter.h"
#include "video_gr.h"
#include "KBD.h"
#include <minix/drivers.h>
#include <stdio.h>
#include "main.h"

const float GRAVITY = 1;
float VELOCITY = 0;

extern int bestScore;

Bitmap* copterImage;
Bitmap* medal;
Bitmap* teste;
Bitmap* newHigh;

void loadCopterImage(){
	copterImage=loadBitmap("/home/lcom/repos/proj/images/teste.bmp");
	medal=loadBitmap("/home/lcom/repos/proj/images/medal.bmp");
	teste=loadBitmap("/home/lcom/repos/proj/images/abcp.bmp");
	newHigh=loadBitmap("/home/lcom/repos/proj/images/!.bmp");
}

void deleteCopterImage(){
	deleteBitmap(copterImage);
	deleteBitmap(medal);
	deleteBitmap(teste);
	deleteBitmap(newHigh);
}

Copter* newCopter(unsigned short x, unsigned short y, unsigned short width, unsigned short height){

	Copter* c;
	c=(Copter *)malloc(sizeof(Copter));
	c->image_copter=copterImage;

	if(c==NULL)
		return NULL;

	c->x=x;
	c->y=y;
	c->width=width;
	c->height=height;
	c->distance=0;




	return c;
}

void draw_copter(Copter* copter, char c){  //TROCAR PARA UMA IMAGEM
	unsigned int i,j;

	//		for(i=copter->x;i<copter->width+copter->x;i++){
	//			for(j=copter->y;j<copter->height+copter->y;j++){
	//				vg_print_pixel(i,j,rgb(255,102,102));
	//
	//			}
	//		}

	//drawBitmap(copter->image_copter,copter->x, copter->y);
	drawCopters(copter->image_copter,copter->x, copter->y, c);
}

void update_copter(Copter* copter, int upOrDown){   //up=0, down != 0
	if(upOrDown == 0)
		copter->y=copter->y-5;
	else
		copter->y=copter->y+5;
	//	{
	//		VELOCITY += GRAVITY;
	//		copter->y=copter->y- VELOCITY;
	//	}
	//	else{
	//		VELOCITY += GRAVITY;
	//		copter->y=copter->y+VELOCITY;
	//	}
}

void incrementDistance(Copter* copter){
	copter->distance++;
}

void deleteCopter(Copter* copter){
	free(copter);
}

void loadHighScore(){

	int score;
	FILE *fp;
	fp=fopen("/home/lcom/repos/proj/highScore.txt", "r+");


	if(fscanf(fp,"%d",&score)==-1)
	{
		printf("ENTREIIIIIIIII OLA!!!!");
		fprintf(fp,"%d",0);
		bestScore=0;
	}
	else bestScore=score;

	fclose (fp);

}

void refreshHighScore(Copter* copter){


	if (copter->distance > bestScore)
	{
		bestScore=copter->distance;
	}


	printf("HIGH SCORE ATUAL:::::: %d",bestScore);

	drawBitmapWithoutBackground(medal,0,521);
	drawBest(bestScore, teste);

}

void highScore(Copter* copter){

	if (copter->distance > bestScore)
	{
		drawNumbers(teste,478,3,'N');
		drawNumbers(teste,495,3,'E');
		drawNumbers(teste,510,3,'W');
		drawNumbers(teste,540,3,'H');
		drawNumbers(teste,555,3,'I');
		drawNumbers(teste,570,3,'G');
		drawNumbers(teste,585,3,'H');
		drawNumbers(teste,600,3,'S');
		drawNumbers(teste,615,3,'C');
		drawNumbers(teste,630,3,'O');
		drawNumbers(teste,645,3,'R');
		drawNumbers(teste,660,3,'E');
		drawBitmapWithoutBackground(newHigh,675,35);
	}

}

void saveHighScore(){
	printf("BESTTTTTTT:::%d",bestScore);
	FILE *fp;
	fp=fopen("/home/lcom/repos/proj/highScore.txt", "w");



	fprintf(fp,"%d",bestScore);

	fclose(fp);

}

