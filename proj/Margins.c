#include <minix/drivers.h>
#include "Margins.h"
#include "video_gr.h"
#include "KBD.h"

GenerationState generationState=FIRST_MARGIN_OF_THE_BREAK;

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

void draw_margin(Margin** margins,unsigned short *sizeOfArray,unsigned int time){
	unsigned h_res=getHres();
	int idx,i,j;



	if(*sizeOfArray>2){
		if(margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width>h_res){
			for(i=margins[*sizeOfArray-1]->x;i<h_res;i++){
				for(j=margins[*sizeOfArray-1]->y;j<margins[*sizeOfArray-1]->y+margins[*sizeOfArray-1]->height;j++){
					vg_print_pixel(i,j,MARGINS_COLOR);
				}
			}
		}
		else {
			for(i=margins[*sizeOfArray-1]->x;i<margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width;i++){
				for(j=margins[*sizeOfArray-1]->y;j<margins[*sizeOfArray-1]->y+margins[*sizeOfArray-1]->height;j++){
					vg_print_pixel(i,j,MARGINS_COLOR);
				}
			}
		}

		for(idx=0;idx<*sizeOfArray-1;idx++){
			for(i=margins[idx]->x;i<margins[idx]->x+margins[idx]->width;i++){
				for(j=margins[idx]->y;j<margins[idx]->y+margins[idx]->height;j++){
					vg_print_pixel(i,j,MARGINS_COLOR);
				}
			}
		}
	}
	else {
		for(idx=0;idx<*sizeOfArray;idx++){
			for(i=margins[idx]->x;i<margins[idx]->x+margins[idx]->width;i++){
				for(j=margins[idx]->y;j<margins[idx]->y+margins[idx]->height;j++){
					vg_print_pixel(i,j,MARGINS_COLOR);
				}
			}
		}
	}
	for(idx=2;idx<*sizeOfArray;idx++){
		for(i=margins[idx]->x;i<margins[idx]->x+margins[idx]->width;i++){
			for(j=margins[idx]->y+margins[idx]->height+margins[idx]->distanceToOtherMargin;j<550;j++)
				vg_print_pixel(i,j,MARGINS_COLOR);

		}
	}

}

int numberGeneration(int x1,int x2){
	return rand()%(x2-x1)+x1;
}

unsigned int tubeSize(unsigned int time){
	return (-10/3*time+400);
}

Margin* randomMargin(short x, short y,unsigned int time){
	Margin* m;
	m=(Margin *)malloc(sizeof(Margin));

	if(m==NULL)
		return NULL;

	static int sameTickeness=15;
	static unsigned int tickeness=400;

	m->distanceToOtherMargin=tickeness;
	sameTickeness--;
	if(sameTickeness==0){
		sameTickeness=15;
		tickeness=tubeSize(time);
		if(tickeness<300){
			tickeness=300;
		}
	}

	static int n,widthInUse,heightInUse,differenceInHeights, upOrDownOrEqual;


	m->x=x;
	m->y=y;

	switch(generationState){
	case FIRST_MARGIN_OF_THE_BREAK:
		m->width=numberGeneration(51,50);
		widthInUse=m->width;

		m->height=numberGeneration(6,50);
		heightInUse=m->height;

		n=numberGeneration(0,6);
		differenceInHeights=(widthInUse*n)/m->height;
		upOrDownOrEqual=numberGeneration(0,5);  //0 equal height, 1 and 2 bigger height and 3 and 4 smaller height

		if(n>0)
			generationState=REST_OF_MARGINS_AT_THE_BREAK;
		break;
	case REST_OF_MARGINS_AT_THE_BREAK:
		m->width=widthInUse;

		if(upOrDownOrEqual==1 || upOrDownOrEqual==2){
			if(!(m->y+m->height>300))
				m->height=heightInUse+differenceInHeights;
		}
		else if (upOrDownOrEqual==3 || upOrDownOrEqual==4){
			m->height=heightInUse-differenceInHeights;
			if(m->height<5)
				m->height=5;
		}
		else m->height=heightInUse;

		heightInUse=m->height;

		n--;
		if(n==0)
			generationState=FIRST_MARGIN_OF_THE_BREAK;
		break;
	}



	/*
	m->x=x;
	m->y=y;
	m->width=rand()%51+50;
	m->height=rand()%49+21;*/

	/*m->x=x;
	m->y=y;
	m->width=100;
	m->height=30;*/

	return m;
}

int isTotallyPrinted(Margin* margin){
	unsigned h_res=getHres();

	if(margin->x+margin->width>h_res){
		return 0;
	}

	return 1;
}


void pullToTheLeft(Margin** margins, unsigned short *sizeOfArray,unsigned int time){
	unsigned short numberOfpixelsPushed=5;
	unsigned h_res=getHres();

	if(*sizeOfArray>2){

		int i;
		for(i=2;i<*sizeOfArray-1;i++){
			margins[i]->x=margins[i]->x-numberOfpixelsPushed;
		}

		if(margins[2]->x+margins[2]->width<0){
			delete_margin(margins,sizeOfArray);
		}

		if(margins[*sizeOfArray-1]->totallyPrinted==0){

			margins[*sizeOfArray-1]->x=margins[*sizeOfArray-1]->x-numberOfpixelsPushed;
			if(isTotallyPrinted(margins[*sizeOfArray-1])==1){

				margins[*sizeOfArray-1]->totallyPrinted=1;

				if(margins[*sizeOfArray-1]->x+margins[*sizeOfArray-1]->width<=h_res){
					//margins=realloc(margins,(*sizeOfArray+1)*sizeof(Margin *));

					(*sizeOfArray)++;

					margins[*sizeOfArray-1]=randomMargin(margins[*sizeOfArray-2]->x+margins[*sizeOfArray-2]->width,50,time);
				}
			}
		}
	} else {
		//*sizeOfArray=*sizeOfArray+1;
		(*sizeOfArray)++;
		//printf("Novo size2: %d", *sizeOfArray);
		margins[*sizeOfArray-1]=randomMargin(780,50,time);
		//printf("size: %d\n", *sizeOfArray);
	}
}

void firstImage(){
	unsigned hres = getHres();
	//	unsigned vres = getVres();

	vg_draw_rectangle(0,0,hres,80,rgb(51,255,51) );
	vg_draw_rectangle(0,520,hres,80,rgb(51,255,51));
}

void drawMargin() {
	//	char* videoMem = getVideoMem();
	//	char* doubleBuffer = getDoubleBuffer();
		unsigned hres = getHres();
	//	unsigned vres = getVres();
	//	unsigned bitsPerPixel = getBitsPerPixel();
	vg_draw_rectangle(0,0,hres,80,rgb(51,255,51) );
	vg_draw_rectangle(0,520,hres,80,rgb(51,255,51));
	vg_updating_double();

	//polling pixels to the left 5 pixels for each frame
	//	int i, j;
	//	for (i = 0; j < vres - NUMBER_OF_PIXELS_PUSHED; i++) {
	//		for (j = 0; i < hres- NUMBER_OF_PIXELS_PUSHED; j++) {
	//			*doubleBuffer=*(videoMem + ((j+NUMBER_OF_PIXELS_PUSHED+i * hres)* bitsPerPixel/8));
	//		}
	//	}

	//creating and drawing pixels that are in dimensions hres-NUMBER_OF_PIXELS_PUSHED
	//	for(i = vres - NUMBER_OF_PIXELS_PUSHED; i < vres; i++){
	//		for(j = hres - NUMBER_OF_PIXELS_PUSHED; j < hres; j++){
	//			if(*(doubleBuffer + (( (j-1) + NUMBER_OF_PIXELS_PUSHED + i * hres)* bitsPerPixel/8))== 18)
	//				**(doubleBuffer + (( j + NUMBER_OF_PIXELS_PUSHED + i * hres)* bitsPerPixel/8)) = 18;
	//		}
	//	}

}

