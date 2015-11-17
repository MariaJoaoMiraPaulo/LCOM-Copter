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

	printf("\nPhysical address of the video RAM: 0x%X\n", mode_info.PhysBasePtr);

	return video_mem;

}


int test_square(unsigned short x, unsigned short y, unsigned short size, unsigned long color) {

	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	message msg;
	int r,scancode=0,over=1;


	if(vg_draw(x, y, size, color) != 0)
	{
		vg_exit();
		printf("\tERROR : vg_draw() failed\n\tInvalid combination of coordinates and size for this screen type\n");
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
					if(scancode==BREAK_ESC)
					{
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


	if(keyboard_unsubscribe_int() != OK)
		return 1;

	vg_exit();
	return 0;
}

int test_line(unsigned short xi, unsigned short yi, 
		unsigned short xf, unsigned short yf, unsigned long color) {

	/* To be completed */

}

int test_xpm(unsigned short xi, unsigned short yi, char *xpm[]) {

	/* To be completed */

}	

int test_move(unsigned short xi, unsigned short yi, char *xpm[], 
		unsigned short hor, short delta, unsigned short time) {

	/* To be completed */

}					

int test_controller() {

	/* To be completed */

}					

