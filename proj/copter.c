#include "copter.h"
#include "video_gr.h"
#include "KBD.h"
#include <minix/drivers.h>

Copter* newCopter(unsigned short x, unsigned short y, unsigned short width, unsigned short height){
	Copter* c;
	c=(Copter *)malloc(sizeof(Copter));
	c->image_copter=loadBitmap("/home/lcom/repos/proj/images/copter.bmp");


	if(c==NULL)
		return NULL;

	c->x=x;
	c->y=y;
	c->width=width;
	c->height=height;
	c->distance=0;



	return c;
}

void draw_copter(Copter* copter){  //TROCAR PARA UMA IMAGEM
	unsigned int i,j;

	//	for(i=copter->x;i<copter->width+copter->x;i++){
	//		for(j=copter->y;j<copter->height+copter->y;j++){
	//			vg_print_pixel(i,j,rgb(255,102,102));
	//
	//		}
	//	}

	drawBitmap(copter->image_copter,copter->x, copter->y);
}

void update_copter(Copter* copter, int upOrDown){   //up=0, down != 0
	if(upOrDown == 0)
		copter->y=copter->y-5;
	else
		copter->y=copter->y+5;
}

void incrementDistance(Copter* copter){
	copter->distance++;
}

void delete_copter(Copter* copter){
	deleteBitmap(copter->image_copter);
	free(copter);
}

