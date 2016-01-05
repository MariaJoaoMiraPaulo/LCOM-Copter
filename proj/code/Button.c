#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/sysutil.h>

#include "Button.h"
#include "video_gr.h"

void drawButton(Button *b){
	int i;

//	if (b->x < 0 || b->x + size > h_res || y < 0 || y + size > v_res) {
//		return 1;
//	}

	for (i = b->x; i < b->width + b->x; i++) {
		vg_print_pixel(i,b->y,rgb(51,255,51));
		vg_print_pixel(i,b->y+b->height,rgb(51,255,51));
	}
	for(i = b->y; i< b->height+b->y;i++){
		vg_print_pixel(b->x,i,rgb(51,255,51));
		vg_print_pixel(b->x+b->width,i,rgb(51,255,51));
	}
	//vg_draw_square(b->x,b->y,b->height,rgb(51,255,51));
}

int hasClickedOnButton(Button *b, MouseInfo *mouse){
	if(mouse->lButton == 1){
		if( mouse->x >= b->x && mouse->x <= b->x+b->width)
			if( mouse->y >= b->y && mouse->y <= b->y+b->height)
				return 1;
	}

	return 0;
}
