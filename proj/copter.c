#include "copter.h"
#include "video_gr.h"
#include <minix/drivers.h>

Copter* newCopter(int x, int y, int width, int height){
	Copter* c;
	c=(Copter *)malloc(sizeof(Copter));

	if(c==NULL)
		return NULL;

	c->x= x;
	c->y=y;
	c->width=width;
	c->height=height;

	return c;
}

void draw_copter(Copter* copter){  //TROCAR PARA UMA IMAGEM
	unsigned int i,j;

	printf("x:%d",copter->x);
	printf("y:%d",copter->x);

	for(i=copter->x;i<copter->width+copter->x;i++){
		for(j=copter->y;j<copter->height+copter->y;j++){
			vg_print_pixel(i,j,18);

		}
	}
}

void update_copter(Copter* copter, int upOrDown){   //up=0, down != 0
	if(upOrDown == 0)
		copter->y=copter->y-10;
	else
		copter->y=copter->y+10;
}
