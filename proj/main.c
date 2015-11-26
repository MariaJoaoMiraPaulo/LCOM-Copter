#include <minix/drivers.h>
#include "copter.h"
#include "vbe.h"
#include "keyboard.h"
#include "timer.h"
#include "i8254.h"
#include "KBD.h"
#include "lmlib.h"
#include "video_gr.h"
#include "GameState.h"

int main() {

	/* Initialize service */

	sef_startup();

	Copter* c=newCopter(200,400,40,10);
	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	int irq_set_timer=timer_subscribe_int();
	message msg;
	int r,scancode=0,over=1;
	int fps=30,counter=0,interruptions;
	int spacePress=0;

	vg_init(MODE_105);

	//	draw_copter(c) ;
	//	update_screen();
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
					if(scancode==MAKE_SPACE){
						spacePress=1;
						//	update_copter(c,0);
						//	draw_copter(c);
						//	update_screen();
					}
					else {
						spacePress=0;
						//	update_copter(c,1);
						//	draw_copter(c);
						//	update_screen();
					}
					if(scancode==BREAK_ESC){
						over=0;
					}
				}
				if(msg.NOTIFY_ARG & irq_set_timer){
					counter++;
					interruptions=counter%(60/fps);
					if(interruptions==0){
						if(spacePress==0)
							update_copter(c,1);
						else
							update_copter(c,0);

						updateGame	(c);
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
		vg_exit();
		return 1;
	}

	if(timer_unsubscribe_int()==1){
		vg_exit();
		return 1;
	}

	free(c);

	vg_exit(); //the function will go to text mode and to thw wrong terminal, then change to terminal ( alt + f1 )

	return 0;
}
