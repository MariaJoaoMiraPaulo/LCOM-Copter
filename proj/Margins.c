#include <minix/drivers.h>
#include "Margins.h"
#include "video_gr.h"

Margin* newMargin(short x, short y, short width, short height){
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

void delete_margin(Margin** margins, unsigned short *sizeOfArray){

	int i;
	for(i=2;i<*sizeOfArray;i++){
		margins[i]=margins[i+1];
	}
	(*sizeOfArray)--;
}

void draw_margin(Margin** margins,unsigned short *sizeOfArray){
	unsigned h_res=getHres();
	unsigned int idx,i,j;

	/*	for(idx=0;idx<*sizeOfArray;idx++){
		for(i=margins[idx]->x;i<margins[idx]->x+margins[idx]->width;i++){
			for(j=margins[idx]->y;j<margins[idx]->y+margins[idx]->height;j++){
				vg_print_pixel(i,j,18);
			}
		}
	}*/

	if(*sizeOfArray>2){
		if(margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width>h_res){
			for(i=margins[*sizeOfArray-1]->x;i<h_res;i++){
				for(j=margins[*sizeOfArray-1]->y;j<margins[*sizeOfArray-1]->y+margins[*sizeOfArray-1]->height;j++){
					vg_print_pixel(i,j,18);
				}
			}
		}
		else {
			for(i=margins[*sizeOfArray-1]->x;i<margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width;i++){
				for(j=margins[*sizeOfArray-1]->y;j<margins[*sizeOfArray-1]->y+margins[*sizeOfArray-1]->height;j++){
					vg_print_pixel(i,j,18);
				}
			}
		}
		for(idx=0;idx<*sizeOfArray-1;idx++){
			for(i=margins[idx]->x;i<margins[idx]->x+margins[idx]->width;i++){
				for(j=margins[idx]->y;j<margins[idx]->y+margins[idx]->height;j++){
					vg_print_pixel(i,j,18);
				}
			}
		}
	}
	else {
		for(idx=0;idx<*sizeOfArray;idx++){
			for(i=margins[idx]->x;i<margins[idx]->x+margins[idx]->width;i++){
				for(j=margins[idx]->y;j<margins[idx]->y+margins[idx]->height;j++){
					vg_print_pixel(i,j,18);
				}
			}
		}
	}

}

Margin* randomMargin(short x, short y){
	Margin* m;
	m=(Margin *)malloc(sizeof(Margin));

	if(m==NULL)
		return NULL;

	/*	m->x=x;
	m->y=y;
	m->width=rand()%51+50;
	m->height=rand()%49+1;*/

	m->x=x;
	m->y=y;
	m->width=100;
	m->height=30;

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
	unsigned short numberOfpixelsPushed=3;
	unsigned h_res=getHres();

	printf("size: %d\n", *sizeOfArray);

	if(*sizeOfArray>2){
		int i;
		for(i=2;i<*sizeOfArray-1;i++){

			margins[i]->x=margins[i]->x-numberOfpixelsPushed;
		}

		if(margins[2]->x<0){
			margins[2]->x=0;
			margins[2]->width=margins[2]->width-numberOfpixelsPushed;
			if(margins[2]->width<0){
				delete_margin(margins,sizeOfArray);
			}
		}
		printf("Passou!\n");
		if(margins[*sizeOfArray-1]->totallyPrinted==0){
			printf("Boas!\n");
			margins[*sizeOfArray-1]->x=margins[*sizeOfArray-1]->x-numberOfpixelsPushed;
			if(is_totallyPrinted(margins[*sizeOfArray-1])==1){
				printf("Novo!\n");
				margins[*sizeOfArray-1]->totallyPrinted=1;

				if(margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width<=h_res){
					//margins=realloc(margins,(*sizeOfArray+1)*sizeof(Margin *));

					(*sizeOfArray)++;
					printf("Novo size: %d\n", *sizeOfArray);
					margins[*sizeOfArray-1]=randomMargin(margins[*sizeOfArray-2]->x+margins[*sizeOfArray-2]->width,100);
				}
			}
		}
	} else {
		//*sizeOfArray=*sizeOfArray+1;
		(*sizeOfArray)++;
		//printf("Novo size2: %d", *sizeOfArray);
		margins[*sizeOfArray-1]=randomMargin(780,100);
		//printf("size: %d\n", *sizeOfArray);
	}


}
