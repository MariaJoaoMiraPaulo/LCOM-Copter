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
	sp->copter=newCopter(200,300,60,30);

	sp->spacePress=0;
	sp->LeftButtonPress=0;

	update_screen();
	firstImage();
	update_screen();

	return sp;
}

void singleplayerDestructor(Singleplayer* sp){
	deleteCopter(sp->copter);

	deleteObstacle(sp->obs);

	free(sp);
}

int playingGame(char chooseCopter){

	Singleplayer* sp;
	sp=singleplayerInit();

	////////////////////////////////////

	int ipc_status;
	message msg;
	int r,scancode=0,over=1;
	int fps=60,counter=0,interruptions;
	//nt spacePress=0, LeftButtonPress=0;
	SingleplayerState state=WAITING;

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
						sp->spacePress=1;
					}
					else {
						sp->spacePress=0;
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
							sp->LeftButtonPress=1;

						}
						else sp->LeftButtonPress=0;

					}
				}

				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
					counter++;
					interruptions=counter%(60/fps);
					if(interruptions==0){
						switch(state){
						case WAITING:
					   		updateGame(sp,counter/60,chooseCopter,0);
							if(  sp->spacePress==1 ){
								state=NO_HIT;
								counter=0;
							}
							break;
						case NO_HIT:
							if((double)counter/60==3)
								sp->obs=newObstacle();

							if( sp->LeftButtonPress==0 && sp->spacePress==0 )
								update_copter(sp->copter,1);  //==0sobe !=0desce
							else
								update_copter(sp->copter,0);

							if(updateGame(sp,counter/60,chooseCopter,1)==HIT){
									state=HIT;
									counter=0;
							}

							break;
						case HIT:
							if(counter/60>2)
								over=0;
							else
								hitDraws(sp, chooseCopter,counter/60);
							break;
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

	singleplayerDestructor(sp);

	return 0;
}
