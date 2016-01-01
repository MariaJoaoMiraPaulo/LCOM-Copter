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


int main() {

	/* Initialize service */

	sef_startup();

	time_t t;
	srand((unsigned) time(&t));

	subscribe();
	configure_environment();
	vg_init(MODE_114);

	Bitmap* teste;
	teste=loadBitmap("/home/lcom/repos/proj/images/copter.bmp");
  drawBitmap(teste,0,0);

//	mainMenu();
	//playingGame();

	unsubscribe();
	vg_exit();

	return 0;


}
