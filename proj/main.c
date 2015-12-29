#include <minix/drivers.h>
#include <stdlib.h>
#include <stdio.h>
#include "copter.h"
#include "vbe.h"
#include "keyboard.h"
#include "timer.h"
#include "i8254.h"
#include "KBD.h"
#include "lmlib.h"
#include "video_gr.h"
#include "GameState.h"
#include "Obstacles.h"
#include "Margins.h"
#include "bitmap.h"
#include "math.h"

int main() {

//	int ipc_status;
//	unsigned long irq_set_kbd =  keyboard_subscribe_int();
//	message msg;
//	int r,scancode=0,over=1;
//	int  width,height;
//	unsigned long cor=0,RGB=0;
//	sef_startup();
//
//	vg_init(0x114);
//	Bitmap* teste;
//	//vg_draw_square(0, 0, 600,rgb(0,255,0));
//	//teste=loadBitmap("/home/lcom/repos/proj/images/abcp.bmp");
//	DrawCircle(300, 300, 100, rgb(0,255,0));
//
//
////	int i=0;
////	int pos;
////	int distance = 1056789;
////	char t;
////	while (distance > 0) {
////		int digit = distance % 10;
////		pos=400-i*20;
////		t= (char) (digit + '0');
////		drawNumbers(teste,pos,0,t);
////		distance /= 10;
////		i++;
////
////		printf("i::%d",i);
////	}
////
//
//
//	update_screen();
//
//
//	//drawNumbers(teste, 0, 0, 'O');
//	//drawNumbers(teste, 20, 0, 'L');
//	//drawNumbers(teste, 40, 1, 'A');
//	//drawBitmapWithoutBackground (teste,0,0);
//	//drawBitmap(teste, 0, 0);
//
//
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
//				if (msg.NOTIFY_ARG & irq_set_kbd) { /* subscribed interrupt */
//					scancode=keyboard_c_handler();
//					if(scancode==BREAK_ESC){
//						over=0;
//
//					}
//				}
//				break;
//
//			default:
//				break; /* no other notifications expected: do nothing */
//			}
//		} else { /* received a standard message, not a notification */
//			/* no standard messages expected: do nothing */
//		}
//	}
//
//	deleteBitmap(teste);
//
//	if(keyboard_unsubscribe_int() != OK){
//		return 1;
//	}
//
//	vg_exit(); //the function will go to text mode and to the wrong terminal,
//	//then change to terminal ( alt + f1 )
//
//	return 0;
//
//}


	/* Initialize service */

	sef_startup();

	//vg_exit();
	//return 0;

	time_t t;
	srand((unsigned) time(&t));

	int ipc_status;
	unsigned long irq_set_kbd =  keyboard_subscribe_int();
	int irq_set_timer=timer_subscribe_int();
	unsigned long irq_set_mouse =  mouse_subscribe_int();
	message msg;
	int r,scancode=0,over=1;
	int fps=60,counter=0,interruptions;
	int spacePress=0, LeftButtonPress=0;

	Copter* c=newCopter(200,400,80,44);
	Margin* m1=newMargin(0,0,800,50);
	Margin* m2=newMargin(0,550,800,50);
	Margin **margins;
	//	margins=(Margin **) malloc(2*sizeof(Margin *));
	margins=(Margin **) malloc(20*sizeof(Margin *));
	margins[0]=m1;
	margins[1]=m2;
	unsigned short sizeOfArray=2;
	Obstacle* obs;

	//vg_init(MODE_105);
	//vg_init(MODE_103);
	vg_init(0x114);


	configure_environment();

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
					scancode=keyboard_space_proj();
					if(scancode==MAKE_SPACE){
						printf("RECEBI INTERRUOÇAO::::::");
						spacePress=1;
					}
					else {
						spacePress=0;
					}
					if(scancode==BREAK_ESC){
						over=0;
					}
				}
				if(msg.NOTIFY_ARG & irq_set_mouse){
					if(mouse_handler()==1)
					{
						if (mouse_left_button_press()==1)
						{
							LeftButtonPress=1;

						}
						else LeftButtonPress=0;

					}
				}

				if(msg.NOTIFY_ARG & irq_set_timer){
					counter++;
					interruptions=counter%(60/fps);
					if((double)counter/60==5)
						obs=newObstacle(margins[sizeOfArray-1]);
					if(interruptions==0){
						if( LeftButtonPress==0 && spacePress==0 )
							update_copter(c,1);  //==0sobe !=0desce
						else
							update_copter(c,0);

						if(updateGame(c,margins,&sizeOfArray,counter/60,obs)==HIT){
							over=0;
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

	if(keyboard_unsubscribe_int() != OK){
		vg_exit();
		return 1;
	}

	if(timer_unsubscribe_int()==1){
		vg_exit();
		return 1;
	}

	while_out_buf_full();
	if(mouse_unsubscribe_int() != 0){
		vg_exit();
		return 1;
	}

	delete_copter(c);
	int i;
	for(i=0;i<20;i++){
		free(margins[i]);
	}
	free(margins);//free(m1);free(m2);
	free(obs);
	vg_exit(); //the function will go to text mode and to the wrong terminal, then change to terminal ( alt + f1 )

	return 0;
 }
