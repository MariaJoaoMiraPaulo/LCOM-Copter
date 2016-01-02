#include "Singleplayer.h"

#include "KBD.h"
#include "GameState.h"
#include "Menu.h"

extern unsigned long IRQ_SET_KBD;
extern int IRQ_SET_TIMER;
extern unsigned long IRQ_SET_MOUSE ;


Singleplayer* singleplayerInit(){
	Singleplayer* sp;

	sp=(Singleplayer*) malloc(sizeof(Singleplayer));
	sp->copter=newCopter(200,300,80,44);

	//	sp->margins=(Margin **) malloc(20*sizeof(Margin *));
	//	sp->margins[0]=newMargin(0,0,800,50);
	//	sp->margins[1]=newMargin(0,550,800,50);
	//	sp->sizeOfArray=2;

	update_screen();
	firstImage();
	update_screen();

	return sp;
}

void singleplayerDestructor(Singleplayer* sp){
	//deleteCopter(sp->copter);

	//TODO A alterar!!!!!!
	/*int i;
	for(i=0;i<20;i++){
		free(sp->margins[i]);
	}*/
	//free(sp->margins);

	//deleteObstacle(sp->obs);

	free(sp);
}

int playingGame(){

	Singleplayer* sp;
	sp=singleplayerInit();

	////////////////////////////////////

	int ipc_status;
	message msg;
	int r,scancode=0,over=1;
	int fps=60,counter=0,interruptions;
	int spacePress=0, LeftButtonPress=0;

	//	configure_environment();

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
				if (msg.NOTIFY_ARG & IRQ_SET_KBD) { /* subscribed interrupt */
					scancode=keyboard_space_proj();
					if(scancode==MAKE_SPACE){
						spacePress=1;
					}
					else {
						spacePress=0;
					}
					if(scancode==BREAK_ESC){
						over=0;
					}
				}
				if(msg.NOTIFY_ARG & IRQ_SET_MOUSE){
					if(mouse_handler()==1)
					{
						if (mouse_left_button_press()==1)
						{
							LeftButtonPress=1;

						}
						else LeftButtonPress=0;

					}
				}

				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
					counter++;
					interruptions=counter%(60/fps);
					//					if((double)counter/60==5)
					//						sp->obs=newObstacle(sp->margins[sp->sizeOfArray-1]);
					if((double)counter/60==5)
						sp->obs=newObstacle();
					if(interruptions==0){
						if( LeftButtonPress==0 && spacePress==0 )
							update_copter(sp->copter,1);  //==0sobe !=0desce
						else
							update_copter(sp->copter,0);

						if(updateGame(sp,counter/60)==HIT){
							over=0;
						}
						//						if(updateGame(sp->copter,sp->margins, &(sp->sizeOfArray),counter/60, sp->obs)==HIT){
						//							over=0;
						//						}
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

	//TODO why.................

	singleplayerDestructor(sp);

	return 0;
}
