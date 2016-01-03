#include "MainMenu.h"

//#include "mouse.h"
#include "keyboard.h"
#include "KBD.h"
#include "Singleplayer.h"


extern unsigned long IRQ_SET_KBD;
extern int IRQ_SET_TIMER;
extern unsigned long IRQ_SET_MOUSE ;
char chooseImage='0';

Bitmap* mouse;
Bitmap* menu;
Bitmap* gameOverImage;
Bitmap* optionImage;

void loadImageMainMenu(){

	mouse=loadBitmap("/home/lcom/repos/proj/images/mouse.bmp");
	menu=loadBitmap("/home/lcom/repos/proj/images/Menu.bmp");
	gameOverImage=loadBitmap("/home/lcom/repos/proj/images/gameOver.bmp");
	optionImage=loadBitmap("/home/lcom/repos/proj/images/option.bmp");

}

void deleteImageMainMenu(){

	deleteBitmap(mouse);
	deleteBitmap(menu);
	deleteBitmap(gameOverImage);
	deleteBitmap(optionImage);
}

MainMenu* mainMenuInit(){
	MainMenu* mM;

	mM=(MainMenu*)malloc(sizeof(MainMenu ));

	//mouse
	mM->mouse.x=0;
	mM->mouse.y=0;
	mM->mouse.lButton=0;
	mM->mouse.rButton=0;
	mM->mouse.mButton=0;

	mM->mouse.mouseImage=mouse;
	//button play
	mM->b1.x=300;
	mM->b1.y=340;
	mM->b1.height=55;
	mM->b1.width=160;

	//button Exit
	mM->b2.x=153;
	mM->b2.y=318;
	mM->b2.height=60;
	mM->b2.width=110;

	//button options
	mM->b3.x=303;
	mM->b3.y=457;
	mM->b3.height=70;
	mM->b3.width=160;

	//image
	mM->menuImage=menu;

	return mM;
}

MenuGameOver* menuGameOverInit(){
	MenuGameOver* mM;

	mM=(MenuGameOver*)malloc(sizeof(MenuGameOver ));

	//mouse
	mM->mouse.x=0;
	mM->mouse.y=0;
	mM->mouse.lButton=0;
	mM->mouse.rButton=0;
	mM->mouse.mButton=0;

	mM->mouse.mouseImage=mouse;

	//button EXIT
	mM->b1.x=135;
	mM->b1.y=203;
	mM->b1.height=130;
	mM->b1.width=260;

	//button PLAY
	mM->b2.x=406;
	mM->b2.y=89;
	mM->b2.height=142;
	mM->b2.width=360;

	//button main menu
	mM->b3.x=47;
	mM->b3.y=39;
	mM->b3.height=150;
	mM->b3.width=100;

	//image
	mM->menuImage=gameOverImage;

	return mM;
}


void mainMenuDestructor(MainMenu* mM){
	free(mM);
}

void  menuGameOverDestructor(MenuGameOver* mM){
	free(mM);
}

int mainMenu(){

	MainMenu* mM;
	mM=mainMenuInit();

	////////////////////////////////////

	int ipc_status;
	message msg;
	int r,scancode=0,over=1,spacePress;
	int fps=60,counter=0,interruptions;

	//configure_environment();

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
					//					if(scancode==MAKE_SPACE){
					//						spacePress=1;
					//					}
					//					else {
					//						spacePress=0;
					//					}
					if(scancode==BREAK_ESC){
						over=0;
					}
				}
				if(msg.NOTIFY_ARG & IRQ_SET_MOUSE){
					if(mouse_handler()==1)	{
						atualMousePosition(&(mM->mouse));
					}
				}

				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
					counter++;
					interruptions=counter%(60/fps);
					if(interruptions==0){
						drawBitmap(mM->menuImage,0,0);
						drawButton(&(mM->b1));
						drawButton(&(mM->b2));
						drawButton(&(mM->b3));
						drawMouse(&(mM->mouse));
						if(hasClickedOnButton(&(mM->b1),&(mM->mouse)) != OK){
							resetMouse(&(mM->mouse));

							playingGame(chooseImage);
							gameOver();
						}
						if(hasClickedOnButton(&(mM->b2),&(mM->mouse)) != OK)
							over=0;
						if(hasClickedOnButton(&(mM->b3),&(mM->mouse)) != OK){
							printf("CARREGUEI NO BOTAO");
							resetMouse(&(mM->mouse));
							optionMenu();
						}

						update_screen();

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

	mainMenuDestructor(mM);

	return 0;

}

int gameOver(){

	MenuGameOver* mGO;
	mGO=menuGameOverInit();

	////////////////////////////////////

	int ipc_status;
	message msg;
	int r,scancode=0,over=1,spacePress;
	int fps=60,counter=0,interruptions;

	//configure_environment();

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
					//					if(scancode==MAKE_SPACE){
					//						spacePress=1;
					//					}
					//					else {
					//						spacePress=0;
					//					}
					if(scancode==BREAK_ESC){
						over=0;
					}
				}
				if(msg.NOTIFY_ARG & IRQ_SET_MOUSE){
					if(mouse_handler()==1)	{
						atualMousePosition(&(mGO->mouse));
					}
				}

				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
					counter++;
					interruptions=counter%(60/fps);
					if(interruptions==0){
						drawBitmap(mGO->menuImage,0,0);
						drawButton(&(mGO->b1));
						drawButton(&(mGO->b2));
						drawButton(&(mGO->b3));
						drawMouse(&(mGO->mouse));
						if(hasClickedOnButton(&(mGO->b1),&(mGO->mouse)) != OK){
							over=0;
						}
						if(hasClickedOnButton(&(mGO->b2),&(mGO->mouse)) != OK){
							playingGame(chooseImage);
							gameOver();
							over=0;
						}
						if(hasClickedOnButton(&(mGO->b3),&(mGO->mouse)) != OK){
							over=0;
						}
						update_screen();

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

	menuGameOverDestructor(mGO);

	return 0;
}

OptionMenu* optionMenuInit(){
	OptionMenu* oM;

	oM=(OptionMenu*)malloc(sizeof(OptionMenu ));

	//mouse
	oM->mouse.x=0;
	oM->mouse.y=0;
	oM->mouse.lButton=0;
	oM->mouse.rButton=0;
	oM->mouse.mButton=0;

	oM->mouse.mouseImage=mouse;

	//button copter
	oM->b1.x=117;
	oM->b1.y=200;
	oM->b1.height=133;
	oM->b1.width=230;

	//button fish
	oM->b2.x=476;
	oM->b2.y=187;
	oM->b2.height=151;
	oM->b2.width=227;

	//button exit
	oM->b3.x=254;
	oM->b3.y=395;
	oM->b3.height=103;
	oM->b3.width=256;

	//image
	oM->menuImage=optionImage;

	return oM;
}

void  optionMenuDestructor(OptionMenu* oM){
	free(oM);
}

int optionMenu(){
	OptionMenu* oM;
	oM=optionMenuInit();

	////////////////////////////////////


	printf("ENTREIIIIIIIIIIIIIIIIIIII\n");

	int ipc_status;
	message msg;
	int r,scancode=0,over=1,spacePress;
	int fps=60,counter=0,interruptions;

	//configure_environment();

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
					//					if(scancode==MAKE_SPACE){
					//						spacePress=1;
					//					}
					//					else {
					//						spacePress=0;
					//					}
					if(scancode==BREAK_ESC){
						over=0;
					}
				}
				if(msg.NOTIFY_ARG & IRQ_SET_MOUSE){
					if(mouse_handler()==1)	{
						atualMousePosition(&(oM->mouse));
					}
				}

				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){printf("TIMER::Entrei no timer\n");
				counter++;
				interruptions=counter%(60/fps);
				if(interruptions==0){
					drawBitmap(oM->menuImage,0,0);
					drawButton(&(oM->b1));
					drawButton(&(oM->b2));
					drawButton(&(oM->b3));


					drawMouse(&(oM->mouse));
					if(hasClickedOnButton(&(oM->b1),&(oM->mouse)) != OK){
						chooseImage='0';
					}
					if(hasClickedOnButton(&(oM->b2),&(oM->mouse)) != OK){
						chooseImage='1';
					}
					if(hasClickedOnButton(&(oM->b3),&(oM->mouse)) != OK){
						printf("CARREGOU NO EXIT!!!!!!!!!!!!!");
						over=0;
					}

					update_screen();

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

	optionMenuDestructor(oM);

	printf("Sai\n");
	return 0;
}

void resetMouse(MouseInfo* mouse){
	mouse->x=0;
	mouse->y=0;
	mouse->lButton=0;
	mouse->rButton=0;
	mouse->mButton=0;
}
