#include "MainMenu.h"

//#include "mouse.h"
#include "keyboard.h"
#include "KBD.h"
#include "Singleplayer.h"


extern unsigned long IRQ_SET_KBD;
extern int IRQ_SET_TIMER;
extern unsigned long IRQ_SET_MOUSE ;

Bitmap* mouse;
Bitmap* menu;
Bitmap* gameOverImage;

void loadImageMainMenu(){

	mouse=loadBitmap("/home/lcom/repos/proj/images/mouse.bmp");
	menu=loadBitmap("/home/lcom/repos/proj/images/Menu.bmp");
	gameOverImage=loadBitmap("/home/lcom/repos/proj/images/gameOver.bmp");

}

void deleteImageMainMenu(){

	deleteBitmap(mouse);
	deleteBitmap(menu);
	deleteBitmap(gameOverImage);
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

	//image
	mM->menuImage=menu;

	return mM;
}

MenuGameOver* MenuGameOverInit(){
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
				if(msg.NOTIFY_ARG & IRQ_SET_MOUSE){printf("MOUSE::entrei na int\n");
				if(mouse_handler()==1)	{
					printf("MOUSE:: entrei no if\n");
					atualMousePosition(&(mM->mouse));
				}
				printf("MOUSE::sai da int\n");
				}

				if(msg.NOTIFY_ARG & IRQ_SET_TIMER){printf("TIMER::entrei na int\n");
				counter++;
				interruptions=counter%(60/fps);
				if(interruptions==0){
					printf("TIMER:: entrei no if\n");
					drawBitmap(mM->menuImage,0,0);
					drawButton(&(mM->b1));
					drawButton(&(mM->b2));
					drawMouse(&(mM->mouse));
					if(hasClickedOnButton(&(mM->b1),&(mM->mouse)) != OK){
						printf("ACABOU!!!\n");
						playingGame();
						printf("ACABOU O JOGO\n");
						mainMenu();
						over=0;
					}
					if(hasClickedOnButton(&(mM->b2),&(mM->mouse)) != OK)
						over=0;
					update_screen();

				}
				printf("TIMER::sai da int\n");
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


