#include "Margins.h"
#include <minix/drivers.h>


Margin* newMargin(int x, int y, int width, int height){
	Margin* m;
	m=(Margin *)malloc(sizeof(Margin));

	if(m==NULL)
		return NULL;

	m->x= x;
	m->y=y;
	m->width=width;
	m->height=height;

	return m;
}

void draw_margin(Margin** margin){
	unsigned int idx,i,j;
	for(idx=0;idx<2;idx++){
		for(i=margin[idx]->x;i<margin[idx]->x+margin[idx]->width;i++){
			for(j=margin[idx]->y;j<margin[idx]->y+margin[idx]->height;j++){
				vg_print_pixel(i,j,18);
			}
		}
	}
}
