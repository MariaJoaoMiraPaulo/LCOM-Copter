#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdio.h>

#include "video_gr.h"
#include "vbe.h"
#include "timer.h"
#include "i8254.h"
#include "KBD.h"
#include "keyboard.h"
#include "sprite.h"
#include "pixmap.h"
#include "read_xpm.c"


void *test_init(unsigned short mode, unsigned short delay) {

	char *video_mem = vg_init(mode);

	if(video_mem == NULL)
	{
		printf("\ttest_init(): vg_init() failed\n");
		vg_exit();
		return NULL;
	}

	timer_test_int(delay);

	if(vg_exit()!=OK){
		printf("\ttest_init(): vg_exit() failed\n");
		return NULL;
	}

	vbe_mode_info_t mode_info;
	if(vbe_get_mode_info(mode, &mode_info) != OK)
	{
		printf("\ttest_init(): vbe_get_mode_info() failed\n");
		return NULL;
	}
	printf("\nHres : %d", mode_info.XResolution);
	printf("\nVres : %d", mode_info.YResolution);
	printf("\nBits Per Pixel : %d", mode_info.BitsPerPixel);
	printf("\nPhysical address of the video RAM: 0x%X\n", mode_info.PhysBasePtr);

	return video_mem;

}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	message msg;
	int r,scancode=0,over=1;

	if(vg_draw_square(x, y, size, color) != OK)
	{
		vg_exit();
		if(keyboard_unsubscribe_int() != OK){
			return 1;
		}
		printf("\tERROR : vg_draw_square() failed\n\tInvalid combination of coordinates and size for this screen type\n");
		return 1;
	}


	while( over ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */
					scancode=keyboard_c_handler();
					if(scancode==BREAK_ESC){
						over=0;

					}
				}
				break;

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if(keyboard_unsubscribe_int() != OK){
		return 1;
	}

	vg_exit(); //the function will go to text mode and to thw wrong terminal, then change to terminal ( alt + f1 )

	return 0;
}

int test_line(unsigned short xi, unsigned short yi,
		unsigned short xf, unsigned short yf, unsigned long color) {

	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	message msg;
	int r,scancode=0,over=1;


	if(vg_draw_line(xi,yi,xf,yf, color) != 0)
	{
		vg_exit();
		if(keyboard_unsubscribe_int() != OK){
			return 1;
		}
		printf("\tERROR : vg_draw_line() failed\n\tInvalid combination of coordinates and size for this screen type\n");
		return 1;
	}


	while( over ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */
					scancode=keyboard_c_handler();
					if(scancode==BREAK_ESC){
						over=0;

					}
				}
				break;

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if(keyboard_unsubscribe_int() != OK){
		return 1;
	}

	vg_exit(); //the function will go to text mode and to the wrong terminal,
	//then change to terminal ( alt + f1 )

	return 0;

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {


	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	message msg;
	int r,scancode=0,over=1;
	int  width,height;

	vg_init(MODE_105);

	char *map=(char *)read_xpm(xpm,&width,&height);

	if(vg_draw_xpm(xi,yi,width,height,	map)!=OK){
		printf("\tERROR : vg_draw_xpm() failed\n");
		vg_exit();
		if(keyboard_unsubscribe_int() != OK){
			return 1;
		}
		return 1;
	}

	while( over ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */
					scancode=keyboard_c_handler();
					if(scancode==BREAK_ESC){
						over=0;

					}
				}
				break;

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	free(map);

	if(keyboard_unsubscribe_int() != OK){
		return 1;
	}

	vg_exit(); //the function will go to text mode and to the wrong terminal,
	//then change to terminal ( alt + f1 )

	return 0;





}

int test_move(unsigned short xi, unsigned short yi, char *xpm[],
		unsigned short hor, short delta, unsigned short time) {

	int ipc_status;
	int irq_set_kbd =  keyboard_subscribe_int();
	int irq_set_timer=timer_subscribe_int();
	message msg;
	int r,scancode=0,over=1;
	int  width,height;
	int fps=30,counter=0,interruptions;

	vg_init(MODE_105);

	Sprite animation;

	animation.map=(char *)read_xpm(xpm,&animation.width,&animation.height);
	animation.x=xi;
	animation.y=yi;
	if(hor!=0){
		animation.xspeed=delta/(time*fps);
		animation.yspeed=0;
	}
	else {
		animation.yspeed=delta/(time*fps);
		animation.xspeed=0;
	}

	vg_draw_xpm(animation.x,animation.y,animation.width,animation.height,animation.map);

	while( over ) { /* You may want to use a different condition */
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) {
			/* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
			case HARDWARE: /* hardware interrupt notification */
				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */
					scancode=keyboard_c_handler();
					if(scancode==BREAK_ESC){
						over=0;
					}
				}
				if(msg.NOTIFY_ARG & irq_set_timer){
					counter++;
					if(counter/60 <= time){
						interruptions=counter%(60/fps);
						if(interruptions==0){
							vg_screen_to_black();
							if(delta>0){
								animation.x+=animation.xspeed;
								animation.y+=animation.yspeed;
							}
							else {
								animation.x-=animation.xspeed;
								animation.y-=animation.yspeed;
							}
							vg_draw_xpm(animation.x,animation.y,animation.width,animation.height,animation.map);
						}
					}
				}
				break;

			default:
				break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	free(animation.map);

	if(keyboard_unsubscribe_int() != OK){
		vg_exit();
		return 1;
	}

	if(timer_unsubscribe_int()==1){
		vg_exit();
		return 1;
	}

	vg_exit(); //the function will go to text mode and to the wrong terminal,
	//then change to terminal ( alt + f1 )

	return 0;

}

int test_controller() {

	/* To be completed */

}
