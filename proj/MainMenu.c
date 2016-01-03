#include "MainMenu.h"

//#include "mouse.h"
#include "keyboard.h"
#include "KBD.h"
#include "Singleplayer.h"


extern unsigned long IRQ_SET_KBD;
extern int IRQ_SET_TIMER;
extern unsigned long IRQ_SET_MOUSE ;
char chooseImage='0';

MainMenu* mainMenu;
OptionMenu* optionMenu;
MenuGameOver* gameOverMenu;
CheckState checkState;
ProgramState programState=MAIN_MENU;
Bitmap* mouse;
Bitmap* menu;
Bitmap* gameOverImage;
Bitmap* optionImage;
Bitmap* checkImage;

void loadImageMainMenu(){

	mouse=loadBitmap("/home/lcom/repos/proj/images/mouse.bmp");
	menu=loadBitmap("/home/lcom/repos/proj/images/Menu.bmp");
	gameOverImage=loadBitmap("/home/lcom/repos/proj/images/gameOver.bmp");
	optionImage=loadBitmap("/home/lcom/repos/proj/images/option.bmp");
	checkImage=loadBitmap("/home/lcom/repos/proj/images/check.bmp");

}

void deleteImageMainMenu(){

	deleteBitmap(mouse);
	deleteBitmap(menu);
	deleteBitmap(gameOverImage);
	deleteBitmap(optionImage);
	deleteBitmap(checkImage);
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

void mainMenuDestructor(MainMenu* mM){
	free(mM);
}

int mainMenuTimerInt(MainMenu* mM){
	drawBitmap(mM->menuImage,0,0);
//	drawButton(&(mM->b1));
//	drawButton(&(mM->b2));
//	drawButton(&(mM->b3));
	drawMouse(&(mM->mouse));
	int retorno;

	if(hasClickedOnButton(&(mM->b1),&(mM->mouse)) != OK){
		resetMouse(&(mM->mouse));

		playingGame(chooseImage);
		programState=GAME_OVER_MENU;

		return runningProgram();
	}
	if(hasClickedOnButton(&(mM->b2),&(mM->mouse)) != OK)
		return 0;
	if(hasClickedOnButton(&(mM->b3),&(mM->mouse)) != OK){
		resetMouse(&(mM->mouse));
		//optionMenu();
		programState=OPTION_MENU;
		checkState=NO_CHECK;
		runningProgram();
	}

	return 1;

}

//int mainMenu(){
//
//	MainMenu* mM;
//	mM=mainMenuInit();
//
//	////////////////////////////////////
//
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
//					if(mouse_handler()==1)	{
//						atualMousePosition(&(mM->mouse));
//					}
//				}
//
//				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
//					counter++;
//					interruptions=counter%(60/fps);
//					if(interruptions==0){
//						//						drawBitmap(mM->menuImage,0,0);
//						//						drawButton(&(mM->b1));
//						//						drawButton(&(mM->b2));
//						//						drawButton(&(mM->b3));
//						//						drawMouse(&(mM->mouse));
//						//						if(hasClickedOnButton(&(mM->b1),&(mM->mouse)) != OK){
//						//							resetMouse(&(mM->mouse));
//						//
//						//							playingGame(chooseImage);
//						//							gameOver();
//						//						}
//						//						if(hasClickedOnButton(&(mM->b2),&(mM->mouse)) != OK)
//						//							over=0;
//						//						if(hasClickedOnButton(&(mM->b3),&(mM->mouse)) != OK){
//						//							resetMouse(&(mM->mouse));
//						//							optionMenu();
//						//						}
//						over=mainMenuTimerInt(mM);
//
//						update_screen();
//
//					}
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
//
//	mainMenuDestructor(mM);
//
//	return 0;
//
//}

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
	mM->b3.y=60;
	mM->b3.height=130;
	mM->b3.width=220;

	//image
	mM->menuImage=gameOverImage;

	return mM;
}

void  menuGameOverDestructor(MenuGameOver* mM){
	free(mM);
}

int menuGameOverTimerInt(MenuGameOver* mGO, int *ret){

	drawBitmap(mGO->menuImage,0,0);
//	drawButton(&(mGO->b1));
//	drawButton(&(mGO->b2));
//	drawButton(&(mGO->b3));
	drawMouse(&(mGO->mouse));

	//button EXIT
	if(hasClickedOnButton(&(mGO->b1),&(mGO->mouse)) != OK){
		programState=MAIN_MENU;
		//ret=0;
		*(ret)=0;
		return 0;
	}

	//button PLAY
	if(hasClickedOnButton(&(mGO->b2),&(mGO->mouse)) != OK){
		playingGame(chooseImage);
		//gameOver();
		runningProgram();
		return 0;
	}

	//button main menu
	if(hasClickedOnButton(&(mGO->b3),&(mGO->mouse)) != OK){
		programState=MAIN_MENU;
		//ret=1;
		*(ret)=1;
		return 0;
	}

	return 1;
}

//int gameOver(){
//
//	MenuGameOver* mGO;
//	mGO=menuGameOverInit();
//
//	int ret=1;
//
//	////////////////////////////////////
//
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
//					if(mouse_handler()==1)	{
//						atualMousePosition(&(mGO->mouse));
//					}
//				}
//
//				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
//					counter++;
//					interruptions=counter%(60/fps);
//					if(interruptions==0){
//						//						drawBitmap(mGO->menuImage,0,0);
//						//						drawButton(&(mGO->b1));
//						//						drawButton(&(mGO->b2));
//						//						drawButton(&(mGO->b3));
//						//						drawMouse(&(mGO->mouse));
//						//						if(hasClickedOnButton(&(mGO->b1),&(mGO->mouse)) != OK){
//						//							ret=0;
//						//							over=0;
//						//						}
//						//						if(hasClickedOnButton(&(mGO->b2),&(mGO->mouse)) != OK){
//						//							playingGame(chooseImage);
//						//							gameOver();
//						//							over=0;
//						//						}
//						//						if(hasClickedOnButton(&(mGO->b3),&(mGO->mouse)) != OK){
//						//							over=0;
//						//						}
//						over= menuGameOverTimerInt(mGO, &ret);
//						update_screen();
//
//					}
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
//
//	menuGameOverDestructor(mGO);
//
//	return ret;
//}

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
	oM->b1.x=75;
	oM->b1.y=180;
	oM->b1.height=101;
	oM->b1.width=151;

	//button fish
	oM->b2.x=567;
	oM->b2.y=230;
	oM->b2.height=142;
	oM->b2.width=181;

	//button flappy
	oM->b3.x=138;
	oM->b3.y=342;
	oM->b3.height=81;
	oM->b3.width=112;

	//button rocket
	oM->b4.x=320;
	oM->b4.y=366;
	oM->b4.height=183;
	oM->b4.width=140;

	//button paper plane
	oM->b5.x=105;
	oM->b5.y=445;
	oM->b5.height=120;
	oM->b5.width=180;

	//button plane
	oM->b6.x=252;
	oM->b6.y=200;
	oM->b6.height=141;
	oM->b6.width=300;

	//button exit
	oM->b7.x=539;
	oM->b7.y=446;
	oM->b7.height=94;
	oM->b7.width=198;

	//images
	oM->menuImage=optionImage;
	oM->check=checkImage;

	return oM;
}

void  optionMenuDestructor(OptionMenu* oM){
	free(oM);
}

int optionMenuTimerInt(OptionMenu* oM,int time){
	drawBitmap(oM->menuImage,0,0);

	switch(checkState){
	case NO_CHECK:
//		drawButton(&(oM->b1));
//		drawButton(&(oM->b2));
//		drawButton(&(oM->b3));
//		drawButton(&(oM->b4));
//		drawButton(&(oM->b5));
//		drawButton(&(oM->b6));
//		drawButton(&(oM->b7));

		if(hasClickedOnButton(&(oM->b1),&(oM->mouse)) != OK){
			chooseImage='0';
			checkState=SHOW_CHECK;
			oM->mouse.lButton=0;
		}
		if(hasClickedOnButton(&(oM->b2),&(oM->mouse)) != OK){
			chooseImage='1';
			checkState=SHOW_CHECK;
			oM->mouse.lButton=0;
		}
		if(hasClickedOnButton(&(oM->b3),&(oM->mouse)) != OK){
			chooseImage='2';
			checkState=SHOW_CHECK;
			oM->mouse.lButton=0;
		}
		if(hasClickedOnButton(&(oM->b4),&(oM->mouse)) != OK){
			chooseImage='3';
			checkState=SHOW_CHECK;
			oM->mouse.lButton=0;
		}
		if(hasClickedOnButton(&(oM->b5),&(oM->mouse)) != OK){
			chooseImage='4';
			checkState=SHOW_CHECK;
			oM->mouse.lButton=0;
		}
		if(hasClickedOnButton(&(oM->b6),&(oM->mouse)) != OK){
			chooseImage='5';
			checkState=SHOW_CHECK;
			oM->mouse.lButton=0;
		}
		if(hasClickedOnButton(&(oM->b7),&(oM->mouse)) != OK){
			programState=MAIN_MENU;
			return 0;
		}

		break;
	case SHOW_CHECK:
		drawBitmapWithoutBackground(oM->check,350,280);
		time++;
		if(time/60>1){
			checkState=NO_CHECK;
			time=0;
		}
		break;
	}

	drawMouse(&(oM->mouse));

	return 1;
}

//int optionMenu(){
//	OptionMenu* oM;
//	oM=optionMenuInit();
//	checkState=NO_CHECK;
//	int time=0;
//
//	////////////////////////////////////
//
//
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
//					if(mouse_handler()==1)	{
//						atualMousePosition(&(oM->mouse));
//					}
//					switch(checkState)
//					case SHOW_CHECK:
//						if(oM->mouse.lButton=1){
//							checkState=NO_CHECK;
//							oM->mouse.lButton=0;
//						}
//						break;
//				}
//
//				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
//					counter++;
//					interruptions=counter%(60/fps);
//					if(interruptions==0){
//						//						drawBitmap(oM->menuImage,0,0);
//						//
//						//						switch(checkState){
//						//						case NO_CHECK:
//						//							drawButton(&(oM->b1));
//						//							drawButton(&(oM->b2));
//						//							drawButton(&(oM->b3));
//						//							drawButton(&(oM->b4));
//						//							drawButton(&(oM->b5));
//						//							drawButton(&(oM->b6));
//						//							drawButton(&(oM->b7));
//						//
//						//							if(hasClickedOnButton(&(oM->b1),&(oM->mouse)) != OK){
//						//								chooseImage='0';
//						//								checkState=SHOW_CHECK;
//						//								oM->mouse.lButton=0;
//						//							}
//						//							if(hasClickedOnButton(&(oM->b2),&(oM->mouse)) != OK){
//						//								chooseImage='1';
//						//								checkState=SHOW_CHECK;
//						//								oM->mouse.lButton=0;
//						//							}
//						//							if(hasClickedOnButton(&(oM->b3),&(oM->mouse)) != OK){
//						//								chooseImage='2';
//						//								checkState=SHOW_CHECK;
//						//								oM->mouse.lButton=0;
//						//							}
//						//							if(hasClickedOnButton(&(oM->b4),&(oM->mouse)) != OK){
//						//								chooseImage='3';
//						//								checkState=SHOW_CHECK;
//						//								oM->mouse.lButton=0;
//						//							}
//						//							if(hasClickedOnButton(&(oM->b5),&(oM->mouse)) != OK){
//						//								chooseImage='4';
//						//								checkState=SHOW_CHECK;
//						//								oM->mouse.lButton=0;
//						//							}
//						//							if(hasClickedOnButton(&(oM->b6),&(oM->mouse)) != OK){
//						//								chooseImage='5';
//						//								checkState=SHOW_CHECK;
//						//								oM->mouse.lButton=0;
//						//							}
//						//							if(hasClickedOnButton(&(oM->b7),&(oM->mouse)) != OK){
//						//								over=0;
//						//							}
//						//
//						//							break;
//						//						case SHOW_CHECK:
//						//							drawBitmapWithoutBackground(oM->check,350,280);
//						//							time++;
//						//							if(time/60>1){
//						//								checkState=NO_CHECK;
//						//								time=0;
//						//							}
//						//							break;
//						//						}
//						//
//						//						drawMouse(&(oM->mouse));
//						over=optionMenuTimerInt(oM,time);
//
//						update_screen();
//
//					}
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
//
//	optionMenuDestructor(oM);
//
//	return 0;
//}

void resetMouse(MouseInfo* mouse){
	mouse->x=0;
	mouse->y=0;
	mouse->lButton=0;
	mouse->rButton=0;
	mouse->mButton=0;
}

int runningProgram(){
	int time=0;
	int ret=1;

	switch(programState){
	case MAIN_MENU:
		mainMenu=mainMenuInit();
		break;
	case OPTION_MENU:
		optionMenu=optionMenuInit();
		break;
	case GAME_OVER_MENU:
		gameOverMenu=menuGameOverInit();
	}

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
						switch(programState){
						case MAIN_MENU:
							atualMousePosition(&(mainMenu->mouse));
							break;
						case OPTION_MENU:
							atualMousePosition(&(optionMenu->mouse));
							break;
						case GAME_OVER_MENU:
							atualMousePosition(&(gameOverMenu->mouse));
							break;
						}
						break;
					}
					if(programState==OPTION_MENU){
						switch(checkState){
						case SHOW_CHECK:
							if(optionMenu->mouse.lButton=1){
								checkState=NO_CHECK;
								optionMenu->mouse.lButton=0;
							}
							break;
						}
					}
				}


				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){
					counter++;
					interruptions=counter%(60/fps);
					if(interruptions==0){

						switch(programState){
						case MAIN_MENU:
							over=mainMenuTimerInt(mainMenu);
							break;
						case OPTION_MENU:
							over=optionMenuTimerInt(optionMenu,time);
							break;
						case GAME_OVER_MENU:
							over=menuGameOverTimerInt(gameOverMenu, &ret);
							break;
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
	//	switch(programState){
	//	case MAIN_MENU:
	//		mainMenuDestructor(mainMenu);
	//		break;
	//	case OPTION_MENU:
	//		optionMenuDestructor(optionMenu);
	//		break;
	//	}

	if(programState==MAIN_MENU)
		return ret;

	return 0;
}

void menusDestructor(){
	mainMenuDestructor(mainMenu);
	optionMenuDestructor(optionMenu);
	menuGameOverDestructor(gameOverMenu);
}

