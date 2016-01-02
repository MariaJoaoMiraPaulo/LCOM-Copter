#include <minix/drivers.h>
#include <stdlib.h>
#include <stdio.h>

#include "Singleplayer.h"
#include "video_gr.h"
#include "vbe.h"
#include "Menu.h"
#include "MainMenu.h"
#include "mouse.h"
#include "bitmap.h"


#include "Margins.h"


int main() {

	/* Initialize service */

	sef_startup();

	time_t t;
	srand((unsigned) time(&t));

	subscribe();
	configure_environment();
	vg_init(MODE_114);
	loadAllImages();



//	int ipc_status;
//	message msg;
//	int r,scancode=0,over=1,spacePress;
//	int fps=60,counter=0,interruptions;
//
//	//configure_environment();
//
//	while( over ) { /* You may want to use a different condition */
//		/* Get a request message. */
//		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ){
//			printf("driver_receive failed with: %d", r);
//			continue;
//		}
//		if (is_ipc_notify(ipc_status)) {
//			/* received notification */
//			switch (_ENDPOINT_P(msg.m_source)) {
//			case HARDWARE: /* hardware interrupt notification */
//				if (msg.NOTIFY_ARG & IRQ_SET_KBD) { /* subscribed interrupt */
//					scancode=keyboard_space_proj();
//					//					if(scancode==MAKE_SPACE){
//					//						spacePress=1;
//					//					}
//					//					else {
//					//						spacePress=0;
//					//					}
//					if(scancode==BREAK_ESC){
//						over=0;
//					}
//				}
//				if(msg.NOTIFY_ARG & IRQ_SET_MOUSE){
//					printf("MOUSE::entrei na int\n");
//					if(mouse_handler()==1)	{
//						printf("MOUSE:: entrei no if\n");
//					}
//					printf("MOUSE::sai da int\n");
//				}
//
//				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
//
//					counter++;
//					interruptions=counter%(60/fps);
//					if(interruptions==0){
//
//						if(counter/60 >2)
//							drawMargin();//vg_updating_double();
//						else firstImage();
//						update_screen();
//
//					}
//
//				}
//
//
//				break;
//
//			default:
//				break; /* no other notifications expected: do nothing */
//			}
//		} else { /* received a standard message, not a notification */
//			/* no standard messages expected: do nothing */
//		}
//	}



	mainMenu();
	//playingGame();

	unsubscribe();
	DeleteAllImages();
	vg_exit();

	return 0;


}
