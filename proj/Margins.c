#include <minix/drivers.h>
#include "Margins.h"
#include "video_gr.h"

Margin* newMargin(unsigned short x, unsigned short y, unsigned short width, unsigned short height){
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

Margin* randomMargin(unsigned short x, unsigned short y){
	Margin* m;
	m=(Margin *)malloc(sizeof(Margin));

	if(m==NULL)
		return NULL;

	m->x=x;
	m->y=y;
	m->width=rand()%51+50;
	m->height=rand()%49+1;

	return m;
}

int is_totallyPrinted(Margin* margin){
	unsigned h_res=getHres();

	if(margin->x+margin->width>h_res){
		return 0;
	}

	return 1;
}


void pullToTheLeft(Margin** margins, unsigned short *sizeOfArray){
	unsigned short numberOfpixelsPushed=6;
	unsigned h_res=getHres();

	int i;
	for(i=2;i<*sizeOfArray-1;i++){

		margins[i]->x=margins[i]->x-numberOfpixelsPushed;
	}

	if(margins[*sizeOfArray-1]->totallyPrinted==0){
		margins[*sizeOfArray-1]->x=margins[*sizeOfArray-1]->x-numberOfpixelsPushed;

		if(is_totallyPrinted(margins[*sizeOfArray-1])==1){
			margins[*sizeOfArray-1]->totallyPrinted=1;

			if(margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width<h_res){
				margins=realloc(margins,(*sizeOfArray+1)*sizeof(Margin *));
				*sizeOfArray++;
				randomMargin(margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width,100);
			}
		}
	}

}
